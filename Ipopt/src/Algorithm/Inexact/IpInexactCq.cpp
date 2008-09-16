// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Common Public License.
//
// $Id$
//
// Authors:  Andreas Waechter             IBM    2008-08-31

#include "IpInexactCq.hpp"

namespace Ipopt
{
#if COIN_IPOPT_VERBOSITY > 0
  static const Index dbg_verbosity = 0;
#endif


  InexactCq::InexactCq(IpoptNLP* ip_nlp,
                       IpoptData* ip_data,
                       IpoptCalculatedQuantities* ip_cq)
      :
      ip_nlp_(ip_nlp),
      ip_data_(ip_data),
      ip_cq_(ip_cq),

      curr_jac_cdT_times_curr_cdminuss_cache_(1),
      curr_scaling_slacks_cache_(1),
      curr_slack_scaled_d_minus_s_cache_(1),
      slack_scaled_norm_cache_(6),
      curr_Wu_x_cache_(1),
      curr_Wu_s_cache_(1),
      curr_uWu_cache_(1)
  {
    DBG_START_METH("InexactCq::InexactCq", dbg_verbosity);
    DBG_ASSERT(ip_nlp_);
    DBG_ASSERT(ip_data_);
    DBG_ASSERT(ip_cq_);
  }

  InexactCq::~InexactCq()
  {}

  bool
  InexactCq::Initialize(const Journalist& jnlst,
                        const OptionsList& options,
                        const std::string& prefix)
  {
    return true;
  }

  SmartPtr<const Vector>
  InexactCq::curr_jac_cdT_times_curr_cdminuss()
  {
    SmartPtr<const Vector> result;
    SmartPtr<const Vector> x = ip_data_->curr()->x();
    SmartPtr<const Vector> s = ip_data_->curr()->s();

    if (!curr_jac_cdT_times_curr_cdminuss_cache_.GetCachedResult2Dep(result, *x, *s)) {
      // c part
      SmartPtr<const Vector> curr_c = ip_cq_->curr_c();
      SmartPtr<const Vector> curr_jac_cT_times_curr_c =
        ip_cq_->curr_jac_cT_times_vec(*curr_c);

      // d minus s part
      SmartPtr<const Vector> curr_d_minus_s = ip_cq_->curr_d_minus_s();
      SmartPtr<const Vector> curr_jac_dT_times_curr_d_minus_s =
        ip_cq_->curr_jac_dT_times_vec(*curr_d_minus_s);

      // add them pu
      SmartPtr<Vector> tmp = curr_jac_cT_times_curr_c->MakeNew();
      tmp->AddTwoVectors(1., *curr_jac_cT_times_curr_c,
                         1., *curr_jac_dT_times_curr_d_minus_s, 0.);
      result = ConstPtr(tmp);
      curr_jac_cdT_times_curr_cdminuss_cache_.AddCachedResult2Dep(result, *x, *s);
    }

    return result;
  }

  SmartPtr<const Vector>
  InexactCq::curr_scaling_slacks()
  {
    DBG_START_METH("InexactCq::curr_scaling_slacks()",
                   dbg_verbosity);
    SmartPtr<const Vector> result;
    SmartPtr<const Vector> s = ip_data_->curr()->s();

    if (!curr_scaling_slacks_cache_.GetCachedResult1Dep(result, *s)) {
      SmartPtr<Vector> tmp = s->MakeNew();

      // Lower bounds
      SmartPtr<const Matrix> Pd_L = ip_nlp_->Pd_L();
      SmartPtr<const Vector> curr_slack_s_L = ip_cq_->curr_slack_s_L();
      DBG_PRINT_MATRIX(1, "Pd_L", *Pd_L);
      DBG_PRINT_VECTOR(1, "curr_slack_s_L", *curr_slack_s_L);
      Pd_L->MultVector(1., *curr_slack_s_L, 0., *tmp);

      // Upper bounds
      SmartPtr<const Matrix> Pd_U = ip_nlp_->Pd_U();
      SmartPtr<const Vector> curr_slack_s_U = ip_cq_->curr_slack_s_U();
      DBG_PRINT_MATRIX(1, "Pd_U", *Pd_U);
      DBG_PRINT_VECTOR(1, "curr_slack_s_U", *curr_slack_s_U);
      Pd_U->MultVector(1., *curr_slack_s_U, 1., *tmp);

      result = ConstPtr(tmp);
      curr_scaling_slacks_cache_.AddCachedResult1Dep(result, *s);
    }

    return result;
  }

  SmartPtr<const Vector>
  InexactCq::curr_slack_scaled_d_minus_s()
  {
    SmartPtr<const Vector> result;
    SmartPtr<const Vector> x = ip_data_->curr()->x();
    SmartPtr<const Vector> s = ip_data_->curr()->s();

    if (!curr_slack_scaled_d_minus_s_cache_.GetCachedResult2Dep(result, *x, *s)) {
      SmartPtr<const Vector> d_minus_s = ip_cq_->curr_d_minus_s();
      SmartPtr<const Vector> scaling_slacks = curr_scaling_slacks();

      SmartPtr<Vector> tmp = d_minus_s->MakeNewCopy();
      tmp->ElementWiseMultiply(*scaling_slacks);
      result = ConstPtr(tmp);
      curr_slack_scaled_d_minus_s_cache_.AddCachedResult2Dep(result, *x, *s);
    }

    return result;
  }

  Number
  InexactCq::slack_scaled_norm(const Vector& x, const Vector &s)
  {
    SmartPtr<const Vector> scaling_slacks = curr_scaling_slacks();

    Number result;
    if (!slack_scaled_norm_cache_.GetCachedResult3Dep(result, *scaling_slacks, x, s)) {
      SmartPtr<Vector> tmp = s.MakeNewCopy();
      tmp->ElementWiseDivide(*scaling_slacks);
      result = ip_cq_->CalcNormOfType(NORM_2, x, *tmp);
      slack_scaled_norm_cache_.AddCachedResult3Dep(result, *scaling_slacks, x, s);
    }

    return result;
  }

  SmartPtr<const Vector>
  InexactCq::curr_Wu_x()
  {
    SmartPtr<const Vector> result;

    SmartPtr<const Vector> tangential_x = InexData().tangential_x();
    SmartPtr<const SymMatrix> W = ip_data_->W();
    Number pd_pert_x;
    Number pd_pert_s;
    Number pd_pert_c;
    Number pd_pert_d;
    ip_data_->getPDPert(pd_pert_x, pd_pert_s, pd_pert_c, pd_pert_d);

    std::vector<const TaggedObject*> tdeps(2);
    tdeps[0] = GetRawPtr(tangential_x);
    tdeps[1] = GetRawPtr(W);
    std::vector<Number> sdeps(1);
    sdeps[0] = pd_pert_x;

    if (!curr_Wu_x_cache_.GetCachedResult(result, tdeps, sdeps)) {
      SmartPtr<Vector> tmp = tangential_x->MakeNewCopy();
      W->MultVector(1., *tangential_x, pd_pert_x, *tmp);
      result = ConstPtr(tmp);
      curr_Wu_x_cache_.AddCachedResult(result, tdeps, sdeps);
    }

    return result;
  }


  SmartPtr<const Vector>
  InexactCq::curr_Wu_s()
  {
    SmartPtr<const Vector> result;

    SmartPtr<const Vector> tangential_s = InexData().tangential_s();
    SmartPtr<const Vector> sigma_s = ip_cq_->curr_sigma_s();
    Number pd_pert_x;
    Number pd_pert_s;
    Number pd_pert_c;
    Number pd_pert_d;
    ip_data_->getPDPert(pd_pert_x, pd_pert_s, pd_pert_c, pd_pert_d);

    std::vector<const TaggedObject*> tdeps(2);
    tdeps[0] = GetRawPtr(tangential_s);
    tdeps[1] = GetRawPtr(sigma_s);
    std::vector<Number> sdeps(1);
    sdeps[0] = pd_pert_s;

    if (!curr_Wu_s_cache_.GetCachedResult(result, tdeps, sdeps)) {
      SmartPtr<Vector> tmp = tangential_s->MakeNewCopy();
      tmp->ElementWiseMultiply(*sigma_s);
      if (pd_pert_s>0.) {
        tmp->AddOneVector(pd_pert_s, *tangential_s, 1.);
      }
      result = ConstPtr(tmp);
      curr_Wu_s_cache_.AddCachedResult(result, tdeps, sdeps);
    }

    return result;
  }

  Number
  InexactCq::curr_uWu()
  {
    Number result;

    SmartPtr<const Vector> tangential_x = InexData().tangential_x();
    SmartPtr<const Vector> tangential_s = InexData().tangential_s();
    SmartPtr<const Vector> Wu_x = curr_Wu_x();
    SmartPtr<const Vector> Wu_s = curr_Wu_s();

    std::vector<const TaggedObject*> tdeps(4);
    tdeps[0] = GetRawPtr(tangential_x);
    tdeps[1] = GetRawPtr(tangential_s);
    tdeps[2] = GetRawPtr(Wu_x);
    tdeps[3] = GetRawPtr(Wu_s);

    if (!curr_uWu_cache_.GetCachedResult(result, tdeps)) {
      result = Wu_x->Dot(*tangential_x) + Wu_s->Dot(*tangential_s);
      curr_uWu_cache_.AddCachedResult(result, tdeps);
    }

    return result;
  }

} // namespace Ipopt

/* src/Common/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if the inexact linear solver option is included */
/* #undef BUILD_INEXACT */

/* Define to be the name of C-function for Inf check */
#define COIN_C_FINITE

/* Define to 1 if the ASL package is available */
/* #undef COIN_HAS_ASL */

/* If defined, the BLAS Library is available. */
#define COIN_HAS_BLAS

/* Define to 1 if the HSL package is available */
/* #undef COIN_HAS_HSL */

/* If defined, the LAPACK Library is available. */
#define COIN_HAS_LAPACK

/* Define to 1 if the Mumps package is available */
#define COIN_HAS_MUMPS

/* Define to the debug sanity check level (0 is no test) */
#define COIN_IPOPT_CHECKLEVEL 0

/* Define to the debug verbosity level (0 is no output) */
#define COIN_IPOPT_VERBOSITY 0

/* Define to dummy `main' function (if any) required to link to the Fortran
   libraries. */
/* #undef F77_DUMMY_MAIN */

/* Define to a macro mangling the given C identifier (in lower and upper
   case), which must not contain underscores, for linking with Fortran. */
#define F77_FUNC(name,NAME) name##_

/* Define to a macro mangling the given C identifier (in lower and upper
   case), which must not contain underscores, for linking with Fortran. */
#define COIN_LAPACK_FUNC(name,NAME) name##_

/* As F77_FUNC, but for C identifiers containing underscores. */
#define F77_FUNC_(name,NAME) name##_

/* Define if F77 and FC dummy `main' functions are identical. */
/* #undef FC_DUMMY_MAIN_EQ_F77 */

/* Define to the C type corresponding to Fortran INTEGER */
#define FORTRAN_INTEGER_TYPE int

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H

/* Define to 1 if you have the <cassert> header file. */
#define HAVE_CASSERT

/* Define to 1 if you have the <cctype> header file. */
#define HAVE_CCTYPE

/* Define to 1 if you have the <cfloat> header file. */
#define HAVE_CFLOAT

/* Define to 1 if you have the <cieeefp> header file. */
/* #undef HAVE_CIEEEFP */

/* Define to 1 if you have the <cmath> header file. */
#define HAVE_CMATH

/* Define to 1 if you have the <cstdarg> header file. */
#define HAVE_CSTDARG

/* Define to 1 if you have the <cstddef> header file. */
#define HAVE_CSTDDEF

/* Define to 1 if you have the <cstdio> header file. */
#define HAVE_CSTDIO

/* Define to 1 if you have the <cstdlib> header file. */
#define HAVE_CSTDLIB

/* Define to 1 if you have the <cstring> header file. */
#define HAVE_CSTRING

/* Define to 1 if you have the <ctime> header file. */
#define HAVE_CTIME

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H

/* Define to 1 if function drand48 is available */
/* #undef HAVE_DRAND48 */

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H

/* Define to 1 if you have the <ieeefp.h> header file. */
/* #undef HAVE_IEEEFP_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H

/* Define to 1 if the linear solver loader should be compiled to allow dynamic
   loading of shared libraries with linear solvers */
/* #undef HAVE_LINEARSOLVERLOADER */

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H

/* Define to 1 if you have the `MPI_Initialized' function. */
/* #undef HAVE_MPI_INITIALIZED */

/* Define to 1 if Pardiso is available */
/* #undef HAVE_PARDISO */

/* Define to 1 if you are using Pardiso from MKL */
/* #undef HAVE_PARDISO_MKL */

/* Define to 1 if you are not using at least a 4.0 version of Pardiso */
/* #undef HAVE_PARDISO_OLDINTERFACE */

/* Define to 1 if you are using the parallel version of Pardiso */
/* #undef HAVE_PARDISO_PARALLEL */

/* Define to 1 if function rand is available */
#define HAVE_RAND

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H

/* Define to 1 if function std::rand is available */
/* #undef HAVE_STD__RAND */

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H

/* Define to 1 if va_copy is available */
/* #undef HAVE_VA_COPY */

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if WSMP is available */
/* #undef HAVE_WSMP */

/* Define to 1 if you have the `_snprintf' function. */
/* #undef HAVE__SNPRINTF */

/* Define to 1 if you have the `_vsnprintf' function. */
/* #undef HAVE__VSNPRINTF */

/* SVN revision number of project */
#define IPOPT_SVN_REV 1

/* Version number of project */
#define IPOPT_VERSION "3.13.0"

/* Major Version number of project */
#define IPOPT_VERSION_MAJOR 3

/* Minor Version number of project */
#define IPOPT_VERSION_MINOR 13

/* Release Version number of project */
#define IPOPT_VERSION_RELEASE 0

/* Name of package */
#define PACKAGE "IpOpt"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "bugs@coin-or.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "IpOpt"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "IpOpt"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ipopt"

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Set to extension for shared libraries in quotes. */
#define SHAREDLIBEXT "dylib"

/* The size of a `int *', as computed by sizeof. */
#define SIZEOF_INT_P 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION ""

set(CMAKE_LIBRARY_PATH_FLAG "-LIBPATH:")
set(CMAKE_LINK_LIBRARY_FLAG "")
set(WIN32 1)
if(CMAKE_VERBOSE_MAKEFILE)
  set(CMAKE_CL_NOLOGO)
else(CMAKE_VERBOSE_MAKEFILE)
  set(CMAKE_CL_NOLOGO "/nologo")
endif(CMAKE_VERBOSE_MAKEFILE)

set(CMAKE_Fortran_MODDIR_FLAG "-module:")

set(CMAKE_Fortran_USE_RESPONSE_FILE_FOR_OBJECTS 1)

set(CMAKE_Fortran_CREATE_SHARED_LIBRARY 
 "link ${CMAKE_CL_NOLOGO} <OBJECTS> ${CMAKE_START_TEMP_FILE}  /out:<TARGET> /dll  <LINK_FLAGS> <LINK_LIBRARIES> ${CMAKE_END_TEMP_FILE}")

set(CMAKE_Fortran_CREATE_SHARED_MODULE ${CMAKE_Fortran_CREATE_SHARED_LIBRARY})

# create a C++ static library
set(CMAKE_Fortran_CREATE_STATIC_LIBRARY  "lib ${CMAKE_CL_NOLOGO} <LINK_FLAGS> /out:<TARGET> <OBJECTS> ")

# compile a C++ file into an object file
set(CMAKE_Fortran_COMPILE_OBJECT
    "<CMAKE_Fortran_COMPILER>  ${CMAKE_START_TEMP_FILE} ${CMAKE_CL_NOLOGO} /fpp /Fo<OBJECT> <DEFINES> <FLAGS> -c <SOURCE>${CMAKE_END_TEMP_FILE}")

set(CMAKE_COMPILE_RESOURCE "rc <FLAGS> /fo<OBJECT> <SOURCE>")

set(CMAKE_Fortran_LINK_EXECUTABLE
    "<CMAKE_Fortran_COMPILER> ${CMAKE_CL_NOLOGO} <OBJECTS> ${CMAKE_START_TEMP_FILE} <FLAGS> /Fe<TARGET> -link <CMAKE_Fortran_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>${CMAKE_END_TEMP_FILE}")

set(CMAKE_CREATE_WIN32_EXE /subsystem:windows)
set(CMAKE_CREATE_CONSOLE_EXE /subsystem:console)

if(CMAKE_GENERATOR MATCHES "Visual Studio 6")
  set(CMAKE_NO_BUILD_TYPE 1)
endif(CMAKE_GENERATOR MATCHES "Visual Studio 6")

if(CMAKE_GENERATOR MATCHES "Visual Studio 7" OR CMAKE_GENERATOR MATCHES "Visual Studio 8")
  set(CMAKE_NO_BUILD_TYPE 1)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING 
     "Semicolon separated list of supported configuration types, only supports Debug, Release, MinSizeRel, and RelWithDebInfo, anything else will be ignored.")
endif(CMAKE_GENERATOR MATCHES "Visual Studio 7" OR CMAKE_GENERATOR MATCHES "Visual Studio 8")
# does the compiler support pdbtype and is it the newer compiler

set(CMAKE_BUILD_TYPE_INIT Debug)
set(CMAKE_Fortran_FLAGS_INIT "/W1 /nologo /fpp ")
set(CMAKE_Fortran_FLAGS_DEBUG_INIT "/debug:full /Od /gen-interfaces /warn:interfaces /libs:dll /threads /c /dbglibs")
set(CMAKE_Fortran_FLAGS_MINSIZEREL_INIT "/O2 /D NDEBUG /gen-interfaces /warn:interfaces /libs:dll /threads /c")
set(CMAKE_Fortran_FLAGS_RELEASE_INIT "/MD /O1 /D NDEBUG /gen-interfaces /warn:interfaces /libs:dll /threads /c")
set(CMAKE_Fortran_FLAGS_RELWITHDEBINFO_INIT "/O1 /debug:full /D NDEBUG /gen-interfaces /warn:interfaces /libs:dll /threads /c")

set(CMAKE_Fortran_STANDARD_LIBRARIES_INIT "user32.lib")

# executable linker flags
set(CMAKE_LINK_DEF_FILE_FLAG "/DEF:")
set(CMAKE_EXE_LINKER_FLAGS_INIT " /INCREMENTAL:YES")

if(CMAKE_COMPILER_SUPPORTS_PDBTYPE)
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT "/debug /pdbtype:sept")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "/debug /pdbtype:sept")
else(CMAKE_COMPILER_SUPPORTS_PDBTYPE)
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT "/debug")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "/debug")
endif(CMAKE_COMPILER_SUPPORTS_PDBTYPE)

set(CMAKE_SHARED_LINKER_FLAGS_INIT ${CMAKE_EXE_LINKER_FLAGS_INIT})
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT ${CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT})
set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_INIT ${CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT})
set(CMAKE_MODULE_LINKER_FLAGS_INIT ${CMAKE_SHARED_LINKER_FLAGS_INIT})
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_INIT ${CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT})
set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_INIT ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT})

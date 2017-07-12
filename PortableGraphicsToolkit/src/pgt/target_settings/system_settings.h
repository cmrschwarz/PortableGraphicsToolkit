#pragma once
// Operating System
#define PGT_OS_WINDOWS true

// Endianness of Plattform
#define PGT_LITTLE_ENDIAN true
#define PGT_BIG_ENDIAN false


//Compiler
#define PGT_COMPILER_CLANG false
#define PGT_COMPILER_INTEL false
#define PGT_COMPILER_GNUCPP false
#define PGT_COMPILER_MSVC false
#define PGT_COMPILER_HP false
#define PGT_COMPILER_IBM false
#define PGT_COMPILER_PORTLAND false
#define PGT_COMPILER_SOLARIS false

#if defined(__clang__)
#undef PGT_COMPILER_CLANG
#define PGT_COMPILER_CLANG true

#elif defined(__ICC) || defined(__INTEL_COMPILER)
#undef PGT_COMPILER_INTEL
#define PGT_COMPILER_INTEL ftrue

#elif defined(__GNUC__) || defined(__GNUG__)
#undef PGT_COMPILER_GNUCPP
#define PGT_COMPILER_GNUCPP true

#elif defined(__HP_cc) || defined(__HP_aCC)
#undef PGT_COMPILER_HP
#define PGT_COMPILER_HP true

#elif defined(__IBMC__) || defined(__IBMCPP__)
#undef PGT_COMPILER_IBM
#define PGT_COMPILER_IBM true

#elif defined(_MSC_VER)
#undef PGT_COMPILER_MSVC
#define PGT_COMPILER_MSVC true

#elif defined(__PGI)
#undef PGT_COMPILER_PORTLAND
#define PGT_COMPILER_PORTLAND true

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#undef PGT_COMPILER_SOLARIS
#define PGT_COMPILER_SOLARIS true

#endif
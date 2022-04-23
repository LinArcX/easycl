#pragma once

#ifdef _MSC_VER

   #ifdef CL_EXPORTS
   #define CL_API __declspec(dllexport)
   #else
   #define CL_API __declspec(dllimport)
   #endif

   // cl.hpp needs a higher value for this (default value is 5)
   #define _VARIADIC_MAX 10

#else   // _MSC_VER

#define CL_API

#endif  // _MSC_VER


#include <assert.h>

typedef unsigned int uint;

//#define USE_CLFFT  // Uncomment to enable using clFFT library to compute Fast Fourrier Transform

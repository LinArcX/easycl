#include "preprocessor.h"

#include <CL/opencl.hpp>

#include "Image.h"

namespace OpenCLIPP
{

// SelectClType<T>, SET_CL_TYPE() and CL_TYPE() are used to find the proper type to use with cl::make_kernel
template<class T>
struct SelectClType
{
   typedef T Type;
};

#define SET_CL_TYPE(type, cl_type)\
   template<> struct SelectClType<type>\
   {   typedef cl_type Type; };\
   template<> struct SelectClType<const type>\
   {   typedef cl_type Type; };\
   template<> struct SelectClType<type&>\
   {   typedef cl_type Type; };\
   template<> struct SelectClType<const type&>\
   {   typedef cl_type Type; };

SET_CL_TYPE(IBuffer,     cl::Buffer)
SET_CL_TYPE(Buffer,      cl::Buffer)
SET_CL_TYPE(ReadBuffer,  cl::Buffer)
SET_CL_TYPE(TempBuffer,  cl::Buffer)
SET_CL_TYPE(Image,       cl::Buffer)
SET_CL_TYPE(TempImage,   cl::Buffer)


#define CL_TYPE(arg) SelectClType<decltype(arg)>::Type


// These macros are customizable to allow usage of the macro to call kernels that work differently
#ifndef SELECT_PROGRAM
#define SELECT_PROGRAM(...) SelectProgram(__VA_ARGS__)
#endif   // SELECT_PROGRAM

#ifndef SELECT_NAME
#define SELECT_NAME(name, src_img) #name
#endif   // SELECT_NAME

#ifndef KERNEL_RANGE
#define KERNEL_RANGE(...) _FIRST(__VA_ARGS__).FullRange()
#endif   // SELECT_NAME

#ifndef LOCAL_RANGE
#define LOCAL_RANGE     // Defaults to no local rage
#endif   // LOCAL_RANGE


// In and Out macros are used to mark the input and output of the kernels
// At least 1 input is needed, output may be empty : Out()
// The first input must be derived from ImageBase
#define In(...) __VA_ARGS__   ///< Used to mark inputs to a kernel
#define Out(...) __VA_ARGS__  ///< Used to mark outputs to a kernel


/// Simple kernel calling macro.
/// Usage : Kernel(name, In(Src1, Src2), Out(Dst), IntArg, FloatAgr);
#define Kernel(name, in, out, ...) Kernel_(*m_CL, SELECT_PROGRAM(in ADD_COMMA(out) out), name, KERNEL_RANGE(in ADD_COMMA(out) out), LOCAL_RANGE, In(in), Out(out), __VA_ARGS__)


// Helpers
#define _SEND_IF_NEEDED(img) (img).SendIfNeeded();
#define _SET_IN_DEVICE(img) (img).SetInDevice();
#define _FIRST(in, ...) REMOVE_PAREN(SELECT_FIRST, (in))

/// More generic kernel calling macro.
/// Example usage : Kernel_(CL, ArithmeticProgram, "Add", Src1.FullRange(), cl::NDRange(16, 16, 1), In(Src1, Src2), Out(Dst), Arg1, Arg2);
#define Kernel_(CL, program, name, global_range, local_range, in, out, ...)\
   FOR_EACH(_SEND_IF_NEEDED, in)\
   cl::compatibility::make_kernel<FOR_EACH_COMMA(CL_TYPE, in) ADD_COMMA(out) FOR_EACH_COMMA(CL_TYPE, out) ADD_COMMA(__VA_ARGS__) FOR_EACH_COMMA(CL_TYPE, __VA_ARGS__)>\
      ((cl::Program) program, SELECT_NAME(name, _FIRST(in)))\
         (cl::EnqueueArgs(CL, global_range ADD_COMMA(local_range) local_range),\
            in ADD_COMMA(out) out ADD_COMMA(__VA_ARGS__) __VA_ARGS__);\
   FOR_EACH(_SET_IN_DEVICE, out)

}

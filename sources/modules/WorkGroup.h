#include "Image.h"

#ifndef PIXELS_PER_WORKITEM_H
#define PIXELS_PER_WORKITEM_H   1
#endif

#ifndef PIXELS_PER_WORKITEM_V
#define PIXELS_PER_WORKITEM_V   1
#endif

#ifndef LOCAL_WIDTH
#define LOCAL_WIDTH 16
#endif

#ifndef LOCAL_HEIGHT
#define LOCAL_HEIGHT LOCAL_WIDTH
#endif

// Disable warning about unused static functions
// We need these functions to be static because they use these static global variables
// But not every .cpp file that uses this .h file uses all the functions so we get unused static functions, which flags a warning
#ifdef _MSC_VER
#pragma warning ( disable : 4505 )
#else
#pragma GCC diagnostic ignored "-Wunused-function"
#endif


namespace OpenCLIPP
{

const static int GroupWidth = LOCAL_WIDTH;                        // Width of a workgroup
const static int GroupHeight = LOCAL_HEIGHT;                      // Height of a workgroup
const static int PixelsPerWorkerH = PIXELS_PER_WORKITEM_H;        // Number of pixels along x processed per workitem
const static int PixelsPerWorkerV = PIXELS_PER_WORKITEM_V;        // Number of pixels along y processed per workitem
const static int GroupPxWidth = GroupWidth * PixelsPerWorkerH;    // Number of pixels that 1 workgroup will process one 1 row
const static int GroupPxHeight = GroupHeight * PixelsPerWorkerV;  // Number of pixels that 1 workgroup will process one 1 column

static bool FlushWidth(const ImageBase& Img);      // Is Width a multiple of GroupWidth*PixelsPerWorker
static bool FlushHeight(const ImageBase& Img);     // Is Height a multiple of GroupHeight
static bool IsFlushImage(const ImageBase& Img);    // Are both Width and Height flush

static uint GetNbWorkersW(const ImageBase& Img);   // Number of work items to be launched for each row of the image, including inactive work items
static uint GetNbWorkersH(const ImageBase& Img);   // Number of work items to be launched for each column of the image, including inactive work items

static uint GetNbGroupsW(const ImageBase& Img);    // Number of work groups along X
static uint GetNbGroupsH(const ImageBase& Img);    // Number of work groups along Y

static cl::NDRange GetRange(const ImageBase& Img, bool UseLocalSize = true);   // Global range for the image - GetNbWorkersW() * GetNbWorkersH()
static cl::NDRange GetLocalRange(bool UseLocalSize = true);                      // Local range - GroupWidth * GroupHeight

static uint GetNbGroups(const ImageBase& Img);     // Number of work groups for the image - GetNbGroupsW() * GetNbGroupsH()

// Equivalent of the Kernel() macro but using the
#define Kernel_Local(name, in, out, ...) \
   Kernel_(*m_CL, SELECT_PROGRAM(_FIRST(in)), name, \
      GetRange(_FIRST(in)), GetLocalRange(), \
      In(in), Out(out), __VA_ARGS__ )


static bool FlushWidth(const ImageBase& Img)
{
   if (Img.Width() % GroupPxWidth > 0)
      return false;

   return true;
}

static bool FlushHeight(const ImageBase& Img)
{
   if (Img.Height() % GroupPxHeight > 0)
      return false;

   return true;
}

static bool IsFlushImage(const ImageBase& Img)
{
   return FlushWidth(Img) && FlushHeight(Img);
}

static uint GetNbWorkersW(const ImageBase& Img)
{
   uint Nb = Img.Width() / GroupPxWidth * GroupWidth;
   if (!FlushWidth(Img))
      Nb += GroupWidth;

   return Nb;
}

static uint GetNbWorkersH(const ImageBase& Img)
{
   uint Nb = Img.Height() / GroupPxHeight * GroupHeight;
   if (!FlushHeight(Img))
      Nb += GroupHeight;

   return Nb;
}

static uint GetNbGroupsW(const ImageBase& Img)
{
   return GetNbWorkersW(Img) / GroupWidth;
}

static uint GetNbGroupsH(const ImageBase& Img)
{
   return GetNbWorkersH(Img) / GroupHeight;
}

static cl::NDRange GetRange(const ImageBase& Img, bool UseLocalSize)
{
   if (UseLocalSize)
      return cl::NDRange(GetNbWorkersW(Img), GetNbWorkersH(Img), 1);

   return cl::NDRange(Img.Width() / PixelsPerWorkerH, Img.Height() / PixelsPerWorkerV, 1);
}

static cl::NDRange GetLocalRange(bool UseLocalSize)
{
   if (UseLocalSize)
      return cl::NDRange(GroupWidth, GroupHeight, 1);

   return cl::NullRange;
}

static uint GetNbGroups(const ImageBase& Img)
{
   return GetNbGroupsW(Img) * GetNbGroupsH(Img);
}

}

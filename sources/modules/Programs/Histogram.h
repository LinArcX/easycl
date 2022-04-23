#pragma once

#include "Program.h"

namespace OpenCLIPP
{

/// A program that calculates the Histogram of an image
class CL_API Histogram : public ImageProgram
{
public:
   Histogram(COpenCL& CL)
   :  ImageProgram(CL, "Histogram.cl")
   { }

   /// Calculates the Histogram of the first channel of the image
   /// \param Histogram : Array of 256 elements that will receive the histogram values
   void Histogram1C(Image& Source, uint * Histogram);

   /// Calculates the Histogram of all channels of the image
   /// \param Histogram : Array of 1024 elements that will receive the histogram values
   void Histogram4C(Image& Source, uint * Histogram);

   /// Calculates the Otsu threshold given an histogram
   static uint OtsuThreshold(uint Histogram[256], uint NbPixels);

   /// Calculates the Otsu threshold for the image
   uint OtsuThreshold(Image& Source);
};

}

#pragma once

#include "Program.h"

namespace OpenCLIPP
{

/// A program for convolution-type filters on images
class CL_API Filters : public ImageProgram
{
public:
   Filters(COpenCL& CL)
   :  ImageProgram(CL, "Filters.cl")
   { }

   /// Gaussian blur filter.
   /// \param Sigma : Intensity of the filer - Allowed values : 0.01-10
   void GaussianBlur(Image& Source, Image& Dest, float Sigma);

   /// Gaussian filter.
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Gauss(Image& Source, Image& Dest, int Width);

   /// Sharpen filter.
   /// \param Width : Width of the filter box - Allowed values : 3
   void Sharpen(Image& Source, Image& Dest, int Width = 3);

   /// Smooth filter - or Box filter.
   /// \param Width : Width of the filter box - Allowed values : Impair & >=3
   void Smooth(Image& Source, Image& Dest, int Width = 3);

   /// Median filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Median(Image& Source, Image& Dest, int Width = 3);

   /// Vertical Sobel filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void SobelVert(Image& Source, Image& Dest, int Width = 3);

   /// Horizontal Sobel filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void SobelHoriz(Image& Source, Image& Dest, int Width = 3);

   /// Cross Sobel filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void SobelCross(Image& Source, Image& Dest, int Width = 3);

   /// Combined Sobel filter
   /// Does SobelVert & SobelHoriz and the combines the two with sqrt(V*V + H*H)
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Sobel(Image& Source, Image& Dest, int Width = 3);

   /// Vertical Prewitt filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void PrewittVert(Image& Source, Image& Dest, int Width = 3);

   /// Horizontal Prewitt filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void PrewittHoriz(Image& Source, Image& Dest, int Width = 3);

   /// Combined Prewitt filter
   /// Does PrewittVert & PrewittHoriz and the combines the two with sqrt(V*V + H*H)
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Prewitt(Image& Source, Image& Dest, int Width = 3);

   /// Vertical Scharr filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void ScharrVert(Image& Source, Image& Dest, int Width = 3);

   /// Horizontal Scharr filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void ScharrHoriz(Image& Source, Image& Dest, int Width = 3);

   /// Combined Scharr filter
   /// Does ScharrVert & ScharrHoriz and the combines the two with sqrt(V*V + H*H)
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Scharr(Image& Source, Image& Dest, int Width = 3);

   /// Hipass filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Hipass(Image& Source, Image& Dest, int Width = 3);

   /// Laplace filter
   /// \param Width : Width of the filter box - Allowed values : 3 or 5
   void Laplace(Image& Source, Image& Dest, int Width = 5);
};

}

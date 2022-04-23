#include "modules/OpenCL.h"
#include "modules/Buffer.h"
#include "modules/Image.h"
#include "modules/Program.h"
#include "modules/Transform.h"
#include "modules/Filters.h"

#include "lodepng/lodepng.h"

using namespace std;
using namespace OpenCLIPP;

uint CalculateStep(const SImage& Img);

int main(int argc, char ** argv)
{
   string FileName = "original.png";
   SImage ImageInfo;
   vector<unsigned char> SourceData, ResultData;

   unsigned Status = lodepng::decode(SourceData, ImageInfo.Width, ImageInfo.Height, FileName, LCT_RGB);

   if (0 == Status)
   {
      ImageInfo.Channels = 3;
      ImageInfo.Type = SImage::U8;
      ImageInfo.Step = CalculateStep(ImageInfo);
   }
   else
   {
      printf("Unable to open file original.png - using empty image\n");
      ImageInfo.Channels = 3;
      ImageInfo.Type = SImage::U8;
      ImageInfo.Width = 512;
      ImageInfo.Height = 512;
      ImageInfo.Step = CalculateStep(ImageInfo);
      SourceData.resize(ImageInfo.Height * ImageInfo.Step);
   }
   ResultData.resize(SourceData.size());

   //// Initialize OpenCL
   COpenCL CL;
   CL.SetClFilesPath("/mnt/D/workspace/c++/projects/easycl/sources/cl-files/");
   Filters Filters(CL);

   // Display device name
   string Name = CL.GetDeviceName();
   printf("Using device : %s\n", Name.c_str());

   // Create images in OpenCL device
   ColorImage SourceImage(CL, ImageInfo, SourceData.data());
   ColorImage ResultImage(CL, ImageInfo, ResultData.data());

   SourceImage.Send();   // Optional : Sends image to device memory - would be done automatically

   // Execute filter
   Filters.Sobel(SourceImage, ResultImage);

   // Read image to main memory
   ResultImage.Read(true);

   // Save image to new file
   string ResultName = "result.png";
   lodepng::encode(ResultName, ResultData, ImageInfo.Width, ImageInfo.Height, LCT_RGB);

   printf("Success\n");
   return 0;
}

uint CalculateStep(const SImage& Img)
{
   uint Depth = 4;
   if (Img.Type < SImage::U16)
      Depth = 1;
   else if (Img.Type < SImage::U32)
      Depth = 2;

   return Img.Width * Img.Channels * Depth;
}

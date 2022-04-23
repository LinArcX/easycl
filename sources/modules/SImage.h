#ifndef __SIMAGE__H
#define __SIMAGE__H

typedef	unsigned int		uint;

struct SImage
{
   uint Width;    ///< Width of the image, in pixels
   uint Height;   ///< Height of the image, in pixels
   uint Step;     ///< Nb of bytes between each row
   uint Channels; ///< Number of channels in the image, allowed values : 1, 2, 3 or 4

   /// EDataType : Lists possible types of data
   enum EDataType
   {
      U8,            /// Unsigned 8-bit integer (unsigned char)
      S8,            /// Signed 8-bit integer (char)
      U16,           /// Unsigned 16-bit integer (unsigned short)
      S16,           /// Signed 16-bit integer (short)
      U32,           /// Unsigned 32-bit integer (unsigned int)
      S32,           /// Signed 32-bit integer (int)
      F32,           /// 32-bit floating point (float)
      F64,           /// 64-bit floating point (double)
      NbDataTypes,   /// Number of possible data types
   } Type;  ///< Data type of each channel in the image
};

#endif   // __SIMAGE__H

#pragma once

#include "Program.h"

namespace OpenCLIPP
{

/// A program that does Arithmetic operations
class CL_API Arithmetic : public VectorProgram
{
public:
   Arithmetic(COpenCL& CL)
      :  VectorProgram(CL, "Arithmetic.cl")
   { }


   // Between two images
   void Add(Image& Source1, Image& Source2, Image& Dest);         ///< D = S1 + S2
   void AddSquare(Image& Source1, Image& Source2, Image& Dest);   ///< D = S1 + S2 * S2
   void Sub(Image& Source1, Image& Source2, Image& Dest);         ///< D = S1 - S2
   void AbsDiff(Image& Source1, Image& Source2, Image& Dest);     ///< D = abs(S1 - S2)
   void Mul(Image& Source1, Image& Source2, Image& Dest);         ///< D = S1 * S2
   void Div(Image& Source1, Image& Source2, Image& Dest);         ///< D = S1 / S2
   void Min(Image& Source1, Image& Source2, Image& Dest);         ///< D = min(S1, S2)
   void Max(Image& Source1, Image& Source2, Image& Dest);         ///< D = max(S1, S1)
   void Mean(Image& Source1, Image& Source2, Image& Dest);        ///< D = (S1 + S2) / 2
   void Combine(Image& Source1, Image& Source2, Image& Dest);     ///< D = sqrt(S1 * S1 + S2 * S2)

   // Image and value
   void Add(Image& Source, Image& Dest, float value);       ///< D = S + v
   void Sub(Image& Source, Image& Dest, float value);       ///< D = S - v
   void AbsDiff(Image& Source, Image& Dest, float value);   ///< D = abs(S - v)
   void Mul(Image& Source, Image& Dest, float value);       ///< D = S * v
   void Div(Image& Source, Image& Dest, float value);       ///< D = S / v
   void RevDiv(Image& Source, Image& Dest, float value);    ///< D = v / S
   void Min(Image& Source, Image& Dest, float value);       ///< D = min(S, v)
   void Max(Image& Source, Image& Dest, float value);       ///< D = max(S, v)
   void Mean(Image& Source, Image& Dest, float value);      ///< D = (S + V) / 2

   // Calculation on one image
   void Abs(Image& Source, Image& Dest);     ///< D = abs(S)
   void Invert(Image& Source, Image& Dest);  ///< D = 255 - S
   void Sqr(Image& Source, Image& Dest);     ///< D = S * S

   // Calculation on one image - float required
   void Exp(Image& Source, Image& Dest);     ///< D = exp(S)
   void Log(Image& Source, Image& Dest);     ///< D = log(S)
   void Sqrt(Image& Source, Image& Dest);    ///< D = sqrt(S)
   void Sin(Image& Source, Image& Dest);     ///< D = sin(S)
   void Cos(Image& Source, Image& Dest);     ///< D = cos(S)

};

}

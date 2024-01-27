/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below

  img=inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
   HSLAPixel t= *img.getPixel(  p.x,p.y);
  auto ans=t;
   ans.l=1-ans.l;
   ans.h=(double)(((int)ans.h+180)%360);
   return ans;
}

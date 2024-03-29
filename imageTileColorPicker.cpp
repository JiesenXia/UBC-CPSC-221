/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  // complete your implementation below
  img_other=otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  // complete your implementation below
  unsigned int x=img_other.height();
  unsigned int y=img_other.width();
  unsigned int bx=p.x,by=p.y;
  // std::cout<<bx%x<<"  "<<by%y<<std::endl;
  
  return *img_other.getPixel(bx%y,by%x); 

}
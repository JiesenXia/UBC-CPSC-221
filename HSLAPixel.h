#ifndef CS221_HSLAPIXEL_H
#define CS221_HSLAPIXEL_H


namespace cs221util {
    class HSLAPixel {
        public: 
                double h,s,l,a;
                HSLAPixel();
                HSLAPixel(double hue, double sat, double lum);
                HSLAPixel(double hue, double sat, double lum, double alp);
    };
} 

#endif
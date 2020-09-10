/*


*/
#ifndef __INCLUDE_GURD_Cube__
#define __INCLUDE_GURD_Cube__

#include <iostream>
#include <vector>
#include "TObject.h"

class Cube : public TObject
{
	public:
	Cube();
	Cube(int id, 
        float surf1_xs, float surf1_ys, float surf1_xh, float surf1_yh, float surf1_r,
        float surf2_xs, float surf2_ys, float surf2_xh, float surf2_yh, float surf2_r,
        float surf3_xs, float surf3_ys, float surf3_xh, float surf3_yh, float surf3_r,
        float surf4_xs, float surf4_ys, float surf4_xh, float surf4_yh, float surf4_r,
        float surf5_xs, float surf5_ys, float surf5_xh, float surf5_yh, float surf5_r,
        float surf6_xs, float surf6_ys, float surf6_xh, float surf6_yh, float surf6_r 
        );

    virtual ~Cube();

    inline void SetSurf1(float a, float b) {
   	    _surf1_xs = a;
        _surf1_ys = b;
    }

    inline void GetInfoSurf1() {
        std::cerr << "call: GetInfoSurf1()" << std::endl;
   	    std::cerr << " _surf1_xs = " << _surf1_xs
                  << " _surf1_ys= " << _surf1_ys << std::endl;
    }

    void GetSurf1(float parlist[5]);
    void GetSurf2(float parlist[5]);
    void GetSurf3(float parlist[5]);
    void GetSurf4(float parlist[5]);
    void GetSurf5(float parlist[5]);
    void GetSurf6(float parlist[5]);

    void CubeArrange1(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 


    void CubeArrange2(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 

	private:
   int _id;
   float _surf1_xs;
   float _surf1_ys;
   float _surf1_xh;
   float _surf1_yh;
   float _surf1_r;

   float _surf2_xs;
   float _surf2_ys;
   float _surf2_xh;
   float _surf2_yh;
   float _surf2_r;

   float _surf3_xs;
   float _surf3_ys;
   float _surf3_xh;
   float _surf3_yh;
   float _surf3_r;

   float _surf4_xs;
   float _surf4_ys;
   float _surf4_xh;
   float _surf4_yh;
   float _surf4_r;

   float _surf5_xs;
   float _surf5_ys;
   float _surf5_xh;
   float _surf5_yh;
   float _surf5_r;

   float _surf6_xs;
   float _surf6_ys;
   float _surf6_xh;
   float _surf6_yh;
   float _surf6_r;

   // in .C macro, I'm not sure the reason
   //       -> Error in <Streamer>: Cannot stream interpreted class.
   ClassDef(Cube, 1)  // Raw Data class
};
#endif

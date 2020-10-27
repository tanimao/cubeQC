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
           float height, float width, float depth,
           float xhole14, float yhole14,
           float xhole25, float yhole25,
           float xhole36, float yhole36,
           float r1, float r2, float r3, float r4, float r5, float r6
        );

    virtual ~Cube();

//    inline void SetSurf1(float a, float b) {
//   	    _surf1_xs = a;
 //       _surf1_ys = b;
 //   }

    inline void GetInfoSurf1() {
        //std::cerr << "call: GetInfoSurf1()" << std::endl;
   	    //std::cerr << " _surf1_xs = " << _surf1_xs
          //        << " _surf1_ys= " << _surf1_ys << std::endl;
    }

    void GetSize  (float size3D[3]);
    void GetHole14(float holexy[2]);
    void GetHole25(float holexy[2]);
    void GetHole36(float holexy[2]);
    void GetRadius(float radius[6]);

    void CubeArrangey1(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 


    void CubeArrangey2(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 


    void CubeArrangex1(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 


    void CubeArrangex2(Cube *c1, Cube *c2, Cube *c3, Cube *c4, 
                      Cube *c5, Cube *c6, Cube *c7, Cube *c8,
                      float * hole[8], float *fibarea[8], 
                      float *sizemax); 
	private:
   int _id;
   float _height;
   float _width;
   float _depth;

   float _xhole14;
   float _yhole14;
   float _xhole25;
   float _yhole25;
   float _xhole36;
   float _yhole36;

   float _r1, _r2, _r3, _r4, _r5, _r6;
   
   // in .C macro, I'm not sure the reason
   //       -> Error in <Streamer>: Cannot stream interpreted class.
   ClassDef(Cube, 1)  // Raw Data class
};
#endif

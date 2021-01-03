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
           float xhole0, float yhole0,
           float xhole1, float yhole1,
           float xhole2, float yhole2,
           float xhole3, float yhole3,
           float xhole4, float yhole4,
           float xhole5, float yhole5,
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

    void GetId    ( int      id   );
    void GetSize  (float size3D[3]);
    void GetHole14(float holexy[2]);
    void GetHole25(float holexy[2]);
    void GetHole36(float holexy[2]);
    void GetRadius(float radius[6]);

    void GetHole0 (float holexy[2]);
    void GetHole1 (float holexy[2]);
    void GetHole2 (float holexy[2]);
    void GetHole3 (float holexy[2]);
    void GetHole4 (float holexy[2]);
    void GetHole5 (float holexy[2]);

    //向かい合う面の穴位置のずれを記録する
    void Fill_fdhxy(Cube *c, TH1F * h);

    //穴の位置が最も平均に近いものが天面に来るように
    //キューブの向きを変える
    void ChangeCubeDirection(Cube * c, float xhMean, float yhMean, TH1F * h, TH1F * hmin);


    //X1,Y1,X2,Y2の値に応じてカテゴリのindexを出力する
    void CheckCategory(float X1, float Y1, float X2, float Y2, float factor, 
                       float SDevX1, float SDevX2, int * icategory);
    //生の穴位置(x,y)をフィルする
    void FillCenter1(Cube * c, TH2F * h);
    void FillCenter2(Cube * c, TH2F * h);

    //回転と平行移動で原点周りに移動させた点(X,Y)をフィルする
    void FillCenterXY1(Cube * c, TH2F * h, TH1F * hx, TH1F * hy, 
                       float x0, float y0, float p1);
    void FillCenterXY2(Cube * c, TH2F * h, TH1F * hx, TH1F * hy,
                       float x0, float y0, float p1);

    void FillCenterXYXY1(Cube * c, TH2F * h, float X0, float Y0, float q1,
                                             float x0, float y0, float p1);
    void FillCenterXYXY2(Cube * c, TH2F * h, float X0, float Y0, float q1,
                                             float x0, float y0, float p1);
    
    //2Dヒストグラムを直線フィットして、十字に切る直線を得る
    void GetPols(TH2F * h, float p[2][2]);
    void ArrangebyHole (Cube *c, float x, float y, float *posxhx[6], float *posxhy[6]);
//    void RotateCube(float x, float y, float *posxhx[6], float *posxhy[6], float tan);
//
    void RotateCube(Cube *c, float x, float y, float *posxhx[6], float *posxhy[6], float tan);
    void ROtateCubeFull(float x, float y, float *posxhx[6], float *posxhy[6], float tan);
    void checkdiff (TH1F * hist, 
            float posxhx[8][8][6], float posxhy[8][8][6], float posxhz[8][8][6], int cannot);


    void RotateEachCube(float x, float y, float *posxhx[6], float *posxhy[6]);


    void FillDiffy (TH1F * hist, TH1F * hist2, int &num_over, TH2F * hpos, 
            float posxhx[8][8][6], float posxhy[8][8][6], float posxhz[8][8][6], 
            int cannot, float pitch, int shuff);
    void FillDiffx (TH1F * hist, TH1F * hist2, int &num_over, TH2F * hpos,
            float posxhx[8][8][6], float posxhy[8][8][6], float posxhz[8][8][6], 
            int cannot, float pitch);
    
    void GetRawEllipse1(Cube * c, float x, float y);
    void GetRawEllipse2(Cube * c, float x, float y);
    //回転と平行移動で原点周りに移動させた点(X,Y)を得る関数。
    //他の関数から参照するやつ

    void GetEllipse1(Cube * c, float x0, float y0, float p1, float &X, float &Y);
    void GetEllipse2(Cube * c, float x0, float y0, float p1, float &X, float &Y);

    //楕円の条件でキューブを選別する
    int EllipseCut1(Cube * c, float a, float b, float x0, float y0, float p1);
    int EllipseCut2(Cube * c, float a, float b, float x0, float y0, float p1);
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

   float _xhole0;
   float _yhole0;
   float _xhole1;
   float _yhole1;
   float _xhole2;
   float _yhole2;
   float _xhole3;
   float _yhole3;
   float _xhole4;
   float _yhole4;
   float _xhole5;
   float _yhole5;

   float _r1, _r2, _r3, _r4, _r5, _r6;
   
   // in .C macro, I'm not sure the reason
   //       -> Error in <Streamer>: Cannot stream interpreted class.
   ClassDef(Cube, 1)  // Raw Data class
};
#endif

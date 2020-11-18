#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

void macro_forrangeif(){

TFile *fin     = new TFile("201102.root", "read");
//TFile *finbad  = new TFile("0828bad0831cor.root","read");
TTree *tree    = (TTree*)fin->Get("tree");
//TTree *treebad = (TTree*)finbad->Get("tree");

TH1D* h1 = new TH1D("h1","radius",100,45,55); 
TH1D* h2 = new TH1D("h2","xhole_max",100,140,220); 
TH1D* h3 = new TH1D("h3","yhole_max",100,140,220); 
TH1D* h4 = new TH1D("h4","xsize_max",100,640,680); 
TH1D* h5 = new TH1D("h5","ysize_max",100,640,680); 
TH1D* hd = new TH1D("hd","distance",100,0,100);
TH1D* hb = new TH1D("hb","bump",100,0,1000); 
TH1D* hE = new TH1D("hE","Esum",1000,0,500); 

TH1D* h1all = new TH1D("h1all","radius",100,45,55); 
TH1D* h2all = new TH1D("h2all","xhole_max",100,140,220); 
TH1D* h3all = new TH1D("h3all","yhole_max",100,140,220); 
TH1D* h4all = new TH1D("h4all","xsize_max",100,640*0.01554,680*0.01554); 
TH1D* h5all = new TH1D("h5all","ysize_max",100,640*0.01554,680*0.01554); 
TH1D* hball = new TH1D("hball","bump",100,0,1000); 
TH1D* hEall = new TH1D("hEall","Esum",1000,0,500); 

TH1D* holexy= new TH1D("holexy","sqrt(xhole^2+yhole^2)", 100, 220*0.01554,300*0.01554);
TH1D* holexy1= new TH1D("holexy1","abs(facing sqrt(xhole^2+yhole^2))", 100, 0 ,0.5);

TH1D* h1six = new TH1D("h1six","radius",100,45,55); 
TH1D* h2six = new TH1D("h2six","xhole_max",100,140*0.01554,220*0.01554); 
TH1D* h3six = new TH1D("h3six","yhole_max",100,140*0.01554,220*0.01554); 
TH1D* h4six = new TH1D("h4six","xsize_max",100,640*0.01554,680*0.01554); 
TH1D* h5six = new TH1D("h5six","ysize_max",100,640*0.01554,680*0.01554); 
TH1D* hdsix = new TH1D("hdsix","distance",100,0,100); 
TH1D* hbsix = new TH1D("hbsix","bump",100,0,1000); 
TH1D* hEsix = new TH1D("hEsix","Esum",1000,0,500); 



TH1D* h1b = new TH1D("h1b","radius",100,45,55); 
TH1D* h2b = new TH1D("h2b","xhole_max",100,140,220); 
TH1D* h3b = new TH1D("h3b","yhole_max",100,140,220); 
TH1D* h4b = new TH1D("h4b","xsize_max",100,640,680); 
TH1D* h5b = new TH1D("h5b","ysize_max",100,640,680); 
TH1D* hbb = new TH1D("hbb","bump",100,0,1000); 
TH1D* hEb = new TH1D("hEb","Esum",1000,0,500); 

//大きさと穴位置の相関を見るための2Dヒストグラム
//
TH2D * xsxhMax = new TH2D ("xsxhMax", "xsize_xhole; xsize [mm]; xhole [mm]",
                        100, 640, 680, 100, 140, 220);
TH2D * xsyhMax = new TH2D ("xsyhMax", "xsize_yhole; xsize [mm]; yhole [mm]",
                        100, 640, 680, 100, 140, 220);
TH2D * ysxhMax = new TH2D ("ysxhMax", "ysize_xhole; ysize [mm]; xhole [mm]",
                        100, 640, 680, 100, 140, 220);
TH2D * ysyhMax = new TH2D ("ysyhMax", "ysize_yhole; ysize [mm]; yhole [mm]",
                        100, 640, 680, 100, 140, 220);
TH2D * xsysMax = new TH2D ("xsysMax", "xsize_ysize; xsize [mm]; ysize [mm]",
                        100, 640, 680, 100, 640, 680);
TH2D * xhyhMax = new TH2D ("xhyhMax", "xhole_yhole; xhole [mm]; yhole [mm]",
                        100, 140, 220, 100, 140, 220);


TH2D * xsxh= new TH2D ("xsxh", "xsize_xhole; xsize [mm]; xhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * xsyh= new TH2D ("xsyh", "xsize_yhole; xsize [mm]; yhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * ysxh= new TH2D ("ysxh", "ysize_xhole; ysize [mm]; xhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * ysyh= new TH2D ("ysyh", "ysize_yhole; ysize [mm]; yhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * xsys= new TH2D ("xsys", "xsize_ysize; xsize [mm]; ysize [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*640, 0.01554*680);
TH2D * xhyh= new TH2D ("xhyh", "xhole_yhole; xhole [mm]; yhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);







//向かい合う面での相関
TH2D * fxsxs= new TH2D ("fxsxs", "facing xsize_xsize; xsize [mm]; xsize [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*640, 0.01554*680);
TH2D * fxsys= new TH2D ("fxsys", "facing xsize_ysize; xsize [mm]; ysize [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*640, 0.01554*680);
TH2D * fysys= new TH2D ("fysys", "facing ysize_ysize; ysize [mm]; ysize [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*640, 0.01554*680);

TH2D * fxhxh= new TH2D ("fxhxh", "facing xhole_xhole; xhole [mm]; xhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fxhyh= new TH2D ("fxhyh", "facing xhole_yhole; xhole [mm]; yhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fyhyh= new TH2D ("fyhyh", "facing yhole_yhole; yhole [mm]; yhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fholexy= new TH2D ("fholexy", "facing sqrt(xhole^2+yhole^2); holexy [mm]; holexy [mm]",
                        100, 0.01554*220, 0.01554*300, 100, 0.01554*220, 0.01554*300);

TH2D * fxhxh_half1= new TH2D ("fxhxh_half1", "facing xhole_xhole; xhole [mm]; xhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fyhyh_half1= new TH2D ("fyhyh_half1", "facing yhole_yhole; yhole [mm]; yhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fxhxh_half2= new TH2D ("fxhxh_half2", "facing xhole_xhole; xhole [mm]; xhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);
TH2D * fyhyh_half2= new TH2D ("fyhyh_half2", "facing yhole_yhole; yhole [mm]; yhole [mm]",
                        100, 0.01554*140, 0.01554*220, 100, 0.01554*140, 0.01554*220);




TH2D * fxsxh= new TH2D ("fxsxh", "facing xsize_xhole; xsize [mm]; xhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * fxsyh= new TH2D ("fxsyh", "facing xsize_yhole; xsize [mm]; yhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * fysxh= new TH2D ("fysxh", "facing ysize_xhole; ysize [mm]; xhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);
TH2D * fysyh= new TH2D ("fysyh", "facing ysize_yhole; ysize [mm]; yhole [mm]",
                        100, 0.01554*640, 0.01554*680, 100, 0.01554*140, 0.01554*220);



TH1D * hist_h = new TH1D("hist_h", "hist_h", 100, 640*0.01554, 680*0.01554);
TH1D * hist_w = new TH1D("hist_w", "hist_w", 100, 640*0.01554, 680*0.01554);
TH1D * hist_d = new TH1D("hist_d", "hist_d", 100, 640*0.01554, 680*0.01554);

TH1D * sub_hw = new TH1D("sub_hw", "sub_hw", 100, 640*0.01554, 680*0.01554);
TH1D * sub_hd = new TH1D("sub_hd", "sub_hd", 100, 640*0.01554, 680*0.01554);
TH1D * sub_wd = new TH1D("sub_wd", "sub_wd", 100, 640*0.01554, 680*0.01554);


TH2D * sizexy= new TH2D ("sizexy", "height, width ; height; width",
                        100,640,680, 100,640,680);
TH2D * sizexz= new TH2D ("sizexz", "height, depth ; height; depth",
                        100,640,680, 100,640,680);
TH2D * sizeyz= new TH2D ("sizeyz", "width, depth ; width; depth",
                        100,640,680, 100,640,680);

TH3D * sizexyz= new TH3D ("sizexyz", "height, width, depth; height; width; depth",
                        100,640,680, 100,640,680, 100,640,680);

//サイズヒストグラムの領域ごとに、穴位置ヒストグラムを８個に分ける。

TH2D * hole1 = new TH2D ("hole1", "hole1 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole2 = new TH2D ("hole2", "hole2 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole3 = new TH2D ("hole3", "hole3 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole4 = new TH2D ("hole4", "hole4 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole5 = new TH2D ("hole5", "hole5 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole6 = new TH2D ("hole6", "hole6 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole7 = new TH2D ("hole7", "hole7 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);
TH2D * hole8 = new TH2D ("hole8", "hole8 ;xhole; yhole", 
                        100, 140, 220, 100, 140, 220);



//テスト。隣あう面について相関を見てみる。
TH2D * sizex2y1= new TH2D ("sizex2y1", "height ; height(xsize2); height(ysize1)",
                        100,640,680, 100,640,680);
TH2D * sizex1y3= new TH2D ("sizex1y3", "width ; width(xsize1); width(ysize3)",
                        100,640,680, 100,640,680);
Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t Esum[n];
Double_t bump[n];


Double_t radiusbad[n];
Double_t xholebad[n];
Double_t yholebad[n];
Double_t xsizebad[n];
Double_t ysizebad[n];
Double_t Esumbad[n];
Double_t bumpbad[n];


Double_t radiabs;
Double_t xholeabs;
Double_t yholeabs;
Double_t xsizeabs;
Double_t ysizeabs;

/*
///0827goodcor.rootから持ってきた平均値
Double_t rMean  = 49.39;
Double_t xsMean = 657.3;
Double_t ysMean = 656.5;
Double_t xhMean = 187.1;
Double_t yhMean = 190.8;
*/

///2009010905から持ってきた平均値
Double_t rMean  = 49.11;
Double_t xsMean = 659.2;
Double_t ysMean = 659.2;
Double_t xhMean = 185.8;
Double_t yhMean = 185.9;



Double_t rMax;
Double_t xsMax;
Double_t ysMax;
Double_t xhMax;
Double_t yhMax;
Double_t bMax;
Double_t EMax;

Double_t height;
Double_t width;
Double_t depth;

Double_t xhole14;
Double_t yhole14;
Double_t xhole25;
Double_t yhole25;
Double_t xhole36;
Double_t yhole36;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum", Esum);
tree->SetBranchAddress("bump", bump);


//treebad->SetBranchAddress("radius", radiusbad);
//treebad->SetBranchAddress("xhole", xholebad);
//treebad->SetBranchAddress("yhole", yholebad);
//treebad->SetBranchAddress("xsize", xsizebad);
//treebad->SetBranchAddress("ysize", ysizebad);
//treebad->SetBranchAddress("Esum", Esumbad);
//treebad->SetBranchAddress("bump", bumpbad);



int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );
//    treebad->GetEntry( ientry );
    //std::cout << xhole[1] << std::endl;

    //平均値からの距離maxをfillする
    radiabs  = fabs(radius[0]-rMean);
    xholeabs = fabs(xhole[0]-xhMean);
    yholeabs = fabs(yhole[0]-yhMean);
    xsizeabs = fabs(xsize[0]-xsMean);
    ysizeabs = fabs(ysize[0]-ysMean);
    

    rMax  = radius[0];
    xhMax = xhole[0];
    yhMax = yhole[0];
    xsMax = xsize[0];
    ysMax = ysize[0];
    bMax = bump[0];
    EMax = Esum[0];

    // キューブの高さ、幅、奥行きをfill
    height = (ysize[0] + xsize[1] + ysize[3] + xsize[4])/4; // 高さ
    width  = (xsize[0] + ysize[2] + xsize[3] + ysize[5])/4;// 幅
    depth  = (ysize[1] + xsize[2] + ysize[4] + xsize[5])/4;// 奥行き

    hist_h->Fill(height*0.01554);
    hist_w->Fill(width *0.01554);
    hist_d->Fill(depth *0.01554);

    sub_hw->Fill(height*0.01554 - width *0.01554);
    sub_hd->Fill(height*0.01554 - depth *0.01554);
    sub_wd->Fill(width *0.01554 - depth *0.01554);
    
    sizexy->Fill(height,// 高さ
                  width);// 幅
    
    sizexz->Fill(height, // 高さ
                  depth);// 奥行き
    
    sizeyz->Fill(width, // 幅
                 depth); // 奥行き

    sizexyz->Fill(height, // 高さ
                  width, // 幅
                  depth); // 奥行き

    xhole14 = (xhole[0] +xhole[3])/2;
    yhole14 = (yhole[0] +yhole[3])/2;
    xhole25 = (xhole[1] +xhole[4])/2;
    yhole25 = (yhole[1] +yhole[4])/2;
    xhole36 = (xhole[2] +xhole[5])/2;
    yhole36 = (yhole[2] +yhole[5])/2;

    if (height < xsMean){
        if (width < xsMean){
            if (depth < xsMean){
                hole1->Fill(xhole14, yhole14);
                hole1->Fill(xhole25, yhole25);
                hole1->Fill(xhole36, yhole36);
            }else{
                hole4->Fill(xhole14, yhole14);
                hole4->Fill(xhole25, yhole25);
                hole4->Fill(xhole36, yhole36);
            }
        }else{
            if (depth < xsMean){
                hole3->Fill(xhole14, yhole14);
                hole3->Fill(xhole25, yhole25);
                hole3->Fill(xhole36, yhole36);
            }else{
                hole7->Fill(xhole14, yhole14);
                hole7->Fill(xhole25, yhole25);
                hole7->Fill(xhole36, yhole36);
            }
        }
    }else{
        if (width < xsMean){
            if (depth < xsMean){
                hole2->Fill(xhole14, yhole14);
                hole2->Fill(xhole25, yhole25);
                hole2->Fill(xhole36, yhole36);
            }else{
                hole6->Fill(xhole14, yhole14);
                hole6->Fill(xhole25, yhole25);
                hole6->Fill(xhole36, yhole36);
            }
        }else{
            if (depth < xsMean){
                hole5->Fill(xhole14, yhole14);
                hole5->Fill(xhole25, yhole25);
                hole5->Fill(xhole36, yhole36);
            }else{
                hole8->Fill(xhole14, yhole14);
                hole8->Fill(xhole25, yhole25);
                hole8->Fill(xhole36, yhole36);
            }
        }
    }






    sizex2y1->Fill(xsize[1],ysize[0]);
    sizex1y3->Fill(xsize[0],ysize[2]);
    
    for (int isurf = 0; isurf <6; isurf++){

        //（役に立ったか分からないが）色々なパラメータ間の相関

        xsxh->Fill(xsize[isurf]*0.01554, xhole[isurf]*0.01554);
        xsyh->Fill(xsize[isurf]*0.01554, yhole[isurf]*0.01554);
        ysxh->Fill(ysize[isurf]*0.01554, xhole[isurf]*0.01554);
        ysyh->Fill(ysize[isurf]*0.01554, yhole[isurf]*0.01554);
        xsys->Fill(xsize[isurf]*0.01554, ysize[isurf]*0.01554);
        xhyh->Fill(xhole[isurf]*0.01554, yhole[isurf]*0.01554);


        holexy->Fill(0.01554*sqrt(xhole[isurf]*xhole[isurf] + yhole[isurf]*yhole[isurf]));


        h1all->Fill(radius[isurf]);
        h2all->Fill( xhole[isurf]);
        h3all->Fill( yhole[isurf]);
        h4all->Fill( xsize[isurf]*0.01554);
        h5all->Fill( ysize[isurf]*0.01554);
        hball->Fill(  bump[isurf]);
        hEall->Fill(  Esum[isurf]);
        if (radiabs <= fabs(radius[isurf]-rMean)){
            radiabs  = fabs(radius[isurf]-rMean);
            rMax = radius[isurf];
            }
        if (xholeabs <= fabs(xhole[isurf]-xhMean)){
            xholeabs  = fabs(xhole[isurf]-xhMean);
            xhMax = xhole[isurf];
            }
        if (yholeabs <= fabs(yhole[isurf]-yhMean)){
            yholeabs  = fabs(yhole[isurf]-yhMean);
            yhMax = yhole[isurf];
            }
        if (xsizeabs <= fabs(xsize[isurf]-xsMean)){
            xsizeabs  = fabs(xsize[isurf]-xsMean);
            xsMax = xsize[isurf];
            }
        if (ysizeabs <= fabs(ysize[isurf]-ysMean)){
            ysizeabs  = fabs(ysize[isurf]-ysMean);
            ysMax = ysize[isurf];
            }
        if (bMax <= bump[isurf]){
            
            bMax = bump[isurf];
            }
        if (EMax <= Esum[isurf]){
            
            EMax = Esum[isurf];
            }
       //向かい合う面について 
        if (isurf <3){ 
            fxsxs->Fill(xsize[isurf]*0.01554, xsize[isurf+3]*0.01554);
            fxsys->Fill(xsize[isurf]*0.01554, ysize[isurf+3]*0.01554);
            fysys->Fill(ysize[isurf]*0.01554, ysize[isurf+3]*0.01554);

            fxhxh->Fill(xhole[isurf]*0.01554, xhole[isurf+3]*0.01554);
            fxhyh->Fill(xhole[isurf]*0.01554, yhole[isurf+3]*0.01554);
            fyhyh->Fill(yhole[isurf]*0.01554, yhole[isurf+3]*0.01554);

            fxsxh->Fill(xsize[isurf]*0.01554, xhole[isurf+3]*0.01554);
            fxsyh->Fill(xsize[isurf]*0.01554, yhole[isurf+3]*0.01554);
            fysxh->Fill(ysize[isurf]*0.01554, xhole[isurf+3]*0.01554);
            fysyh->Fill(ysize[isurf]*0.01554, yhole[isurf+3]*0.01554);


            fholexy->Fill( sqrt(xhole[isurf]*xhole[isurf] + yhole[isurf]*yhole[isurf])*0.01554, 
                           sqrt(xhole[isurf+3]*xhole[isurf+3] + yhole[isurf+3]*yhole[isurf+3])*0.01554);
            holexy1->Fill( fabs(sqrt(xhole[isurf]*xhole[isurf] + yhole[isurf]*yhole[isurf]) 
                              - sqrt(xhole[isurf+3]*xhole[isurf+3] + yhole[isurf+3]*yhole[isurf+3]))*0.01554);


            if (sqrt(xhole[isurf]*xhole[isurf] + yhole[isurf]*yhole[isurf])  
                - sqrt(xhole[isurf+3]*xhole[isurf+3] + yhole[isurf]*yhole[isurf+3]) > 0 ){
                fxhxh_half1->Fill(xhole[isurf]*0.01554, xhole[isurf+3]*0.01554);
                fyhyh_half1->Fill(yhole[isurf]*0.01554, yhole[isurf+3]*0.01554);
            }else{
                fxhxh_half2->Fill(xhole[isurf]*0.01554, xhole[isurf+3]*0.01554);
                fyhyh_half2->Fill(yhole[isurf]*0.01554, yhole[isurf+3]*0.01554);
            }
        }
    }


   if (  
/*
   47.8 < radius[0] &&
   47.8 < radius[1] &&
   47.8 < radius[2] &&
   47.8 < radius[3] &&
   47.8 < radius[4] &&
   47.8 < radius[5] &&
 
 168+4+0.5 < xhole[0] && xhole[0] < 198 -0.5+2 &&
 168+4+0.5 < xhole[1] && xhole[1] < 198 -0.5+2 &&
 168+4+0.5 < xhole[2] && xhole[2] < 198 -0.5+2 &&
 168+4+0.5 < xhole[3] && xhole[3] < 198 -0.5+2 &&
 168+4+0.5 < xhole[4] && xhole[4] < 198 -0.5+2 &&
 168+4+0.5 < xhole[5] && xhole[5] < 198 -0.5+2 &&

 168+4+0.5 < yhole[0] && yhole[0] < 198 -0.5+2 &&
 168+4+0.5 < yhole[1] && yhole[1] < 198 -0.5+2 &&
 168+4+0.5 < yhole[2] && yhole[2] < 198 -0.5+2 &&
 168+4+0.5 < yhole[3] && yhole[3] < 198 -0.5+2 &&
 168+4+0.5 < yhole[4] && yhole[4] < 198 -0.5+2 &&
 168+4+0.5 < yhole[5] && yhole[5] < 198 -0.5+2 &&
   
  651.8 < xsize[0] && xsize[0] < 664.8-0.5 &&
  651.8 < xsize[1] && xsize[1] < 664.8-0.5 &&
  651.8 < xsize[2] && xsize[2] < 664.8-0.5 &&
  651.8 < xsize[3] && xsize[3] < 664.8-0.5 &&
  651.8 < xsize[4] && xsize[4] < 664.8-0.5 &&
  651.8 < xsize[5] && xsize[5] < 664.8-0.5 &&
  
  651.8 < ysize[0] && ysize[0] < 664.8-0.5 &&
  651.8 < ysize[1] && ysize[1] < 664.8-0.5 &&
  651.8 < ysize[2] && ysize[2] < 664.8-0.5 &&
  651.8 < ysize[3] && ysize[3] < 664.8-0.5 &&
  651.8 < ysize[4] && ysize[4] < 664.8-0.5 &&
  651.8 < ysize[5] && ysize[5] < 664.8-0.5 &&
 
 Esum[0] < 200 &&
 Esum[1] < 200 &&
 Esum[2] < 200 &&
 Esum[3] < 200 &&
 Esum[4] < 200 &&
 Esum[5] < 200 &&
 
 bump[0] < 200 &&
 bump[1] < 200 &&
 bump[2] < 200 &&
 bump[3] < 200 &&
 bump[4] < 200 &&
 bump[5] < 200 &&
*/  
    1==1)
 {

    xsxhMax->Fill(xsMax, xhMax);
    xsyhMax->Fill(xsMax, yhMax);
    ysxhMax->Fill(ysMax, xhMax);
    ysyhMax->Fill(ysMax, yhMax);
    xsysMax->Fill(xsMax, ysMax);
    xhyhMax->Fill(xhMax, yhMax);
    h1->Fill(rMax);
    h2->Fill(xhMax);
    h3->Fill(yhMax);
    h4->Fill(xsMax);
    h5->Fill(ysMax);
    hb->Fill(bMax);
    hE->Fill(EMax);
    
    for (int fill =0; fill<6; fill++){
    h1six->Fill(radius[fill]);
    h2six->Fill(xhole[fill]*0.01554);
    h3six->Fill(yhole[fill]*0.01554);
    h4six->Fill(xsize[fill]*0.01554);
    h5six->Fill(ysize[fill]*0.01554);
    hbsix->Fill(bump[fill]);
    hEsix->Fill(Esum[fill]);

//    h1bad->Fill(radiusbad[fill]);
//    h2bad->Fill(xholebad[fill]);
//    h3bad->Fill(yholebad[fill]);
//    h4bad->Fill(xsizebad[fill]);
//    h5bad->Fill(ysizebad[fill]);
//    hbbad->Fill(bumpbad[fill]);
//    hEbad->Fill(Esumbad[fill]);
    }

    }
    else{
    h1b->Fill(rMax);
    h2b->Fill(xhMax);
    h3b->Fill(yhMax);
    h4b->Fill(xsMax);
    h5b->Fill(ysMax);
    hbb->Fill(bMax);
    hEb->Fill(EMax);
    }

}


xsxhMax->SetMarkerStyle(6);
xsyhMax->SetMarkerStyle(6);
ysxhMax->SetMarkerStyle(6);
ysyhMax->SetMarkerStyle(6);
xsysMax->SetMarkerStyle(6);
xhyhMax->SetMarkerStyle(6);

xsxh->SetMarkerStyle(6);
xsyh->SetMarkerStyle(6);
ysxh->SetMarkerStyle(6);
ysyh->SetMarkerStyle(6);
xsys->SetMarkerStyle(6);
xhyh->SetMarkerStyle(6);


hole1->SetMarkerStyle(6);     
hole2->SetMarkerStyle(6);     
hole3->SetMarkerStyle(6);     
hole4->SetMarkerStyle(6);     
hole5->SetMarkerStyle(6);     
hole6->SetMarkerStyle(6);     
hole7->SetMarkerStyle(6);     
hole8->SetMarkerStyle(6);     
     
    
     
     


fxsxs->SetMarkerStyle(6);
fxsys->SetMarkerStyle(6);
fysys->SetMarkerStyle(6);

fxhxh->SetMarkerStyle(6);
fxhyh->SetMarkerStyle(6);
fyhyh->SetMarkerStyle(6);
fholexy->SetMarkerStyle(6);



fxhxh_half1->SetMarkerStyle(6);
fyhyh_half1->SetMarkerStyle(6);
fxhxh_half2->SetMarkerStyle(6);
fyhyh_half2->SetMarkerStyle(6);

fxsxh->SetMarkerStyle(6);
fxsyh->SetMarkerStyle(6);
fysxh->SetMarkerStyle(6);
fysyh->SetMarkerStyle(6);

sizexy->SetMarkerStyle(6);
sizexz->SetMarkerStyle(6);
sizeyz->SetMarkerStyle(6);
sizexyz->SetMarkerStyle(6);


sizex2y1->SetMarkerStyle(6);
sizex1y3->SetMarkerStyle(6);

std::cout << "CorrelationFactor(fxsxs): " << fxsxs->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fxsys): " << fxsys->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fysys): " << fysys->GetCorrelationFactor() << std::endl;

std::cout << "CorrelationFactor(fxhxh): " << fxhxh->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fxhyh): " << fxhyh->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fyhyh): " << fyhyh->GetCorrelationFactor() << std::endl;

std::cout << "CorrelationFactor(fxsxh): " << fxsxh->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fxsyh): " << fxsyh->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fysxh): " << fysxh->GetCorrelationFactor() << std::endl;
std::cout << "CorrelationFactor(fysyh): " << fysyh->GetCorrelationFactor() << std::endl;


TFile *fout = new TFile("201102cut.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hb->Write();
hE->Write();

h1all->Write();
h2all->Write();
h3all->Write();
h4all->Write();
h5all->Write();
hball->Write();
hEall->Write();

holexy->Write();


h1six->Write();
h2six->Write();
h3six->Write();
h4six->Write();
h5six->Write();
hbsix->Write();
hEsix->Write();

//h1bad->Write();
//h2bad->Write();
//h3bad->Write();
//h4bad->Write();
//h5bad->Write();
//hbbad->Write();
//hEbad->Write();

h1b->Write();
h2b->Write();
h3b->Write();
h4b->Write();
h5b->Write();
hbb->Write();
hEb->Write();

xsxhMax->Write();
xsyhMax->Write();
ysxhMax->Write();
ysyhMax->Write();
xsysMax->Write();
xhyhMax->Write();


xsxh->Write();
xsyh->Write();
ysxh->Write();
ysyh->Write();
xsys->Write();
xhyh->Write();

hole1->Write();
hole2->Write();
hole3->Write();
hole4->Write();
hole5->Write();
hole6->Write();
hole7->Write();
hole8->Write();


fxsxs->Write();
fxsys->Write();
fysys->Write();

fxhxh->Write();
fxhyh->Write();
fyhyh->Write();
fholexy->Write();


fxhxh_half1->Write();
fyhyh_half1->Write();
fxhxh_half2->Write();
fyhyh_half2->Write();


fxsxh->Write();
fxsyh->Write();
fysxh->Write();
fysyh->Write();

sizexy->Write();
sizexz->Write();
sizeyz->Write();
sizexyz->Write();

sizex2y1->Write();
sizex1y3->Write();

hist_h->Write();
hist_w->Write();
hist_d->Write();

sub_hw->Write();
sub_hd->Write();
sub_wd->Write();
holexy1->Write();
TTree *treeclone = tree->CloneTree();
treeclone->Write();

fout->Close();
fin->Close();




}

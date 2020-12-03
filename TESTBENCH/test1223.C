#include <boost/python.hpp>
#include <TApplication.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <RooInt.h>
#include <TCanvas.h>
#include <TGraph.h>


//int main(){
void test1223(){
  // キャンバスの準備
  TCanvas *c = new TCanvas( "test" ); 
  // 枠を書く 左下(0.0, 0.0)　右上(4.0, 10.0) 
  TH1 *frame = c->DrawFrame( 0.0, 0.0, 4.0, 10.0 );
  // データーの準備 
  double x[4] = { 0.0, 1.0, 2.0, 3.0 };
  double y[4] = { 0.0, 1.0, 4.0, 9.0 };
  // グラフを作る 
  TGraph *g = new TGraph( 4, x, y );
  g->Fit("pol2","","",0,3);
  g->SetMarkerStyle( 20 ); 
  g->SetMarkerSize( 1.0 );
  g->Draw( "PC" );        // グラフを書く 
  c->Print( "test.png" ); // グラフをファイルに出力 
}

BOOST_PYTHON_MODULE(test1223){

    using namespace boost::python;
    def("test1223", test1223);

}

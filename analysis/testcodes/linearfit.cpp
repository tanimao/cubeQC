void linearfit(){
gStyle->SetOptStat(1111);
const Int_t n = 3;
Double_t pixel[n]   = {0., 260.02, 260.96};
//Double_t pix_err[n] = {0., 0.05, 0.31};
Double_t real[n]    = {0., 10.17, 10.21};
//Double_t real_err[n]= {0.};

//TGraphErrors *gr = new TGraphErrors(n,pixel,real,pix_err,real_err);
TGraph *gr = new TGraph(n,pixel,real);
gr->SetMarkerSize(1.5);
gr->SetMarkerColor(2);
gr->SetMarkerStyle(8);
gr->Fit("pol1");
gr->Draw("AP");


}

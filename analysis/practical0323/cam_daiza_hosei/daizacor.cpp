#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void daizacor(){

TString daizaA      = "08210821daiza2";
TString daizaB      = "08230823daiza3";
TString readroot    = ".root";
TString daizacor    = "daizacor.root";

TString file_readrootA = daizaA + readroot ;
TString file_readrootB = daizaB + readroot ;
TString file_output    = daizaA + daizaB + daizacor ;


TFile * finA = new TFile(file_readrootA, "read");
TFile * finB = new TFile(file_readrootB, "read");







}

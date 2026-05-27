#pragma once

#include <iostream>
#include <string>
// ROOT
#include "TTree.h"
#include "TBranch.h"
#include "TVector3.h"
// dk2nu
#include "dk2nu/tree/dk2nu.h"

namespace dk2nuana{

class TreeHelper{

public:

  TreeHelper();
  ~TreeHelper();

  void Init();
  void Reset();
  void FillVariable(bsim::Dk2Nu* _dk2nu);

  TTree* GetTree(){ return fTree; }

  bool DoDebug;

private:
  TTree* fTree{nullptr};

  // Detector positions
  TVector3 DetPos_ICARUS; // [450.37, 7991.98, 79512.66], https://github.com/woodtp/dk2nu-numi-flux/blob/main/config.toml#L2C5-L2C32, ICARUS TPC center in NuMI coords [cm]
  TVector3 DetPos_MINERvA; // [-24.86, -24.0067, 103168.] https://github.com/NuSoftHEP/dk2nu/commit/ef125a07a190b3803731cf999c80a5c040f4edf4

  size_t NDUNEPos;
  std::vector<TVector3> DetPos_DUNE_AllAxes;

  // Variables
  Int_t DecayProcess;
  Int_t NuPDG;
  Double_t ParentMom;
  Double_t ParentPt;
  Double_t ParentCos;
  Double_t ImpWgt;
  Double_t ENuCM;
  // ICARUS
  Double_t Weight_ICARUS;
  Double_t Enu_ICARUS;
  // MINERvA
  Double_t Weight_MINERvA;
  Double_t Enu_MINERvA;
  // DUNE
  std::vector<Double_t> Weights_DUNE;
  std::vector<Double_t> Enus_DUNE;

};

} // END namespace dk2nuana

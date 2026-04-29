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
  TVector3 DetPos_ICARUS; // [450.37, 7991.98, 79512.66],  # ICARUS TPC center in NuMI coords [cm]

  // Variables
  Int_t DecayProcess;
  Int_t NuPDG;
  Double_t ParentMom;
  // ICARUS
  Double_t Weight_ICARUS;
  Double_t Enu_ICARUS;

};

} // END namespace dk2nuana

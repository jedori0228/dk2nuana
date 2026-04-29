#include "TreeHelper.h"

#include "dk2nu/tree/calcLocationWeights.h"

namespace dk2nuana{

TreeHelper::TreeHelper(){

  DoDebug = false;

  DetPos_ICARUS = TVector3(450.37, 7991.98, 79512.66); // ICARUS TPC center in NuMI coords [cm]

}

TreeHelper::~TreeHelper(){

}

void TreeHelper::Init(){

  if(DoDebug) std::cout << "[TreeHelper::Init()] Called" << std::endl;

  if(DoDebug) std::cout << "[TreeHelper::Init()] Creating TTree" << std::endl;

  fTree = new TTree("Tree", "Tree");

  if(DoDebug) std::cout << "[TreeHelper::Init()] Define branches" << std::endl;

  
  fTree->Branch("DecayProcess", &DecayProcess, "DecayProcess/I");
  fTree->Branch("NuPDG", &NuPDG, "NuPDG/I");
  fTree->Branch("ParentMom", &ParentMom, "ParentMom/D");
  // ICARUS
  fTree->Branch("Weight_ICARUS", &Weight_ICARUS, "Weight_ICARUS/D");
  fTree->Branch("Enu_ICARUS", &Enu_ICARUS, "Enu_ICARUS/D");
  
  
  if(DoDebug) std::cout << "[TreeHelper::Init()] Done!" << std::endl;

}

void TreeHelper::Reset(){

  DecayProcess = -1;
  NuPDG = -999;
  ParentMom = -999.;

  Weight_ICARUS = -999.;
  Enu_ICARUS = -999.;

}

void TreeHelper::FillVariable(bsim::Dk2Nu* _dk2nu){

  if(DoDebug) std::cout << "[TreeHelper::FillVariable()] Called" << std::endl;

  const auto& _decay = _dk2nu->decay;

  DecayProcess = _decay.ndecay;
  NuPDG = _decay.ntype;
  
  ParentMom = sqrt(_decay.pdpx*_decay.pdpx + _decay.pdpy*_decay.pdpy + _decay.pdpz*_decay.pdpz);

  bsim::calcEnuWgt(_dk2nu, DetPos_ICARUS, Enu_ICARUS, Weight_ICARUS);
  

  fTree->Fill();

}

} // END namespace dk2nuana

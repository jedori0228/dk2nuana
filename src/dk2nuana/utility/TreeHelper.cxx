#include "TreeHelper.h"

#include "dk2nu/tree/calcLocationWeights.h"

namespace dk2nuana{

TreeHelper::TreeHelper(){

  DoDebug = false;

  DetPos_ICARUS = TVector3(450.37, 7991.98, 79512.66);
  DetPos_MINERvA = TVector3(-24.86, -24.0067, 103168.);

  // DUNE, on-axis
  DetPos_DUNE_AllAxes.push_back( TVector3(0., 0., 57400.) );
  for(int i=0; i<8; i++){
    DetPos_DUNE_AllAxes.push_back( TVector3( (i*4.0) * 100., 0., 57400.) );
  }
  DetPos_DUNE_AllAxes.push_back( TVector3( (30.5) * 100., 0., 57400.) );

  NDUNEPos = DetPos_DUNE_AllAxes.size();

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
  fTree->Branch("ParentPt", &ParentPt, "ParentPt/D");
  fTree->Branch("ParentCos", &ParentCos, "ParentCos/D");
  fTree->Branch("ImpWgt", &ImpWgt, "ImpWgt/D");
  fTree->Branch("ENuCM", &ENuCM, "ENuCM/D");
  
  // ICARUS
  fTree->Branch("Weight_ICARUS", &Weight_ICARUS, "Weight_ICARUS/D");
  fTree->Branch("Enu_ICARUS", &Enu_ICARUS, "Enu_ICARUS/D");
  // MINERvA
  fTree->Branch("Weight_MINERvA", &Weight_MINERvA, "Weight_MINERvA/D");
  fTree->Branch("Enu_MINERvA", &Enu_MINERvA, "Enu_MINERvA/D");
  // DUNE
  fTree->Branch("Weights_DUNE", &Weights_DUNE);
  fTree->Branch("Enus_DUNE", &Enus_DUNE);
  
  if(DoDebug) std::cout << "[TreeHelper::Init()] Done!" << std::endl;

}

void TreeHelper::Reset(){

  DecayProcess = -1;
  NuPDG = -999;
  ImpWgt = -999.;
  ParentMom = -999.;
  ParentPt = -999.;
  ParentCos = -999.;
  ENuCM = -999.;

  Weight_ICARUS = -999.;
  Enu_ICARUS = -999.;

  Weight_MINERvA = -999.;
  Enu_MINERvA = -999.;

  Weights_DUNE = std::vector<Double_t>(NDUNEPos, -999.);
  Enus_DUNE = std::vector<Double_t>(NDUNEPos, -999.);

}

void TreeHelper::FillVariable(bsim::Dk2Nu* _dk2nu){

  if(DoDebug) std::cout << "[TreeHelper::FillVariable()] Called" << std::endl;

  Reset();

  const auto& _decay = _dk2nu->decay;

  DecayProcess = _decay.ndecay;
  NuPDG = _decay.ntype;
  ENuCM = _decay.necm;
  
  ImpWgt = _decay.nimpwt;
  ParentMom = sqrt(_decay.pdpx*_decay.pdpx + _decay.pdpy*_decay.pdpy + _decay.pdpz*_decay.pdpz);
  ParentPt = sqrt(_decay.pdpx*_decay.pdpx + _decay.pdpy*_decay.pdpy);
  ParentCos = abs(_decay.pdpz)/ParentMom;

  bsim::calcEnuWgt(_dk2nu, DetPos_ICARUS, Enu_ICARUS, Weight_ICARUS);
  Weight_ICARUS /= M_PI;
  
  bsim::calcEnuWgt(_dk2nu, DetPos_MINERvA, Enu_MINERvA, Weight_MINERvA);
  Weight_MINERvA /= M_PI;

  for(unsigned int i_DUNEPos=0; i_DUNEPos<NDUNEPos; i_DUNEPos++){
    bsim::calcEnuWgt(_dk2nu, DetPos_DUNE_AllAxes[i_DUNEPos], Enus_DUNE[i_DUNEPos], Weights_DUNE[i_DUNEPos]);
    Weights_DUNE[i_DUNEPos] /= M_PI;
  }

  fTree->Fill();

}

} // END namespace dk2nuana

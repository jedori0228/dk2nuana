#include "LoopRecord.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "dk2nu/tree/dk2nu.h"
#include "dk2nu/tree/dkmeta.h"

namespace dk2nuana{

LoopRecord::LoopRecord(
  std::string basedirname,
  std::string dk2nutreename,
  std::string dkmetatreename){

  fBaseDirName = basedirname=="" ? "" : basedirname+"/";
  fDK2NUTreeName = dk2nutreename;
  fDKMetaTreeName = dkmetatreename;

  NProcessedEvents = 0;
  NMaxEventsToProcess = 0;
  NProcessedFiles = 0;

  DoDebug = false;

  POTSum = 0;
  treeHelper = new TreeHelper();

}

LoopRecord::~LoopRecord(){

}

void LoopRecord::SetNMaxEventsToProcess(size_t nmax){
  NMaxEventsToProcess = nmax;
}

void LoopRecord::ProcessFile(std::string inputfile){

  TFile *f_input = TFile::Open(inputfile.c_str());

  // dk2nu tree

  TTree *fInputDK2NUTree = (TTree *)f_input->Get( (fBaseDirName+fDK2NUTreeName).c_str());
  size_t ThisNDK2NUEvents = fInputDK2NUTree->GetEntries();

  bsim::Dk2Nu* m_dk2nu = nullptr;
  fInputDK2NUTree->SetBranchAddress("dk2nu", &m_dk2nu);

  if(DoDebug){
    printf("[LoopRecord::ProcessFile] ThisNDK2NUEvents = %ld\n", ThisNDK2NUEvents);
  }

  // POT from meta
  TTree *fInputDKMetaTree = (TTree *)f_input->Get( (fBaseDirName+fDKMetaTreeName).c_str());
  bsim::DkMeta* m_dkmeta = nullptr;
  fInputDKMetaTree->SetBranchAddress("dkmeta", &m_dkmeta);
  if(fInputDKMetaTree->GetEntries()!=1){
    printf("[LoopRecord::ProcessFile] Number of entry from dkmeta is not 1 but  = %ld\n", fInputDKMetaTree->GetEntries());
    abort();
  }
  fInputDKMetaTree->GetEntry(0);
  POTSum += m_dkmeta->pots;

  // Loop over CAFTree
  for (size_t i_evt = 0; i_evt < ThisNDK2NUEvents; ++i_evt) {

    if(DoDebug){
      printf("[LoopRecord::ProcessFile] * DK2NU event entry = %ld\n", i_evt);
    }
    // Check if NMaxCAFEventsToProcess is set
    if( NMaxEventsToProcess>0 ){
      // if set, check if we have reached the maximum
      if(NProcessedEvents>=NMaxEventsToProcess ){
        printf("[LoopRecord::ProcessFile] * Reached the maximum events to process, N_MAX = %ld\n", NMaxEventsToProcess);
        break;
      }
    }

    fInputDK2NUTree->GetEntry(i_evt);

    treeHelper->FillVariable(m_dk2nu);

    NProcessedEvents++;

  } // END caf event loop

  NProcessedFiles++;

  printf("[LoopRecord::ProcessFile] -----------------\n");
  printf("[LoopRecord::ProcessFile] File done\n");

}

} // END namespace cafnusyst

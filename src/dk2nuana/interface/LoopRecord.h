#pragma once

#include <iostream>
#include <string>
// ROOT
#include "TChain.h"
#include "TBranch.h"

// dk2nuana
#include "dk2nuana/utility/TreeHelper.h"

namespace dk2nuana{

class LoopRecord{

public:

  LoopRecord(
    std::string basedirname,
    std::string dk2nutreename,
    std::string dkmetatreename
  );
  ~LoopRecord();

  std::string fBaseDirName;
  std::string fDK2NUTreeName;
  std::string fDKMetaTreeName;
  size_t NProcessedEvents;
  size_t NMaxEventsToProcess;
  void SetNMaxEventsToProcess(size_t nmax);
  void ProcessFile(std::string inputfile);
  size_t NProcessedFiles;

  bool DoDebug;

  // output
  double POTSum;
  TreeHelper* treeHelper{nullptr};

  void Save();

};

} // END namespace dk2nuana

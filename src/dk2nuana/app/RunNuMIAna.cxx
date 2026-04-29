// std
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
// ROOT
#include "TObjString.h"
#include "TChain.h"
#include "TFile.h"
#include "TParameter.h"

// dk2nuana
#include "dk2nuana/utility/string_parsers.hh"
#include "dk2nuana/utility/TreeHelper.h"
#include "dk2nuana/interface/LoopRecord.h"

namespace cliopts {
  std::string input_filename = "";
  std::string output_filename = "";
  size_t NMax = std::numeric_limits<size_t>::max();
  size_t NSkip = 0;
  bool DoDebug = false;
} // namespace cliopts

void SayUsage(char const *argv[]) {
  std::cout << "[USAGE]: " << argv[0] << "\n" << std::endl;
  std::cout << "\t-?|--help          : Show this message.\n"
               "\t-i <inputlist.txt> : List of input CAF files\n"
               "\t-N <NMax>        : Maximum number of events to process.\n"
               "\t-s <NSkip>       : Number of events to skip.\n"
               "\t-o <out.root>    : File to write validation canvases to.\n"
               "\t--debug          : Run debugging mode.\n"
            << std::endl;
}

void HandleOpts(int argc, char const *argv[]) {
  int opt = 1;
  while (opt < argc) {
    if ((std::string(argv[opt]) == "-?") ||
        (std::string(argv[opt]) == "--help")) {
      SayUsage(argv);
      exit(0);
    } else if (std::string(argv[opt]) == "-i") {
      cliopts::input_filename = argv[++opt];
    } else if (std::string(argv[opt]) == "-N") {
      cliopts::NMax = dk2nuana::str2T<size_t>(argv[++opt]);
    } else if (std::string(argv[opt]) == "-s") {
      cliopts::NSkip = dk2nuana::str2T<size_t>(argv[++opt]);
    } else if (std::string(argv[opt]) == "-o") {
      cliopts::output_filename = argv[++opt];
    } else if (std::string(argv[opt]) == "--debug") {
      cliopts::DoDebug = true;
      ++opt;
    } else {
      std::cout << "[ERROR]: Unknown option: " << argv[opt] << std::endl;
      SayUsage(argv);
      exit(1);
    }
    opt++;
  }
}

int main(int argc, char const *argv[]) {

  HandleOpts(argc, argv);
  if (!cliopts::input_filename.size()) {
    std::cout << "[ERROR]: Expected to be passed a -i option." << std::endl;
    SayUsage(argv);
    return 1;
  }

  std::ifstream inputFile(cliopts::input_filename);
  if(!inputFile.is_open()){
    printf("[ERROR] %s does not exist\n", cliopts::input_filename);
    return 1;
  }

  std::string filePath;
  dk2nuana::LoopRecord LR("", "dk2nuTree", "dkmetaTree");
  LR.SetNMaxEventsToProcess(cliopts::NMax);
  if(cliopts::DoDebug) LR.DoDebug = true;

  printf("Saving outputs to: %s\n", cliopts::output_filename.c_str());
  TFile *fOutputFile = new TFile(cliopts::output_filename.c_str(), "RECREATE");
  fOutputFile->cd();
  LR.treeHelper->Init();

  // Loop over input files
  while (std::getline(inputFile, filePath)) {
    printf("[Input] %s\n", filePath.c_str());
    LR.ProcessFile(filePath.c_str());
  }
  inputFile.close();

  fOutputFile->cd();
  LR.treeHelper->GetTree()->Write("AnaTree");

  // POT
  TParameter<double> *p_POTSum = new TParameter<double>("POTSum", LR.POTSum);
  p_POTSum->Write();

  fOutputFile->Close();

}

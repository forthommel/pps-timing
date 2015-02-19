#include "PPSReader.h"

ClassImp(PPS::PPSReader)

namespace PPS
{

  //ClassImp(PPSReader)

  PPSReader::PPSReader() :
    fFilename(""), fFile(0), fEventsTree(0)
  {}

  PPSReader::PPSReader(TString file) :
    fFilename(file), fFile(0), fEventsTree(0)
  {
    Open(fFilename);
  }

  PPSReader::~PPSReader()
  {
    /*if (fFile) {
      if (fFile->IsOpen()) {
        //delete fRunsTree;
        delete fEventsTree;
      }
      fFile->Close();
      delete fFile;
    }*/
  }

  bool
  PPSReader::Open(TString file)
  {
    fFilename = file;
    if (fFilename=="") return false;

    fFile = new TFile(fFilename, "READ");
    if (!fFile->IsOpen()) return false;

    /*fRunsTree = (TTree*)(fFile->Get("runs"));
    if (!fRunsTree) return false;*/

    fEventsTree = (TTree*)(fFile->Get("events"));
    //fEventsTree->SetMakeClass(1);
    if (!fEventsTree) return false;

    fEventsTree->SetBranchStatus("*", 0); // introduced to speed up the tree reading

    return true;
  }
}

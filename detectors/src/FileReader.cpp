#include "FileReader.h"

ClassImp(PPS::FileReader)

namespace PPS
{
  FileReader::FileReader() :
    fFilename(""), fFile(0), fEventsTree(0)
  {}

  FileReader::FileReader(TString file) :
    fFilename(file), fFile(0), fEventsTree(0)
  {
    Open(fFilename);
  }

  FileReader::~FileReader()
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
  FileReader::Open(TString file)
  {
    fFilename = file;
    if (fFilename=="") return false;

    fFile = new TFile(fFilename, "READ");
    if (!fFile->IsOpen()) return false;

    fEventsTree = static_cast<TTree*>(fFile->Get("events"));
    if (!fEventsTree) return false;

    //fEventsTree->SetBranchStatus("*", 0); // introduced to speed up the tree reading

    return true;
  }
}

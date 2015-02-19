#ifndef PPSReader_h
#define PPSReader_h

#include "TFile.h"
#include "TTree.h"

#include <iostream>

namespace PPS
{
  /**
   * \brief PPS file format reader
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 17 Feb 2015
   */
  class PPSReader
  {
    public:
      PPSReader();
      PPSReader(TString file);
      virtual ~PPSReader();

      bool Open(TString file="");
      bool IsOpen() const { return (fFile!=0 && fFile->IsOpen()); }

#ifdef __CINT__
      template<class T> bool SetDetectorEventsAddress(TString det, T* obj);
#else
      template<class T> bool SetDetectorEventsAddress(TString det, T* obj) {
        // it looks like CINT and templates are worthless to be put together...
        T* obj_cop = new T;
        TString name = Form("%s__%s", det.Data(), obj_cop->ClassName());
        delete obj_cop;
        std::cout << __PRETTY_FUNCTION__ << " invoked to retrieve a \"" << name << "\" object" << std::endl;
        if (!fFile or !fEventsTree) return false;
        fEventsTree->SetBranchStatus(name, 1);
        if (fEventsTree->SetBranchAddress(name, &obj)<0) return false;
        return true;
      }
#endif
      inline size_t NumEvents() const { return (size_t)fEventsTree->GetEntries(); }
      inline void GetEvent(size_t i) const {
        if (!fEventsTree) return;
        if (i>=NumEvents()) return;
        std::cout << "retrieving event " << i << "/" << NumEvents() << std::endl;
        fEventsTree->GetEntry(i);
      }

    private:
      TString fFilename;
      TFile* fFile;
      //TTree* fRunsTree;
      TTree* fEventsTree;

    public:
      ClassDef(PPSReader, 1)
  };
}


#endif

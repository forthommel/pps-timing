#ifndef PPSReader_h
#define PPSReader_h

#include "RunInformation.h"
#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <vector>

namespace PPS
{
  typedef std::vector<TBranch*> TBranchesRef;
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
      /**
       * Test to check the validity of the opened file (if opened).
       */
      inline bool IsOpen() const { return (fFile!=0 && fFile->IsOpen()); }
      /**
       * Extract all the information on the run to produce these events.
       */
      inline RunInformation* GetRunInformation() const {
        if (!fFile) return 0;
        return static_cast<RunInformation*>(fFile->Get("run"));
      }
      /**
       * Set the address to the object to be retrieved for each event
       * \param[in] det The GeometryComponent's sensitive detector name to be retrieved
       * \param[out] obj Pointer to the object to be filled on the tree's retrieval
       * \return An integer stating the result of the operation (same as TTree::SetBranchAddress)
       */
#ifdef __CINT__
      template<class T> int SetDetectorEventsAddress(TString det, T* obj);
#else
      template<class T> int SetDetectorEventsAddress(TString det, T* obj) {
        // it looks like CINT and templates are worthless to be put together...
        obj = new T;
        //T* obj_cop = new T;
        TString name = Form("%s__%s", det.Data(), obj->ClassName());
        //delete obj_cop;
        std::cout << __PRETTY_FUNCTION__ << " invoked to retrieve a \"" << name << "\" object" << std::endl;
        if (!fFile or !fEventsTree) return -1;
        fEventsTree->SetBranchStatus(name, 1);
        //if (fEventsTree->SetBranchAddress(name, &obj)<0) return false;
        //int ret = fEventsTree->SetBranchAddress(name, obj);
        TBranch *br = fEventsTree->GetBranch(name);
        fBranches->push_back(br);
        br->SetAddress(&obj);
        std::cout << __PRETTY_FUNCTION__ << " branch " << name << " : " << std::endl;
        br->Print();
        return 0;
        //return true;
      }
#endif
      /**
       * Get the number of events stored in the input file
       */
      inline size_t NumEvents() const { return (size_t)fEventsTree->GetEntries(); }
      /**
       * Retrieve one event from the input file (and fill all the objects previously
       * declared through SetDetectorEventsAddress)
       */
      inline void GetEvent(size_t i) const {
        if (!fEventsTree) return;
        if (i>=NumEvents()) return;
        std::cout << "retrieving event " << i << "/" << NumEvents() << std::endl;
        for (TBranchesRef::iterator br=fBranches->begin(); br<fBranches->end(); br++) {
        //fEventsTree->GetEntry(i);
          (*br)->GetEntry(i);
        }
      }

    private:
      /// Path to the input file
      TString fFilename;
      /// Retrieved input ROOT file
      TFile* fFile;
      /// Tree containing all the events information
      TTree* fEventsTree;
      TBranchesRef* fBranches;
    public:
      ClassDef(PPSReader, 1)
  };
}


#endif

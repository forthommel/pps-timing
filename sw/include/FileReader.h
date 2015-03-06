#ifndef FileReader_h
#define FileReader_h

#include "RunInformation.h"
#include "EventInformation.h"

#include "TFile.h"

#include <iostream>
#include <iomanip>
#include <vector>

namespace PPS
{
  /**
   * \brief PPS file format reader
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 17 Feb 2015
   */
  class FileReader
  {
    public:
      FileReader();
      FileReader(TString file);
      virtual ~FileReader();

      bool Open(TString file="");
      /**
       * Test to check the validity of the opened file (if opened).
       */
      inline bool IsOpen() const { return (fFile!=0 && fFile->IsOpen()); }

      inline void ShowEvents() const {
        if (!fFile or !fEvent) return;
        fEvent->Show();
      }

      /**
       * Extract all the information on the run to produce these events.
       */
      inline RunInformation* GetRunInformation() const { return fRun; }
      /**
       * Extract all the events content.
       */
      inline EventInformation* GetEventInformation() const { return fEvent; }
      /**
       * Set the address to the object to be retrieved for each event
       * \param[in] det The GeometryComponent's sensitive detector name to be retrieved
       * \param[out] obj Pointer to the object to be filled on the tree's retrieval
       * \return An integer stating the result of the operation (same as TTree::SetBranchAddress)
       */
#ifdef __CINT__
      template<class T> int SetDetectorEventsAddress(TString det, T** obj);
#else
      template<class T> int SetDetectorEventsAddress(TString det, T** obj) {
        T* obj_cop = new T;
        TString name = Form("%s__%s", det.Data(), obj_cop->ClassName());
        delete obj_cop;
#ifdef DEBUG
        std::cout << __PRETTY_FUNCTION__ << " invoked to retrieve a \"" << name << "\" object" << std::endl;
#endif
        if (!fFile or !fEvent) return -1;
        return fEvent->SetBranchAddress(name, obj);
      }
#endif
      /**
       * Get the number of events stored in the input file
       */
      inline size_t NumEvents() const { return static_cast<size_t>(fEvent->GetEntries()); }
      /**
       * Retrieve one event from the input file (and fill all the objects previously
       * declared through SetDetectorEventsAddress)
       */
      inline void GetEvent(size_t i) const {
        if (!fEvent) return;
        if (i>=NumEvents()) return;
        if (fmod(100.*i/NumEvents(), 10.)==0) 
          std::cout << "[" << std::setw(3) << static_cast<int>(100.*i/NumEvents()) << "%]  Retrieving event " << i << "/" << NumEvents() << std::endl;
        fEvent->GetEntry(i);
      }

    private:
      /// Path to the input file
      TString fFilename;
      /// Retrieved input ROOT file
      TFile* fFile;
      /// Tree containing all the events information
      RunInformation* fRun;
      /// Tree containing all the events information
      EventInformation* fEvent;
    public:
      ClassDef(FileReader, 1)
  };
}


#endif

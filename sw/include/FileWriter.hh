#ifndef FileWriter_h
#define FileWriter_h

#include "RunInformation.h"
#include "EventInformation.h"

#include "G4Step.hh"

#include "TFile.h"

#define MAX_MODULES 4

namespace PPS
{
  /**
   * Analysis class intended to store into a TTree the information collected
   * for each event in each run.
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date Feb 2015
   */
  class FileWriter
  {
    public:
      /**
       * \brief Default class constructor to book the TTree and its
       *  different leaves to store the information.
       * \param[in] filename The file name to store the output tree.
       */
      FileWriter(G4String filename="events.root");
      ~FileWriter();
    
      /** \brief Store the runs tree onto the external ROOT file */
      void StoreRun();
      /** \brief Store the events tree onto the external ROOT file */
      void StoreEvent();
    
      /**
       * \brief Add the information on current run to the output file
       * \return A boolean stating the succes (or error) of the operation
       */
      inline G4bool SetRunInformation(RunInformation* ri) {
        if (!fFile) return false;
        fRun = ri;
        return true;
      }
      inline RunInformation* GetRunInformation() const { return fRun; }
      inline EventInformation* GetEventInformation() const { return fEvent; }
    
    private:
      TString fFilename;
      TFile *fFile;

      RunInformation* fRun;
      EventInformation* fEvent;
  };
}

#endif

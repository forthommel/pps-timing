#ifndef FileWriter_h
#define FileWriter_h

#include "RunInformation.h"

#include "G4Step.hh"

#include "TTree.h"
#include "TFile.h"
#include "TH2.h"

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
       * Add a new sensitive detector to the output file (and TTree) for
       * the storage of data accumulated at each event for it.
       * \param[inout] object Class (derived from a TObject) to be stored in
       *  the TTree
       * \return A boolean stating the success (or error) of the operation
       */
      template<class T> G4bool RegisterSD(T* object) {
	if (!fFile or !fEventsTree) return false;
	fEventObjects.push_back(object);
	fEventsTree->Branch(Form("%s__%s", object->GetSDName().Data(), object->GetName()), object->ClassName(), object, 64000, 1);
	fEventObjectsName.push_back(object->GetSDName());
	object->Clear(); // Object is cleared before any run
	return true;
      }

      G4bool SetRunInformation(PPS::RunInformation* ri) {
        if (!fFile or !fRunsTree) return false;
	fRunsTree->Branch("run", ri->ClassName(), ri, 64000, 1);
	return true;
      }
    
      /**
       *  Add all the information about a sensitive detector to the output
       *  file.
       * \param[in] sd Sensitive detector name the data is related to
       * \param[in] object Data container (derived from a TObject class)
       *  to be stored in the output TTree
       * \return A boolean stating the success (or error) of the operation
       */
      template<class T> G4bool AddSDData(TString sd, T* object) {
	G4int i = 0;
	for (std::vector<TString>::iterator nm=fEventObjectsName.begin(); nm!=fEventObjectsName.end(); nm++, i++) {
	  if ((*nm)==sd) {
	    fEventObjects.at(i) = object;
	    //G4cout << __PRETTY_FUNCTION__ << " object \"" << fObjectsName.at(i) << "\" set and filled !" << G4endl;
	    return true;
	  }
	}
	return false;
      }
  
    private:
      TString fFilename;
      TFile *fFile;

      TTree *fRunsTree;
    
      TTree *fEventsTree;
      std::vector<TString> fEventObjectsName;
      std::vector<TObject*> fEventObjects;
  };
}

#endif

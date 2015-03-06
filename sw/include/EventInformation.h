#ifndef EventInformation_h
#define EventInformation_h

#include "TObject.h"
#include "TTree.h"

#include <iostream>
#include <vector>

namespace PPS
{
  typedef std::vector<TObject*> DetectorsRef;
  typedef std::vector<TString> DetectorsNames;
  /**
   * Object containing useful information on the sensitive detectors present in
   * this sample of simulated events.
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 5 Mar 2015
   */
  class EventInformation : public TTree
  {
    public:
      EventInformation();
      virtual ~EventInformation();
      /**
       * \brief Remove all detectors information associated to the current run
       * condition from this object
       */
      inline void Clear(Option_t*) {
        if (!fDetCollection) return;
        fDetCollection->clear();
        fDetCollectionName.clear();
      }
      inline void Lock() {
        std::cout << __PRETTY_FUNCTION__ << " events format locked !" << std::endl;
        fLocked = true;
      }
      inline void UnLock() {
        std::cout << __PRETTY_FUNCTION__ << " events format unlocked !" << std::endl;
        fLocked = false;
      }
      void BeforeRun();
      
      /**
       * \brief Register an additional detector to the present events content
       * to store its accumulated data.
       * \param[in] det The SensitiveDetector-like object to store in this object's
       * collection
       * \return A boolean stating the success (or error) of the operation
       */
#ifndef __MAKECINT__
      template<class T> bool RegisterDetector(T* det) {
        if (fLocked) {
          std::cout << __PRETTY_FUNCTION__ << " Warning ! trying to add a new detector (\"" << det->GetName() << "\") with a locked data format !" << std::endl;
          // one cannot add an extra detector once this structure is locked
          return false;
        }
        fDetCollection->push_back(det);
        Branch(Form("%s__%s", det->GetSDName().Data(), det->GetName()), det->ClassName(), det, 32000, 1);
        fDetCollectionName.push_back(det->GetSDName());
        det->Clear(); // Detector is cleared before any run
        return true;
      }
#endif
      /**
       * Add all the information about a sensitive detector to the output               
       * tree.
       * \param[in] sd Sensitive detector name the data is related to.
       * \param[in] object Data container (derived from a TObject class)
       * to be stored in the output.
       * \tparam T Type of event object to be stored in the file
       * \return A boolean stating the success (or error) of the operation
       */
#ifndef __MAKECINT__
      template<class T> bool AddDetectorData(TString sd, T* det) {
        int i=0;
        for (DetectorsNames::iterator n=fDetCollectionName.begin(); n!=fDetCollectionName.end(); n++, i++) {
          if (*n==sd) { fDetCollection->at(i) = det; return true; }
        }
        return false;
      }
#endif
      inline DetectorsNames GetDetectorsNames() const { return fDetCollectionName; }

      inline void SetGenerationTime(float gentime) { fGenTime=gentime; }
      inline float GetGenerationTime() const { return fGenTime; }

    private:
      bool fLocked; //!

      DetectorsNames fDetCollectionName; //!
      DetectorsRef* fDetCollection; //!

      /// Event generation time
      float fGenTime; //!

    public:
      ClassDef(EventInformation, 1)
  };
}

#endif

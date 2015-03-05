#ifndef RunInformation_h
#define RunInformation_h

#include "IncomingParticle.h"

#include "TObject.h"
#include "TTree.h"

namespace PPS
{
  /**
   * Object containing useful information on the run conditions to produce this sample of
   * simulated events
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date Feb 2015
   */
  class RunInformation : public TTree
  {
    public:
      RunInformation();
      virtual ~RunInformation();
      /**
       * \brief Remove all information associated to the current run from this object
       */
      inline void Clear(Option_t*) {
        if (!fIPCollection) return;
        fIPCollection->clear();
      }
      
      /**
       * \brief Add an additional incoming particle to the present run
       * \param[in] ip The IncomingParticle object to store in this object's collection
       */
      inline void AddIncomingParticle(IncomingParticle* ip) { fIPCollection->push_back(ip); }
      /**
       * \brief Retrieve the information on an incoming particle from this object
       * \param[in] i The unique index of the particle to retrieve in this run
       * \return The IncomingParticle object containing all kinematic information from the
       * selected incoming particle
       */
      inline IncomingParticle* GetIncomingParticle(size_t i) const { return fIPCollection->at(i); }

      /**
       * \brief Retrieve the number of incoming particles simulated in this run.
       */
      inline size_t GetNumberOfIncomingParticles() const { return fIPCollection->size(); }
      /**
       * \brief Retrieve the mean energy (in GeV) deposited by all the incoming particles simulated
       * in this run
       */
      inline double GetMeanIncomingParticlesEnergy() const {
        if (!fIPCollection) return -1.;
	double esum = 0.;
	for (IncomingParticlesRef::iterator ip=fIPCollection->begin(); ip!=fIPCollection->end(); ip++) {
	  esum += (*ip)->GetMomentum()->E();
	}
	return esum/GetNumberOfIncomingParticles();
      }

    private:
      IncomingParticlesRef* fIPCollection;

    public:
      ClassDef(RunInformation, 1)
  };
}

#endif

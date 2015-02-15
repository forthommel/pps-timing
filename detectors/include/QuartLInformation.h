#ifndef QuartLInformation_h
#define QuartLInformation_h

#include <iostream>

#include "TObject.h"

namespace PPS
{
  class QuartLInformation : public TObject
  {
    public:
      QuartLInformation();
      virtual ~QuartLInformation();
   
      inline void SetRunId(int ri) { fRunId=ri; } 
      inline int GetRunId() const { return fRunId; }
      inline void SetProtonEnergy(double pe) { fProtonEnergy=pe; }
      inline double GetProtonEnergy() const { return fProtonEnergy; }
      
  
    private:
      int fRunId;
      double fProtonEnergy;
    
    public:
      //void Print(Option_t* opt="") const;
      ClassDef(QuartLInformation, 1)
  };
}

#endif

#ifndef QuartLRunInfo_hh
#define QuartLRunInfo_hh

#include <iostream>

#include "TObject.h"

namespace PPS
{
  class QuartLRunInfo : public TObject
  {
    public:
      QuartLRunInfo();
      virtual ~QuartLRunInfo();
   
      inline void SetRunId(int ri) { fRunId=ri; } 
      inline int GetRunId() const { return fRunId; }
      inline void SetProtonEnergy(double pe) { fProtonEnergy=pe; }
      inline double GetProtonEnergy() const { return fProtonEnergy; }
  
    private:
      int fRunId;
      double fProtonEnergy;
    
    public:
      ClassDef(QuartLRunInfo, 1)
      //void Print(Option_t* opt="") const;
  };
}

#endif

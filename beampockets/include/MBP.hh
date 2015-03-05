#ifndef MBP_h
#define MBP_h

#include "G4GDMLParser.hh"
#include "globals.hh"

#include "GeometryComponent.hh"

namespace MBP
{
  class MBP : public PPS::GeometryComponent
  {
  public:
    MBP(G4String name);
    virtual ~MBP();
    
  private:
    G4GDMLParser* fParser;
  };
}

#endif


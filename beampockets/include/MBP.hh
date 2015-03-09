#ifndef MBP_h
#define MBP_h

#include "G4GDMLParser.hh"
#include "globals.hh"

#include "GeometryComponentStore.hh"

namespace MBP
{
  class MBP : public PPS::GeometryComponent
  {
  public:
    MBP(G4String name="");
    virtual ~MBP();
    static G4String GetType() { return "MBP"; }
    
  private:
    G4GDMLParser* fParser;
  };
}

#endif

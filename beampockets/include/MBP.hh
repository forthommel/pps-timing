#ifndef MBP_h
#define MBP_h

#include "G4GDMLParser.hh"
#include "globals.hh"

#include "GeometryComponent.hh"

namespace MBP
{
  typedef enum {
    STAINLESS_STEEL,
    ALBEMET,
    BERYLLIUM
  } window_type;
  
  class MBP : public PPS::GeometryComponent
  {
  public:
    MBP(G4String name, window_type=STAINLESS_STEEL, G4bool only_window=false);
    virtual ~MBP();
    
  private:
    G4GDMLParser* fParser;
  };
}

#endif


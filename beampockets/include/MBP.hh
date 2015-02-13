#ifndef MBP_h
#define MBP_h

#include "G4GDMLParser.hh"

#include "globals.hh"

#include "Component.hh"

typedef enum {
  STAINLESS_STEEL,
  ALBEMET,
  BERYLLIUM
} window_type;

/// Detector construction class to define materials and geometry.

class MBP : public Component
{
public:
  MBP(G4String name, window_type=STAINLESS_STEEL, G4bool only_window=false);
  virtual ~MBP();
  
private:
  G4GDMLParser* fParser;
};

#endif


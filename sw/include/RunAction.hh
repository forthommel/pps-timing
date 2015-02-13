#ifndef RunAction_h
#define RunAction_h

#include "globals.hh"
#include "G4UserRunAction.hh"

#include "FileWriter.hh"
#include "MaterialManager.hh"

#include "TFile.h"
#include "TTree.h"

class G4Timer;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(FileWriter* analyzer=0);
    ~RunAction();

    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
    /** \brief Returns a pointer to the FileWriter object used to collect all tracks' information in an external ROOT tree */
    inline FileWriter* GetAnalyzer() { return fOutput; }
    inline MaterialManager* GetMaterialManager() { return fMaterialManager; }

  private:
    G4Timer* fTimer;
    FileWriter* fOutput;
    MaterialManager* fMaterialManager;
};

#endif

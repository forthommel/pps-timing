#ifndef EnvironmentalEvent_h
#define EnvironmentalEvent_h

#include "TObject.h"
#include "TH3.h"
#include "TLorentzVector.h"
#include <iostream>

class EnvironmentalHit;
class EnvironmentalEvent : public TObject
{
  public:
    EnvironmentalEvent(TString name="");
    virtual ~EnvironmentalEvent();
    
    inline TString GetSDName() const { return fName; }
    /**
     * \brief Reset the event after its storage to the output file
     */
    virtual void Clear(Option_t* opt="");
    
    void AddSecondaryHit(EnvironmentalHit hit);
    inline size_t GetNumberOfSecondaries() const { return fHits->size(); }
    
  private:
    TString fName;
    std::vector<EnvironmentalHit>* fHits;
    //TH3D* fHist;
    
  public:
    ClassDef(EnvironmentalEvent, 1)
};

class EnvironmentalHit : public TObject
{
  public:
    EnvironmentalHit() {;}
    virtual ~EnvironmentalHit() {;}
    
    inline void SetPosition(TLorentzVector pos) { fPosition=pos; }
    inline TLorentzVector GetPosition() const { return fPosition; }
    
    inline void SetVertexPosition(TLorentzVector pos) { fVtxPosition=pos; }
    inline TLorentzVector GetVertexPosition() const { return fVtxPosition; }
    
    inline void SetMomentum(TLorentzVector mom) { fMomentum=mom; }
    inline TLorentzVector GetMomentum() const { return fMomentum; }
    
    inline void SetPDGId(int pdg) { fPDGId=pdg; }
    inline int GetPDGId() const { return fPDGId; }

    void Dump() const;
    
  private:
    TLorentzVector fPosition;
    TLorentzVector fVtxPosition;
    TLorentzVector fMomentum;
    int fPDGId;
    
  public:
    ClassDef(EnvironmentalHit, 1)
};

#endif

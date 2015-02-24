#ifndef Canvas_h
#define Canvas_h

#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TStyle.h"

#include <sstream>

namespace PPS
{
  class Canvas : public TCanvas
  {
    public:
      Canvas();
      Canvas(TString, Int_t width_=560, Int_t height_=560, TString upper_label_="");
      Canvas(TString, TString upper_label_);
      virtual ~Canvas();

      void SetUpperLabel(TString text_="");
      void AddLegendEntry(const TObject*, TString label_="", Option_t* option_="lpf");
      void Save(TString filename="");
      inline TPad* Pad() { return c1; }

    private:
      void Build();
      
      TPad *c1, *c2;
      Double_t fWidth, fHeight;
      TLegend *fLegend;
      Double_t fLegendX, fLegendY;
      Int_t fLegendNumEntries;
      TPaveText *fLabel1, *fLabel2;
      TString fUpperLabelText;
      TPaveText *fUpperLabel;
      Bool_t fLabelsDrawn;

    public:
      ClassDef(Canvas, 1)
  };
}

#endif

#include "Canvas.h"

namespace PPS
{
  Canvas::Canvas() :
    TCanvas("null"),
    fLegend(0), fLegendX(.52), fLegendY(.76), fLegendNumEntries(0),
    fUpperLabel(0), fLabelsDrawn(false)
  {}

  Canvas::Canvas(TString name_, Int_t width_, Int_t height_, TString upper_label_) :
    TCanvas(name_, "", width_, height_),
    fWidth(width_), fHeight(height_),
    fLegend(0), fLegendX(.52), fLegendY(.76), fLegendNumEntries(0),
    fUpperLabelText(upper_label_), fUpperLabel(0),
    fLabelsDrawn(false)
  {
    Build();
  }

  Canvas::Canvas(TString name_, TString upper_label_) :
    TCanvas(name_, "", 560, 560),
    fWidth(560), fHeight(560),
    fLegend(0), fLegendX(.52), fLegendY(.76), fLegendNumEntries(0),
    fUpperLabelText(upper_label_), fUpperLabel(0),
    fLabelsDrawn(false)
  {
    Build();
  }

  Canvas::~Canvas()
  {
    delete fLegend;
    delete fUpperLabel;
  }

  void
  Canvas::Build()
  {
    gStyle->SetOptStat(0);
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerSize(.87);
    gStyle->SetTitle("");
    gStyle->SetTitleFont(43, "XYZ");
    gStyle->SetTitleSize(22, "XYZ");
    gStyle->SetLabelFont(43, "XYZ");
    gStyle->SetLabelSize(22, "XYZ");
    
    fLegend = new TLegend(fLegendX, fLegendY, fLegendX+.35, fLegendY+.12);
    fLegend->SetFillColor(kWhite);
    fLegend->SetLineColor(kWhite);
    fLegend->SetLineWidth(0);
    fLegend->SetTextFont(43);
    fLegend->SetTextSize(14);

    SetTicks(1, 1);
  }

  void
  Canvas::SetUpperLabel(TString text_)
  {
    fUpperLabelText = text_;
    fUpperLabel = new TPaveText(.37, .922, .9, .952, "NDC");
    fUpperLabel->SetMargin(0.);
    fUpperLabel->SetFillColor(kWhite);
    fUpperLabel->SetLineColor(kWhite);
    fUpperLabel->SetLineWidth(0);
    fUpperLabel->SetShadowColor(kWhite);
    fUpperLabel->SetTextFont(43);
    fUpperLabel->SetTextAlign(33);
    fUpperLabel->SetTextSize(18);
    fUpperLabel->AddText(fUpperLabelText);
    fUpperLabel->Draw();
  }

  void
  Canvas::AddLegendEntry(const TObject* obj_, TString label_, Option_t* option_)
  {
    fLegend->AddEntry(obj_, label_, option_);
    fLegendNumEntries++;
    if (fLegendNumEntries>3) {
      fLegend->SetY1(fLegend->GetY1()-(fLegendNumEntries-3)*0.01);
    }
  }

  void
  Canvas::Save(TString path_)
  {
    std::stringstream output;
    
    if (!fLabelsDrawn) {
      fLabel1 = new TPaveText(.115, .925, .2, .955, "NDC");
      fLabel1->AddText("PPS");
      fLabel1->SetMargin(0.);
      fLabel1->SetFillColor(kWhite);
      fLabel1->SetLineColor(kWhite);
      fLabel1->SetLineWidth(0);
      fLabel1->SetShadowColor(kWhite);
      fLabel1->SetTextFont(63);
      fLabel1->SetTextAlign(13);
      fLabel1->SetTextSize(22);
      fLabel1->Draw();
      fLabel2 = new TPaveText(.2, .93, .36, .955, "NDC");
      fLabel2->AddText("simulation");
      fLabel2->SetMargin(0.);
      fLabel2->SetFillColor(kWhite);
      fLabel2->SetLineColor(kWhite);
      fLabel2->SetLineWidth(0);
      fLabel2->SetShadowColor(kWhite);
      fLabel2->SetTextFont(43);
      fLabel2->SetTextAlign(13);
      fLabel2->SetTextSize(22);
      fLabel2->Draw();
      if (fLegend->GetNRows()!=0) fLegend->Draw();
      SetUpperLabel(fUpperLabelText);
      fLabelsDrawn = true;
    }
    output.str(""); output << path_ << ".png";
    SaveAs(output.str().c_str());
    output.str(""); output << path_ << ".pdf";
    SaveAs(output.str().c_str());
    //output.str(""); output << path_ << ".root";
    ////SaveAs(output.str().c_str());
    //}
  }
}

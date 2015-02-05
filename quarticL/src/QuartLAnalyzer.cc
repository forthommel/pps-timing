#include "QuartLAnalyzer.hh"

QuartLAnalyzer::QuartLAnalyzer() :
  tree(0)
{
  tree = new TTree("events", "Quartic simulation events");
}

QuartLAnalyzer::~QuartLAnalyzer()
{
  delete tree;
}

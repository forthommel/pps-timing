#ifndef QuartLAnalyzer_h
#define QuartLAnalyzer_h

#include "TTree.h"

class QuartLAnalyzer
{
  public:
    QuartLAnalyzer();
    ~QuartLAnalyzer();
  
  private:
    TTree *tree;
};

#endif

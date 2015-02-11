#ifndef QuartLEvent_h
#define QuartLEvent_h

#include <vector>

#include "TObject.h"

namespace PPS
{
  class QuartLEvent : public TObject
  {
    public:
      QuartLEvent();
      virtual ~QuartLEvent();

      ClassDef(QuartLEvent, 1)

    private:
      std::vector<int> fTest;
  };
}

#endif

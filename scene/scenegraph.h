#ifndef SCENEGRAPHH
#define SCENEGRAPHH

#include <vector>
#include "hitable/hitable.h"
#include "hitable/hitable_compose.h"

namespace film {

namespace scene {

class scenegraph {
public:
  scenegraph();
  ~scenegraph();
  hitable::hitable* GetObjects() const;
  void Build();
private:
  hitable::hitable_compose* hitable_compose;
};

}

}

#endif

#ifndef SCENEGRAPHH
#define SCENEGRAPHH

#include <vector>
#include "hitable/hitable.h"

namespace film {

namespace scene {

class scenegraph {
public:
  scenegraph();
  ~scenegraph();
  std::vector<hitable::hitable*> GetObjects() const;
  void build();
private:
  std::vector<hitable::hitable*> objects;
};

}

}

#endif

#ifndef SKELETONOBJECT_HPP
#define SKELETONOBJECT_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class SkeletonObject : public UrsineEngine::GameObject
  {
    public:

      /**
       * Constructor.
       */
      SkeletonObject(const std::string& aName);
  };
}

#endif

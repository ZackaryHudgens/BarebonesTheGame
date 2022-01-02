#ifndef BOARDOBJECT_HPP
#define BOARDOBJECT_HPP

#include <GameObject.hpp>

#include "TileObject.hpp"

namespace Barebones
{
  class BoardObject : public UrsineEngine::GameObject
  {
    public:

      /**
       * Constructor.
       */
      BoardObject(const std::string& aName);
  };
}

#endif

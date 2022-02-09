#ifndef BOARDFACTORY_HPP
#define BOARDFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class BoardFactory
  {
    public:

      /**
       * Creates a board GameObject and adds the proper components,
       * then returns it as a std::unique_ptr.
       *
       * @param aName The name of the new board.
       * @return A unique pointer to a new GameObject.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateBoard(const std::string& aName);
  };
}

#endif

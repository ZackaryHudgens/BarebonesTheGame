#ifndef MENUFACTORY_HPP
#define MENUFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class MenuFactory
  {
    public:

      /**
       * Creates a GameObject with a MenuLayoutComponent and a
       * MenuInputComponent, then returns it as a unique_ptr.
       *
       * @param aType The type of action to create.
       * @param aName The name of the new action.
       * @return A unique pointer to a new action object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateMenu(const std::string& aName);
  };
}

#endif

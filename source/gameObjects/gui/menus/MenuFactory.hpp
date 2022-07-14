#ifndef MENUFACTORY_HPP
#define MENUFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class MenuType
  {
    eMAIN,
    eOPTIONS,
    eRESOLUTION,
    eWINDOW_TYPE,
    ePAUSE,
    eSKILL,
    eREWARDS
  };

  class MenuFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of menu given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of menu to create.
       * @param aName The name of the new menu.
       * @return A unique pointer to a new menu object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateMenu(const MenuType& aType,
                                                                  const std::string& aName);
  };
}

#endif

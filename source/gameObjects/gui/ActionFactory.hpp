#ifndef ACTIONFACTORY_HPP
#define ACTIONFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class ActionType
  {
    eSKILL
  };

  class ActionFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of action given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of action to create.
       * @param aName The name of the new action.
       * @return A unique pointer to a new action object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateAction(const ActionType& aType,
                                                                    const std::string& aName);
  };
}

#endif

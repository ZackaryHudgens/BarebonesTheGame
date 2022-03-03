#ifndef PLAYERFACTORY_HPP
#define PLAYERFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class PlayerType
  {
    eARTIFICIAL,
    eHUMAN
  };

  class PlayerFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of player given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of player to create.
       * @param aName The name of the new player.
       * @return A unique pointer to a new game object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreatePlayer(const PlayerType& aType,
                                                                    const std::string& aName);
  };
}

#endif

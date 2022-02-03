#ifndef CHARACTERFACTORY_HPP
#define CHARACTERFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class CharacterType
  {
    eBASIC_SKELETON,
    eBASIC_HUMAN
  };

  class CharacterFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of character given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of character to create.
       * @param aName The name of the new character.
       * @return A unique pointer to a new game object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateCharacter(const CharacterType& aType,
                                                                       const std::string& aName);
  };
}

#endif

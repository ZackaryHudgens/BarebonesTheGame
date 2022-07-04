#ifndef CHARACTERDEFAULTSTATE_HPP
#define CHARACTERDEFAULTSTATE_HPP

#include "CharacterState.hpp"

namespace Barebones
{
  class CharacterDefaultState : public CharacterState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this state.
       */
      CharacterDefaultState(UrsineEngine::GameObject& aCharacter);

      /**
       * A handler function that gets called whenever the parent character
       * is told to move to a position in world space.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed at which to move.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> HandleMovementRequested(const glm::vec3& aPosition,
                                                              double aSpeed) override;

      /**
       * A handler function that gets called whenever the parent character
       * receives damage.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> HandleDamageReceived() override;

      /**
       * A handler function that gets called whenever the parent character dies.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> HandleCharacterDied() override;
  };
}

#endif

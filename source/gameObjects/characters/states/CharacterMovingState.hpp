#ifndef CHARACTERMOVINGSTATE_HPP
#define CHARACTERMOVINGSTATE_HPP

#include "CharacterState.hpp"

namespace Barebones
{
  class CharacterMovingState : public CharacterState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this state.
       * @param aPosition The position to move to.
       * @param aSpeed The speed to move at.
       */
      CharacterMovingState(UrsineEngine::GameObject& aCharacter,
                           const glm::vec3& aPosition,
                           double aSpeed);

      /**
       * Gets called whenever the character exits this state.
       */
      void OnExit() override;

      /**
       * A function that gets called during the parent character's Update().
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> Update(double aTime) override;

    private:
      glm::vec3 mTargetPosition;
      double mSpeed;
  };
}

#endif

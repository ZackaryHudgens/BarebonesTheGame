#ifndef CHARACTERDYINGSTATE_HPP
#define CHARACTERDYINGSTATE_HPP

#include "CharacterState.hpp"

namespace Barebones
{
  class CharacterDyingState : public CharacterState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this state.
       */
      CharacterDyingState(UrsineEngine::GameObject& aCharacter);

      /**
       * Gets called whenever the character enters this state.
       */
      void OnEnter() override;

      /**
       * A function that gets called during the parent character's Update().
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> Update(double aTime) override;

    private:
      double mFadeValue;
      double mFadeSpeed;
  };
}

#endif

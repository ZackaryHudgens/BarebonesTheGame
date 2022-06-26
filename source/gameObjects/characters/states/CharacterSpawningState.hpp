#ifndef CHARACTERSPAWNINGSTATE_HPP
#define CHARACTERSPAWNINGSTATE_HPP

#include "CharacterState.hpp"

namespace Barebones
{
  class CharacterSpawningState : public CharacterState
  {
    public:

      /**
       * Constructor.
       */
      CharacterSpawningState(UrsineEngine::GameObject& aCharacter);

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

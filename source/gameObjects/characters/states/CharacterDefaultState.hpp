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
       * A function that gets called during the parent character's Update().
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CharacterState> Update(double aTime) override;
  };
}

#endif

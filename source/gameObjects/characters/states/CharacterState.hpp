#ifndef CHARACTERSTATE_HPP
#define CHARACTERSTATE_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class CharacterState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this state.
       */
      CharacterState(UrsineEngine::GameObject& aCharacter);
      virtual ~CharacterState() {}

      /**
       * A virtual function that gets called during the parent character's
       * Update().
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CharacterState> Update(double aTime) = 0;

    protected:

      /**
       * Returns a pointer to the parent character GameObject.
       *
       * @return A pointer to the parent character GameObject.
       */
      UrsineEngine::GameObject* GetCharacter() { return mCharacter; }

    private:
      UrsineEngine::GameObject* mCharacter;
  };
}

#endif

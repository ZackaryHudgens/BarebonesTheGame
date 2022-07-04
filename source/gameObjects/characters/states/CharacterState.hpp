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
       * A virtual function that gets called whenever the character enters
       * this state.
       */
      virtual void OnEnter() {}

      /**
       * A virtual function that gets called whenever the character exits
       * this state.
       */
      virtual void OnExit() {}

      /**
       * A virtual function that gets called during the parent character's
       * Update().
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CharacterState> Update(double aTime) { return nullptr; };

      /**
       * A virtual function that gets called whenever the parent character
       * is told to move to a position in world space.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed at which to move.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CharacterState> HandleMovementRequested(const glm::vec3& aPosition,
                                                                      double aSpeed) { return nullptr; }

      /**
       * A virtual function that gets called whenever the parent character
       * receives damage.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CharacterState> HandleDamageReceived() { return nullptr; };

      /**
       * A virtual function that gets called whenever the parent character dies.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CharacterState> HandleCharacterDied() { return nullptr; };

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

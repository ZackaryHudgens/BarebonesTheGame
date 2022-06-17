#ifndef HUMANPLAYERPLACINGCHARACTERINPUTSTATE_HPP
#define HUMANPLAYERPLACINGCHARACTERINPUTSTATE_HPP

#include "HumanPlayerInputState.hpp"

#include "CharacterFactory.hpp"

namespace Barebones
{
  class HumanPlayerPlacingCharacterInputState : public HumanPlayerInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The player GameObject to handle input for.
       * @param aType The type of character to place.
       * @param aRemove Whether a removal of a character is required first
       *                before adding a new one.
       */
      HumanPlayerPlacingCharacterInputState(UrsineEngine::GameObject& aPlayer,
                                            const CharacterType& aType,
                                            bool aRemove);

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      std::unique_ptr<HumanPlayerInputState> HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                              int aMods) override;

      /**
       * A handler function that gets called whenever the user holds
       * a key down long enough to repeat the input.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      std::unique_ptr<HumanPlayerInputState> HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                               int aMods) override;

    private:
      CharacterType mType;

      bool mRemovalRequired;
  };
}

#endif

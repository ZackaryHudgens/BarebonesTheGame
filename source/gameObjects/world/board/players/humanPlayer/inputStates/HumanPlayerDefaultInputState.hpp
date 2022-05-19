#ifndef HUMANPLAYERDEFAULTINPUTSTATE_HPP
#define HUMANPLAYERDEFAULTINPUTSTATE_HPP

#include "HumanPlayerInputState.hpp"

namespace Barebones
{
  class HumanPlayerDefaultInputState : public HumanPlayerInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The player GameObject to handle input for.
       */
      HumanPlayerDefaultInputState(UrsineEngine::GameObject& aPlayer);

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

      /**
       * Creates a skill menu for a given character and adds it to the
       * current scene.
       *
       * @param aCharacter The character in question.
       */
      void CreateSkillMenu(UrsineEngine::GameObject& aCharacter);

      /**
       * Creates a spell menu for the current player and adds it to the
       * current scene.
       *
       * @param aPlayer The player GameObject.
       */
      void CreateSpellMenu(UrsineEngine::GameObject& aPlayer);
  };
}

#endif

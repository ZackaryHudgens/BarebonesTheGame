#ifndef HUMANPLAYERINPUTCOMPONENT_HPP
#define HUMANPLAYERINPUTCOMPONENT_HPP

#include <Component.hpp>

#include "CharacterSkillComponent.hpp"

#include "HumanPlayerInputState.hpp"
#include "InputComponent.hpp"

namespace Barebones
{
  class HumanPlayerInputComponent : public InputComponent
  {
    public:

      /**
       * Constructor.
       */
      HumanPlayerInputComponent();

      /**
       * Sets whether this component should accept input. If this component
       * is disabled, it will not respond to input.
       *
       * @param aEnabled Whether to enable or disable this component.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       */
      void HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
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
      void HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                             int aMods) override;

    private:

      /**
       * A handler function that gets called whenever the user
       * selects a skill to use from a menu.
       *
       * @param aSkill The skill component that was selected.
       */
      void HandleSkillSelected(CharacterSkillComponent& aSkill);

      std::unique_ptr<HumanPlayerInputState> mState;

      bool mEnabled;
  };
}

#endif

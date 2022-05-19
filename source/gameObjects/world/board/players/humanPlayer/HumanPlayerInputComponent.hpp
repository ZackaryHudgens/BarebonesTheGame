#ifndef HUMANPLAYERINPUTCOMPONENT_HPP
#define HUMANPLAYERINPUTCOMPONENT_HPP

#include <Component.hpp>

#include "InputComponent.hpp"

#include "HumanPlayerInputState.hpp"

#include "Skill.hpp"

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
       * Sets the board that this component should operate on.
       *
       * @param aBoard The board to operate on.
       */
      void SetBoard(UrsineEngine::GameObject& aBoard);

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

    protected:

      /**
       * Initializes the component by creating a default state object.
       */
      void ProtectedInitialize() override;

      /**
       * A handler function that gets called whenever a skill is selected.
       *
       * @param aSkill The skill that was selected.
       */
      void HandleSkillSelected(Skill& aSkill);

    private:

      UrsineEngine::GameObject* mBoard;

      std::unique_ptr<HumanPlayerInputState> mState;

      bool mEnabled;
  };
}

#endif

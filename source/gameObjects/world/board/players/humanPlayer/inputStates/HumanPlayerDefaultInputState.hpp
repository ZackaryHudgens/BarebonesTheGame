#ifndef HUMANPLAYERDEFAULTINPUTSTATE_HPP
#define HUMANPLAYERDEFAULTINPUTSTATE_HPP

#include "HumanPlayerInputState.hpp"

#include "Skill.hpp"

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
       * Populates a given menu GameObject with an action for each skill
       * in the given list of skills.
       *
       * @param aMenu The menu to populate.
       * @param aSkills A list of skills to create actions for.
       */
      void PopulateSkillMenu(UrsineEngine::GameObject& aMenu,
                             const std::vector<Skill*>& aSkills);
  };
}

#endif

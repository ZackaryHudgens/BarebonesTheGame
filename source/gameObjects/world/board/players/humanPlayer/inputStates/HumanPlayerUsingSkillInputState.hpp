#ifndef HUMANPLAYERUSINGSKILLINPUTSTATE_HPP
#define HUMANPLAYERUSINGSKILLINPUTSTATE_HPP

#include "HumanPlayerMovableInputState.hpp"

#include "Skill.hpp"

namespace Barebones
{
  class HumanPlayerUsingSkillInputState : public HumanPlayerMovableInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The player GameObject to handle input for.
       * @param aSkill The skill that is being used.
       */
      HumanPlayerUsingSkillInputState(UrsineEngine::GameObject& aPlayer,
                                      Skill& aSkill);

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
       * A virtual function that gets called whenever the user holds
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
      Skill* mSkill;
  };
}

#endif

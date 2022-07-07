#ifndef HUMANPLAYERINITIALBEHAVIORSTATE_HPP
#define HUMANPLAYERINITIALBEHAVIORSTATE_HPP

#include "HumanPlayerBehaviorState.hpp"

namespace Barebones
{
  class HumanPlayerInitialBehaviorState : public HumanPlayerBehaviorState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The human player this state represents.
       */
      HumanPlayerInitialBehaviorState(UrsineEngine::GameObject& aPlayer);

      /**
       * Gets called when the player enters this state.
       */
      void OnEnter() override;

      /**
       * A handler function that gets called whenever a character finishes
       * its spawning animation.
       *
       * @param aCharacter The character that finished the animation.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HumanPlayerBehaviorState> HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter) override;
  };
}

#endif

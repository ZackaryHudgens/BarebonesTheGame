#ifndef HUMANPLAYERINITIALBEHAVIORSTATE_HPP
#define HUMANPLAYERINITIALBEHAVIORSTATE_HPP

#include "HumanPlayerBehaviorState.hpp"

#include <Observer.hpp>

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
       * Gets called when the player exits this state.
       */
      void OnExit() override;

      /**
       * A handler function that gets called whenever a character finishes
       * its spawning animation.
       *
       * @param aCharacter The character that finished the animation.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HumanPlayerBehaviorState> HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter) override;

    private:

      /**
       * A handler function that gets called whenever the board has finished
       * placing and loading tiles, and is ready to add characters to.
       *
       * @param aBoard The board that finished.
       */
      void HandleBoardFinishedInitialSequence(UrsineEngine::GameObject& aBoard);

      std::vector<CharacterType> mSkeletonsToSpawn;
      std::vector<UrsineEngine::GameObject*> mSpawningSkeletons;

      UrsineEngine::Observer mObserver;
  };
}

#endif

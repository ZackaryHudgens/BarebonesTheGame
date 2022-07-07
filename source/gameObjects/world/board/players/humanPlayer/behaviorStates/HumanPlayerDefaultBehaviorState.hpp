#ifndef HUMANPLAYERDEFAULTBEHAVIORSTATE_HPP
#define HUMANPLAYERDEFAULTBEHAVIORSTATE_HPP

#include "HumanPlayerBehaviorState.hpp"

namespace Barebones
{
  class HumanPlayerDefaultBehaviorState : public HumanPlayerBehaviorState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The human player this state represents.
       */
      HumanPlayerDefaultBehaviorState(UrsineEngine::GameObject& aPlayer);

      /**
       * A handler function that gets called whenever a character is
       * selected from the rewards menu.
       *
       * @param aType The type of character selected.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HumanPlayerBehaviorState> HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType) override;
  };
}

#endif

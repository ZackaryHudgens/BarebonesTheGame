#ifndef BOARDTURNMANAGERCOMPONENT_HPP
#define BOARDTURNMANAGERCOMPONENT_HPP

#include <Component.hpp>

#include "PlayerBehaviorComponent.hpp"

namespace Barebones
{
  class BoardTurnManagerComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardTurnManagerComponent();

      /**
       * "Starts" the turn manager by making the first player take
       * a turn. As turns are ended, the turn tracker will update.
       */
      void Start();

      /**
       * Adds a player to the turn manager by taking ownership of it,
       * adding it as a child object, and keeping a pointer to the
       * PlayerBehaviorComponent in the turn tracker.
       *
       * @param aPlayer The player to add.
       */
      void AddPlayer(std::unique_ptr<UrsineEngine::GameObject> aPlayer);

    private:

      /**
       * A handler function that gets called whenever a player's turn
       * ends.
       *
       * @param aPlayer The player whose turn ended.
       */
      void HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      std::vector<PlayerBehaviorComponent*> mTurnTracker;
  };
}

#endif

#ifndef BOARDTURNMANAGERCOMPONENT_HPP
#define BOARDTURNMANAGERCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "PlayerBehaviorComponent.hpp"

namespace Barebones
{
  /**
   * The BoardTurnManagerComponent provides a means to add players
   * to the board and allow them to take turns.
   */
  class BoardTurnManagerComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardTurnManagerComponent();

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * Adds a player to the turn manager by taking ownership of it,
       * adding it as a child object, and keeping a pointer to the
       * PlayerBehaviorComponent in the turn tracker.
       *
       * @param aPlayer The player to add.
       */
      void AddPlayer(std::unique_ptr<UrsineEngine::GameObject> aPlayer);

      /**
       * Returns the currently active player.
       *
       * @return The currently active player, or nullptr if there is none.
       */
      UrsineEngine::GameObject* GetCurrentPlayer();

    private:

      /**
       * Creates a turn display and adds it to the current scene's
       * foreground. When the turn display finishes, the player in
       * the front of the turn list will take their turn.
       */
      void CreateTurnDisplay();

      /**
       * A handler function that gets called whenever a player's turn
       * ends.
       *
       * @param aPlayer The player whose turn ended.
       */
      void HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a wave finishes spawning
       * on a given board.
       *
       * @param aBoard The board that the wave finished spawning on.
       */
      void HandleWaveFinishedSpawning(UrsineEngine::GameObject& aBoard);

      /**
       * A handler function that gets called whenever a GameObject
       * is about to be deleted.
       *
       * @param aObject The GameObject that's about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);

      UrsineEngine::GameObject* mTurnDisplay;
      std::vector<UrsineEngine::GameObject*> mTurnTracker;
      std::vector<UrsineEngine::GameObject*> mInitialTurnOrder;

      bool mWaitingToTakeTurn;
  };
}

#endif

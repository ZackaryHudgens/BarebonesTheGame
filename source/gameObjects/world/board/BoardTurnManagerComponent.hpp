#ifndef BOARDTURNMANAGERCOMPONENT_HPP
#define BOARDTURNMANAGERCOMPONENT_HPP

#include <Component.hpp>
#include <Signal.hpp>

#include "PlayerBehaviorComponent.hpp"
#include "TurnDisplayComponent.hpp"

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
       * Updates the turn manager.
       */
      void Update() override;

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

      /**
       * Returns the currently active player.
       *
       * @return The currently active player, or nullptr if there is none.
       */
      UrsineEngine::GameObject* GetCurrentPlayer();

    private:

      /**
       * Creates a turn display and adds it to the current scene's
       * canvas. When the turn display finishes, the player in
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
       * A handler function that gets called whenever the turn
       * display finishes its animation.
       *
       * @param aDisplay The display in question.
       */
      void HandleTurnDisplayFinished(TurnDisplayComponent& aDisplay);

      std::vector<UrsineEngine::GameObject*> mTurnTracker;
      TurnDisplayComponent* mTurnDisplay;

      bool mWaitingForDisplay;
      bool mWaitingToTakeTurn;
  };

  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnBeganSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnEndedSignal;

  extern PlayerTurnBeganSignal   PlayerTurnBegan;
  extern PlayerTurnEndedSignal   PlayerTurnEnded;
}

#endif

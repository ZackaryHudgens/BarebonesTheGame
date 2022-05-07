#ifndef ENEMYBEHAVIORCOMPONENT_HPP
#define ENEMYBEHAVIORCOMPONENT_HPP

#include "CharacterBehaviorComponent.hpp"

#include "TileUtil.hpp"

namespace Barebones
{
  class EnemyBehaviorComponent : public CharacterBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      EnemyBehaviorComponent();

      /**
       * A virtual function that gets called by the AI player. This function
       * should be overridden to provide functionality when it is this
       * character's turn.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) = 0;

    protected:

      /**
       * A virtual function that determines the cost of moving from one tile to another,
       * represented by an integer. By default, this function returns 1 for any two tiles.
       * Note that it is assumed movement between the two tiles is possible.
       *
       * @param aInitialLocation The initial tile location.
       * @param aTargetLocation The tile to move to.
       * @return The cost of moving from aInitialLocation to aTargetLocation.
       */
      virtual int CalculateCostofMovement(const TileLocation& aInitialLocation,
                                          const TileLocation& aTargetLocation) const;

      /**
       * Generates a TileAdjacencyGraph using this character's GetMovements()
       * function for each tile on the board.
       *
       * @param aBoard The board to generate a graph for.
       * @return A TileAdjacencyGraph for the given board.
       */
      TileAdjacencyGraph GenerateGraph(UrsineEngine::GameObject& aBoard) const;

      /**
       * Ends this character's turn and notifies the CharacterTurnEnded Signal.
       */
      void EndTurn();
  };
}

#endif

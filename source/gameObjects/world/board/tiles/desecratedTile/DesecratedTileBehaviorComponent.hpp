#ifndef DESECRATEDTILEBEHAVIORCOMPONENT_HPP
#define DESECRATEDTILEBEHAVIORCOMPONENT_HPP

#include <GameObject.hpp>

#include "TileBehaviorComponent.hpp"

namespace Barebones
{
  class DesecratedTileBehaviorComponent : public TileBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      DesecratedTileBehaviorComponent();

      /**
       * A virtual function that gets called whenever a character ends the turn
       * on this tile.
       *
       * @param aCharacter The character GameObject that ended the turn on this tile.
       */
      void HandleTurnEnded(UrsineEngine::GameObject& aCharacter) override;
  };
}

#endif

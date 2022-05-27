#ifndef DIAGONALCHARACTERMOVER_HPP
#define DIAGONALCHARACTERMOVER_HPP

#include "CharacterMover.hpp"

namespace Barebones
{
  class DiagonalCharacterMover : public CharacterMover
  {
    public:

      /**
       * Returns a list of possible movements given a location on a board.
       *
       * @param aObject A GameObject containing a BoardLoyoutComponent.
       * @param aLocation The initial location.
       * @return A list of possible movements.
       */
      TileList GetMovements(UrsineEngine::GameObject& aObject,
                            const TileLocation& aLocation) const override;
  };
}

#endif

#ifndef CHARACTERMOVER_HPP
#define CHARACTERMOVER_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  /**
   * A mover determines what spaces are legal for a character to move
   * to on a board.
   *
   * If you want to move the character in 3D space, you want the
   * MoveToPosition() function in CharacterBehaviorComponent.
   */
  class CharacterMover
  {
    public:

      /**
       * A virtual function that returns a list of possible movements
       * given a location on a board.
       *
       * @param aObject A GameObject containing a BoardLoyoutComponent.
       * @param aLocation The initial location.
       * @return A list of possible movements.
       */
      virtual TileList GetMovements(UrsineEngine::GameObject& aObject,
                                    const TileLocation& aLocation) const = 0;
  };
}

#endif

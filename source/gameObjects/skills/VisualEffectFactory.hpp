#ifndef VISUALEFFECTFACTORY_HPP
#define VISUALEFFECTFACTORY_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  enum class VisualEffectType
  {
    eCLAW,
    eBONE_THROW,
    eTENTACLE_SLAP
  };

  class VisualEffectFactory
  {
    public:

      /**
       * Creates a visual effect based on the given type, placed on the
       * given board at the given location.
       *
       * @param aName The name of the new GameObject.
       * @param aType The type of visual effect to create.
       * @param aBoard The board to create a visual effect for.
       * @param aSourceLocation The location of the character using a skill.
       * @param aTargetLocation The location on the board to create a visual effect.
       * @return A unique pointer to a new visual effect.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateVisualEffect(const std::string& aName,
                                                                          const VisualEffectType& aType,
                                                                          UrsineEngine::GameObject& aBoard,
                                                                          const TileLocation& aSourceLocation,
                                                                          const TileLocation& aTargetLocation);
  };
}

#endif

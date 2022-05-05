#ifndef BURNINGEFFECT_HPP
#define BURNINGEFFECT_HPP

#include "Effect.hpp"

namespace Barebones
{
  class BurningEffect : public Effect
  {
    public:

      /**
       * Constructor.
       */
      BurningEffect();

      /**
       * Returns an icon for this effect as a MeshComponent.
       *
       * @return An icon mesh for this effect.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() const override;
  };
}

#endif

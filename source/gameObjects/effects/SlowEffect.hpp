#ifndef SLOWEFFECT_HPP
#define SLOWEFFECT_HPP

#include "Effect.hpp"

namespace Barebones
{
  class SlowEffect : public Effect
  {
    public:

      /**
       * Constructor.
       */
      SlowEffect();

      /**
       * Returns an icon for this effect as a MeshComponent.
       *
       * @return An icon mesh for this effect.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() const override;
  };
}

#endif

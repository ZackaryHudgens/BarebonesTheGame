#ifndef TESTEFFECT_HPP
#define TESTEFFECT_HPP

#include "Effect.hpp"

namespace Barebones
{
  class TestEffect : public Effect
  {
    public:

      /**
       * Constructor.
       */
      TestEffect();

      /**
       * A function that returns an icon for this effect as a MeshComponent.
       *
       * @return An icon mesh for this effect.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() const override;
  };
}

#endif

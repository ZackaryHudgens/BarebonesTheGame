#ifndef DEFAULTTILEMESHCOMPONENT_HPP
#define DEFAULTTILEMESHCOMPONENT_HPP

#include "TileMeshComponent.hpp"

namespace Barebones
{
  class DefaultTileMeshComponent : public TileMeshComponent
  {
    public:

      /**
       * Constructor.
       */
      DefaultTileMeshComponent();

    protected:

      /**
       * Sets up any necessary vertices.
       */
      void SetupVertices() override;

      /**
       * Sets up any necessary textures.
       */
      void SetupTextures() override;

      /**
       * Sets up any necessary shaders.
       */
      void SetupShaders() override;
  };
}

#endif

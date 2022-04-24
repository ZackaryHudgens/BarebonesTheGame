#ifndef DESECRATEDTILEMESHCOMPONENT_HPP
#define DESECRATEDTILEMESHCOMPONENT_HPP

#include "TileMeshComponent.hpp"

namespace Barebones
{
  class DesecratedTileMeshComponent : public TileMeshComponent
  {
    public:

      /**
       * Constructor.
       */
      DesecratedTileMeshComponent();

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

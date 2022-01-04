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
       * Loads any necessary vertices.
       */
      void LoadVertices();

      /**
       * Loads any necessary textures.
       */
      void LoadTextures();

      /**
       * Loads any necessary shaders.
       */
      void LoadShaders();
  };
}

#endif

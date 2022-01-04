#ifndef TILEMESHCOMPONENT_HPP
#define TILEMESHCOMPONENT_HPP

#include <MeshComponent.hpp>

namespace Barebones
{
  class TileMeshComponent : public UrsineEngine::MeshComponent
  {
    public:

      /**
       * Constructor.
       */
      TileMeshComponent();

      /**
       * Loads the component, along with any vertices, textures,
       * and shaders, by calling the protected virtual functions.
       */
      void Load() override;

    protected:

      /**
       * Loads any necessary vertices.
       */
      virtual void LoadVertices() {};

      /**
       * Loads any necessary textures.
       */
      virtual void LoadTextures() {};

      /**
       * Loads any necessary shaders.
       */
      virtual void LoadShaders() {}

      double mWidth;
      double mHeight;
      double mLength;
  };
}

#endif

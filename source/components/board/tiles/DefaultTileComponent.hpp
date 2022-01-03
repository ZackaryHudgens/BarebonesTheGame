#ifndef DEFAULTTILECOMPONENT_HPP
#define DEFAULTTILECOMPONENT_HPP

#include "TileBehaviorComponent.hpp"

namespace Barebones
{
  class DefaultTileComponent : public TileBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      DefaultTileComponent();

    protected:

      /**
       * Initializes the vertex information by creating a cube.
       *
       * @param aMesh The mesh to initialize.
       */
      void SetupVertexInfo(UrsineEngine::MeshComponent& aMesh);

      /**
       * Initializes the texture information for the cube.
       *
       * @param aMesh The mesh to initialize.
       */
      void SetupTextureInfo(UrsineEngine::MeshComponent& aMesh);

      /**
       * Initializes the shader information for the cube.
       *
       * @param aMesh The mesh to initialize.
       */
      void SetupShaderInfo(UrsineEngine::MeshComponent& aMesh);
  };
}

#endif

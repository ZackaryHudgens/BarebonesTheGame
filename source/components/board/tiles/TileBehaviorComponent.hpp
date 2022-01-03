#ifndef TILEBEHAVIORCOMPONENT_HPP
#define TILEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <MeshComponent.hpp>

namespace Barebones
{
  class TileBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      TileBehaviorComponent();

      /**
       * Loads the component.
       */
      void Load() override;

    protected:

      /**
       * Initializes the vertex information by creating a cube.
       *
       * This should be overridden for each tile type.
       *
       * @param aMesh The mesh to initialize.
       */
      virtual void SetupVertexInfo(UrsineEngine::MeshComponent& aMesh) {};

      /**
       * Initializes the texture information for the cube.
       *
       * This should be overridden for each tile type.
       *
       * @param aMesh The mesh to initialize.
       */
      virtual void SetupTextureInfo(UrsineEngine::MeshComponent& aMesh) {};

      /**
       * Initializes the shader information for the cube.
       *
       * This should be overridden for each tile type.
       *
       * @param aMesh The mesh to initialize.
       */
      virtual void SetupShaderInfo(UrsineEngine::MeshComponent& aMesh) {};

      double mWidth;
      double mHeight;
      double mLength;
  };
}

#endif

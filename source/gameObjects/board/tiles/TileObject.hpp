#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <GameObject.hpp>
#include <MeshComponent.hpp>

namespace Barebones
{
  class TileObject : public UrsineEngine::GameObject
  {
    public:

      /**
       * Constructor.
       */
      TileObject(const std::string& aName);

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

      double mWidth;
      double mHeight;
      double mLength;
  };
}

#endif

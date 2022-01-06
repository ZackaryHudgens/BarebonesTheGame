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

      /**
       * Returns the width of this tile in model space coordinates.
       *
       * @return The width of this tile in model space coordinates.
       */
      double GetWidth() const { return mWidth; }

      /**
       * Returns the height of this tile in model space coordinates.
       *
       * @return The height of this tile in model space coordinates.
       */
      double GetHeight() const { return mHeight; }

      /**
       * Returns the width of this tile in model space coordinates.
       *
       * @return The width of this tile in model space coordinates.
       */
      double GetLength() const { return mLength; }

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

    private:
      double mWidth;
      double mHeight;
      double mLength;
  };
}

#endif

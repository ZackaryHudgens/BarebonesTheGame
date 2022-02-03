#ifndef CHARACTERMENUMESHCOMPONENT_HPP
#define CHARACTERMENUMESHCOMPONENT_HPP

#include <MeshComponent.hpp>

namespace Barebones
{
  class CharacterMenuMeshComponent : public UrsineEngine::MeshComponent
  {
    public:

      /**
       * Constructor.
       */
      CharacterMenuMeshComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Sets the width of the mesh.
       *
       * @param aWidth The width of the mesh in pixels.
       */
      void SetWidth(int aWidth);

      /**
       * Sets the height of the mesh.
       *
       * @param aHeight The height of the mesh in pixels.
       */
      void SetHeight(int aHeight);

    private:

      /**
       * Sets up any necessary vertices.
       */
      void SetupVertices();

      /**
       * Sets up any necessary textures.
       */
      void SetupTextures();

      /**
       * Sets up any necessary shaders.
       */
      void SetupShaders();

      int mWidth;
      int mHeight;
  };
}

#endif

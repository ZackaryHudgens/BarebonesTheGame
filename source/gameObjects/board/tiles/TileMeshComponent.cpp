#include "TileMeshComponent.hpp"

using Barebones::TileMeshComponent;

/******************************************************************************/
TileMeshComponent::TileMeshComponent()
  : MeshComponent()
  , mWidth(1.0)
  , mHeight(1.0)
  , mLength(1.0)
{
}

/******************************************************************************/
void TileMeshComponent::Load()
{
  LoadVertices();
  LoadTextures();
  LoadShaders();
}

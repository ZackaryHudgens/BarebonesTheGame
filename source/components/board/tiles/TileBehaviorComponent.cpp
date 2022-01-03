#include "TileBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mWidth(1.0)
  , mHeight(1.0)
  , mLength(1.0)
{
}

/******************************************************************************/
void TileBehaviorComponent::Load()
{
  // Create a mesh, then pass it to the virtual setup functions
  // and add it to the parent object as a component.
  auto mesh = std::make_unique<UrsineEngine::MeshComponent>();
  SetupVertexInfo(*mesh.get());
  SetupTextureInfo(*mesh.get());
  SetupShaderInfo(*mesh.get());

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddComponent(std::move(mesh));
  }
}

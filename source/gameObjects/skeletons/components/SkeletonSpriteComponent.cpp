#include "SkeletonSpriteComponent.hpp"

using Barebones::SkeletonSpriteComponent;

/******************************************************************************/
SkeletonSpriteComponent::SkeletonSpriteComponent()
  : SpriteComponent()
{
}

/******************************************************************************/
void SkeletonSpriteComponent::Load()
{
  LoadShaders();
  LoadTextures();
  LoadAnimations();
}

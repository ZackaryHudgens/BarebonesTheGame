#include "CharacterSpriteComponent.hpp"

using Barebones::CharacterSpriteComponent;

/******************************************************************************/
CharacterSpriteComponent::CharacterSpriteComponent()
  : SpriteComponent()
{
}

/******************************************************************************/
void CharacterSpriteComponent::Load()
{
  LoadTextures();
  LoadShaders();
  LoadAnimations();
}

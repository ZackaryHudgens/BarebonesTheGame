#include "CharacterSpriteComponent.hpp"

using Barebones::CharacterSpriteComponent;

/******************************************************************************/
CharacterSpriteComponent::CharacterSpriteComponent()
  : SpriteComponent()
{
}

/******************************************************************************/
void CharacterSpriteComponent::Initialize()
{
  SetupTextures();
  SetupShaders();
  SetupAnimations();
}

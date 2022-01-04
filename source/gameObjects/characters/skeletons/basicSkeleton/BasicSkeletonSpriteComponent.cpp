#include "BasicSkeletonSpriteComponent.hpp"

using Barebones::BasicSkeletonSpriteComponent;

/******************************************************************************/
BasicSkeletonSpriteComponent::BasicSkeletonSpriteComponent()
  : CharacterSpriteComponent()
{
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::LoadShaders()
{
  std::string vertexFile = "resources/shaders/SpriteShader.vert";
  std::string fragmentFile = "resources/shaders/SpriteShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
  AddShader("defaultShader", defaultShader);
  SetCurrentShader("defaultShader");
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::LoadTextures()
{
  UrsineEngine::Texture spritesheet;
  spritesheet.CreateTextureFromFile("resources/sprites/skeletons/TempSprite.png");
  SetTexture(spritesheet);
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::LoadAnimations()
{
}

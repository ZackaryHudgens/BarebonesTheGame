#include "BasicHumanSpriteComponent.hpp"

using Barebones::BasicHumanSpriteComponent;

/******************************************************************************/
BasicHumanSpriteComponent::BasicHumanSpriteComponent()
{
}

/******************************************************************************/
void BasicHumanSpriteComponent::SetupShaders()
{
  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
  AddShader("defaultShader", defaultShader);
  SetCurrentShader("defaultShader");
}

/******************************************************************************/
void BasicHumanSpriteComponent::SetupTextures()
{
  UrsineEngine::Texture spritesheet;
  spritesheet.CreateTextureFromFile("resources/sprites/enemies/basicHuman.png");
  SetTexture(spritesheet);
}

/******************************************************************************/
void BasicHumanSpriteComponent::SetupAnimations()
{
}

#include "BasicHumanSpriteComponent.hpp"

using Barebones::BasicHumanSpriteComponent;

/******************************************************************************/
BasicHumanSpriteComponent::BasicHumanSpriteComponent()
{
}

/******************************************************************************/
void BasicHumanSpriteComponent::SetupShaders()
{
  std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);

  defaultShader.Activate();
  defaultShader.SetFloat("fadeValue", 0.0);
  defaultShader.SetVec4("fadeColor", glm::vec4(0.125, 0.125, 0.125, 1.0));

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

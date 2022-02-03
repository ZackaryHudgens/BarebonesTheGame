#include "BasicHumanSpriteComponent.hpp"

using Barebones::BasicHumanSpriteComponent;

/******************************************************************************/
BasicHumanSpriteComponent::BasicHumanSpriteComponent()
{
}

/******************************************************************************/
void BasicHumanSpriteComponent::SetupShaders()
{
  std::string vertexFile = "resources/shaders/CharacterShader.vert";
  std::string fragmentFile = "resources/shaders/CharacterShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);

  defaultShader.Activate();
  defaultShader.SetVec4("selectionColor", glm::vec4(1.0,
                                                    1.0,
                                                    1.0,
                                                    1.0));
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

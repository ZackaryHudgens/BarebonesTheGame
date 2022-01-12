#include "BasicSkeletonSpriteComponent.hpp"

using Barebones::BasicSkeletonSpriteComponent;

/******************************************************************************/
BasicSkeletonSpriteComponent::BasicSkeletonSpriteComponent()
  : CharacterSpriteComponent()
{
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::SetupShaders()
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
void BasicSkeletonSpriteComponent::SetupTextures()
{
  UrsineEngine::Texture spritesheet;
  spritesheet.CreateTextureFromFile("resources/sprites/skeletons/TempSprite.png");
  SetTexture(spritesheet);
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::SetupAnimations()
{
}

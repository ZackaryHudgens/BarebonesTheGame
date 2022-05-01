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
void BasicSkeletonSpriteComponent::SetupTextures()
{
  UrsineEngine::Texture spritesheet;
  spritesheet.CreateTextureFromFile("resources/sprites/skeletons/basicSkeletonSpritesheet.png");
  SetTexture(spritesheet);
}

/******************************************************************************/
void BasicSkeletonSpriteComponent::SetupAnimations()
{
  CreateAnimation("walking");

  UrsineEngine::TextureClip clip;
  clip.mHeight = 16;
  clip.mWidth = 16;
  clip.mX = 0;
  clip.mY = 0;
  AddFrameToAnimation("walking", clip);

  clip.mX = 16;
  AddFrameToAnimation("walking", clip);

  SetAnimation("walking");
  SetSpeedOfAnimation(3.0);
}

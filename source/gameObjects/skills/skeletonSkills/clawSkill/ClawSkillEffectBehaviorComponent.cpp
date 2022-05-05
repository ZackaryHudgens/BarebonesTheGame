#include "ClawSkillEffectBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <Shader.hpp>

#include <iostream>

using Barebones::ClawSkillEffectBehaviorComponent;

/******************************************************************************/
ClawSkillEffectBehaviorComponent::ClawSkillEffectBehaviorComponent()
  : Component()
  , mSprite(nullptr)
{
  UrsineEngine::SpriteAnimationComplete.Connect(*this, [this](const std::string& aName,
                                                              UrsineEngine::SpriteComponent& aSprite)
  {
    this->HandleSpriteAnimationComplete(aName,
                                        aSprite);
  });
}

/******************************************************************************/
void ClawSkillEffectBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a sprite and add it to the parent.
    auto sprite = std::make_unique<UrsineEngine::SpriteComponent>();

    UrsineEngine::Texture texture;
    texture.CreateTextureFromFile("resources/sprites/clawEffectSpritesheet.png");
    sprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile,
                                       fragmentFile);
    sprite->AddShader("defaultShader", defaultShader);
    sprite->SetCurrentShader("defaultShader");

    // Create the animations for the sprite.
    sprite->CreateAnimation("default");

    UrsineEngine::TextureClip clip;
    clip.mHeight = 16;
    clip.mWidth = 16;
    clip.mX = 0;
    clip.mY = 0;
    sprite->AddFrameToAnimation("default", clip);

    clip.mX = 16;
    sprite->AddFrameToAnimation("default", clip);

    clip.mX = 32;
    sprite->AddFrameToAnimation("default", clip);

    sprite->SetAnimation("default");
    sprite->SetSpeedOfAnimation(15.0);

    parent->AddComponent(std::move(sprite));
    mSprite = parent->GetComponentsOfType<UrsineEngine::SpriteComponent>().back();
  }
}

/******************************************************************************/
void ClawSkillEffectBehaviorComponent::HandleSpriteAnimationComplete(const std::string& aName,
                                                                     UrsineEngine::SpriteComponent& aSprite)
{
  if(mSprite == &aSprite)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      parent->ScheduleForDeletion();
    }
  }
}

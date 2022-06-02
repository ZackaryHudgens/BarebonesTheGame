#include "AnimationVisualEffectBehaviorComponent.hpp"

#include <CoreSignals.hpp>
#include <GameObject.hpp>

using Barebones::AnimationVisualEffectBehaviorComponent;

/******************************************************************************/
AnimationVisualEffectBehaviorComponent::AnimationVisualEffectBehaviorComponent(const std::string& aSpritesheet,
                                                                               const std::vector<UrsineEngine::TextureClip> aClips,
                                                                               double aSpeed)
  : Component()
  , mSprite(nullptr)
  , mSpritesheet(aSpritesheet)
  , mClips(aClips)
  , mSpeed(aSpeed)
{
  UrsineEngine::SpriteAnimationComplete.Connect(*this, [this](const std::string& aName,
                                                              UrsineEngine::SpriteComponent& aSprite)
  {
    this->HandleSpriteAnimationComplete(aName, aSprite);
  });
}

/******************************************************************************/
void AnimationVisualEffectBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a sprite and add it to the parent.
    auto sprite = std::make_unique<UrsineEngine::SpriteComponent>();
    sprite->SetRenderOption(GL_DEPTH_TEST, false);

    UrsineEngine::Texture texture;
    texture.CreateTextureFromFile(mSpritesheet);
    sprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile,
                                       fragmentFile);
    sprite->AddShader("defaultShader", defaultShader);
    sprite->SetCurrentShader("defaultShader");

    // Create the animations for the sprite.
    sprite->AddAnimation("default");
    for(const auto& clip : mClips)
    {
      sprite->AddFrameToAnimation("default", clip);
    }

    sprite->SetAnimation("default");
    sprite->SetSpeedOfAnimation(mSpeed);

    parent->AddComponent(std::move(sprite));
    mSprite = parent->GetComponentsOfType<UrsineEngine::SpriteComponent>().back();
  }
}

/******************************************************************************/
void AnimationVisualEffectBehaviorComponent::HandleSpriteAnimationComplete(const std::string& aName,
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

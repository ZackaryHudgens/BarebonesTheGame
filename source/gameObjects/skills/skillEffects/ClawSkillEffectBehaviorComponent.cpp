#include "ClawSkillEffectBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <Shader.hpp>
#include <SpriteComponent.hpp>

using Barebones::ClawSkillEffectBehaviorComponent;

/******************************************************************************/
ClawSkillEffectBehaviorComponent::ClawSkillEffectBehaviorComponent()
  : Component()
  , mDisplayTime(0.3)
  , mTimeInitialized(0.0)
{
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
    texture.CreateTextureFromFile("resources/sprites/claw.png");
    sprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/CharacterShader.vert";
    std::string fragmentFile = "resources/shaders/CharacterShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile,
                                       fragmentFile);

    defaultShader.Activate();
    defaultShader.SetVec4("selectionColor", glm::vec4(1.0,
                                                      1.0,
                                                      1.0,
                                                      1.0));
    sprite->AddShader("defaultShader", defaultShader);
    sprite->SetCurrentShader("defaultShader");

    parent->AddComponent(std::move(sprite));
  }

  mTimeInitialized = env.GetTime();
}

/******************************************************************************/
void ClawSkillEffectBehaviorComponent::Update(double aTime)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto timeDisplayed = aTime - mTimeInitialized;
    if(timeDisplayed >= mDisplayTime)
    {
      parent->ScheduleForDeletion();
    }
  }
}

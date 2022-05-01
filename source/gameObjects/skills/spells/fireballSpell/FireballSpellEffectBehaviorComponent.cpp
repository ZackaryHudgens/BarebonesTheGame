#include "FireballSpellEffectBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::FireballSpellEffectBehaviorComponent;

/******************************************************************************/
FireballSpellEffectBehaviorComponent::FireballSpellEffectBehaviorComponent()
  : Component()
  , mSprite(nullptr)
  , mScaleSpeed(0.05)
{
}

/******************************************************************************/
void FireballSpellEffectBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto fireballSprite = std::make_unique<UrsineEngine::SpriteComponent>();

    UrsineEngine::Texture fireballTexture;
    fireballTexture.CreateTextureFromFile("resources/sprites/fireballSpellSprite.png");
    fireballSprite->SetTexture(fireballTexture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile,
                                       fragmentFile);
    fireballSprite->AddShader("defaultShader", defaultShader);
    fireballSprite->SetCurrentShader("defaultShader");

    parent->AddComponent(std::move(fireballSprite));
  }
}

/******************************************************************************/
void FireballSpellEffectBehaviorComponent::Update(double aTime)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto scalarTransform = parent->GetScalarTransform();
    auto currentScalar = scalarTransform[0][0];

    auto newScalar = glm::mix(currentScalar, 0.0f, mScaleSpeed);
    if(newScalar <= 0.005)
    {
      parent->ScheduleForDeletion();
    }
    else
    {
      parent->SetScale(glm::vec3(newScalar, newScalar, 1.0));
    }
  }
}

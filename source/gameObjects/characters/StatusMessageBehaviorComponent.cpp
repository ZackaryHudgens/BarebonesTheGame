#include "StatusMessageBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::StatusMessageBehaviorComponent;

/******************************************************************************/
StatusMessageBehaviorComponent::StatusMessageBehaviorComponent()
  : Component()
  , mTextComponent(nullptr)
{
}

/******************************************************************************/
void StatusMessageBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create the text.
    auto textObject = std::make_unique<UrsineEngine::GameObject>("textObject");
    textObject->AddComponent(std::make_unique<UrsineEngine::TextComponent>());
    mTextComponent = textObject->GetComponentsOfType<UrsineEngine::TextComponent>().back();

    mTextComponent->SetFont("Alagard", "Medium");
    mTextComponent->SetSize(42);
    mTextComponent->SetColor(glm::vec4(0.89, 0.93, 0.75, 1.0));
    mTextComponent->SetText("Desecrated!");

    mTextComponent->SetRenderOption(GL_DEPTH_TEST, false);

    parent->AddChild(std::move(textObject));
  }
}

/******************************************************************************/
void StatusMessageBehaviorComponent::Update(double aTime)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto pos = parent->GetPosition();
    //pos.y += 0.01;
    parent->SetPosition(pos);

    if(pos.y >= 2.5)
    {
      parent->ScheduleForDeletion();
    }
  }
}

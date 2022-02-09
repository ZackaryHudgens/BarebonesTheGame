#include "BoardBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "BoardInputComponent.hpp"
#include "MenuBehaviorComponent.hpp"

using Barebones::BoardBehaviorComponent;

/******************************************************************************/
BoardBehaviorComponent::BoardBehaviorComponent()
{
  MenuCreated.Connect(*this, [this](UrsineEngine::GameObject& aObject)
  {
    this->HandleMenuCreated(aObject);
  });

  MenuDestroyed.Connect(*this, [this](UrsineEngine::GameObject& aObject)
  {
    this->HandleMenuDestroyed(aObject);
  });
}

/******************************************************************************/
void BoardBehaviorComponent::HandleMenuCreated(UrsineEngine::GameObject& aObject)
{
  // When a menu is created, disable the board's input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(inputComponent != nullptr)
    {
      inputComponent->SetEnabled(false);
    }
  }
}

/******************************************************************************/
void BoardBehaviorComponent::HandleMenuDestroyed(UrsineEngine::GameObject& aObject)
{
  // When a menu is destroyed, re-enable the board's input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(inputComponent != nullptr)
    {
      inputComponent->SetEnabled(true);
    }
  }
}

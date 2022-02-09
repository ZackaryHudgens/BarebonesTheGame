#include "MenuBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::MenuBehaviorComponent;

/******************************************************************************/
MenuBehaviorComponent::MenuBehaviorComponent()
  : Component()
{
  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
}

/******************************************************************************/
void MenuBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    MenuCreated.Notify(*parent);
  }
}

/******************************************************************************/
void MenuBehaviorComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject)
{
  auto parent = GetParent();
  if(parent != nullptr &&
     aObject == parent)
  {
    MenuDestroyed.Notify(*parent);
  }
}

/******************************************************************************/
Barebones::MenuCreatedSignal   Barebones::MenuCreated;
Barebones::MenuDestroyedSignal Barebones::MenuDestroyed;

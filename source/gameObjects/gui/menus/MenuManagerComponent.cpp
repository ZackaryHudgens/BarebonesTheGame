#include "MenuManagerComponent.hpp"

#include <CoreSignals.hpp>

#include "Signals.hpp"

using Barebones::MenuManagerComponent;

/******************************************************************************/
MenuManagerComponent::MenuManagerComponent()
  : Component()
{
  MenuLayoutComponentInitialized.Connect(*this, [this](MenuLayoutComponent& aComponent)
  {
    this->HandleMenuLayoutComponentInitialized(aComponent);
  });

  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(*aObject);
  });
}

/******************************************************************************/
void MenuManagerComponent::HandleMenuLayoutComponentInitialized(MenuLayoutComponent& aComponent)
{
  if(!mMenuStack.empty())
  {
    mMenuStack.top()->SetHidden(true);
  }

  mMenuStack.push(&aComponent);
}

/******************************************************************************/
void MenuManagerComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject& aObject)
{
  if(!mMenuStack.empty())
  {
    if(mMenuStack.top()->GetParent() == &aObject)
    {
      mMenuStack.pop();

      if(!mMenuStack.empty())
      {
        mMenuStack.top()->SetHidden(false);
      }
    }
  }
}

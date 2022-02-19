#include "InputManagerComponent.hpp"

#include <GameObject.hpp>

using Barebones::InputManagerComponent;

/******************************************************************************/
InputManagerComponent::InputManagerComponent()
  : Component()
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
  });

  UrsineEngine::KeyRepeated.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
  {
    this->HandleKeyRepeated(aCode,
                            aMods);
  });

  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(*aObject);
  });

  InputComponentInitialized.Connect(*this, [this](InputComponent& aComponent)
  {
    mInputStack.push(&aComponent);
  });
}

/******************************************************************************/
void InputManagerComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                             int aMods)
{
  if(!mInputStack.empty() &&
     mInputStack.top() != nullptr)
  {
    mInputStack.top()->HandleKeyPressed(aCode,
                                        aMods);
  }
}

/******************************************************************************/
void InputManagerComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                              int aMods)
{
  if(!mInputStack.empty() &&
     mInputStack.top() != nullptr)
  {
    mInputStack.top()->HandleKeyRepeated(aCode,
                                         aMods);
  }
}

/******************************************************************************/
void InputManagerComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject& aObject)
{
  if(!mInputStack.empty() &&
     mInputStack.top() != nullptr)
  {
    if(mInputStack.top()->GetParent() == &aObject)
    {
      mInputStack.pop();
    }
  }
}

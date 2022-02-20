#include "InputComponent.hpp"

using Barebones::InputComponent;

/******************************************************************************/
InputComponent::InputComponent()
  : Component()
{
}

/******************************************************************************/
void InputComponent::Initialize()
{
  ProtectedInitialize();
  InputComponentInitialized.Notify(*this);
}

/******************************************************************************/
Barebones::InputComponentInitializedSignal Barebones::InputComponentInitialized;

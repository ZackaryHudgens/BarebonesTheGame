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
  InputComponentInitialized.Notify(*this);
}

/******************************************************************************/
Barebones::InputComponentInitializedSignal Barebones::InputComponentInitialized;

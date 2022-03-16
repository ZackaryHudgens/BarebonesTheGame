#include "InputComponent.hpp"

#include "Signals.hpp"

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

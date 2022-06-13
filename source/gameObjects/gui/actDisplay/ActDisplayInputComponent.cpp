#include "ActDisplayInputComponent.hpp"

#include "Signals.hpp"

using Barebones::ActDisplayInputComponent;

/******************************************************************************/
ActDisplayInputComponent::ActDisplayInputComponent()
  : InputComponent()
  , mEnabled(false)
{
  ActDisplayReadyForInput.Connect(*this, [this](UrsineEngine::GameObject& aDisplay)
  {
    this->HandleActDisplayReadyForInput(aDisplay);
  });
}

/******************************************************************************/
void ActDisplayInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                int aMods)
{
  if(mEnabled)
  {
    switch(aCode)
    {
      case UrsineEngine::KeyCode::eKEY_ENTER:
      {
        auto parent = GetParent();
        if(parent != nullptr)
        {
          ActDisplayAdvanced.Notify(*parent);
          mEnabled = false;
        }
        break;
      }
      default:
      {
        break;
      }
    }
  }
}

/******************************************************************************/
void ActDisplayInputComponent::HandleActDisplayReadyForInput(UrsineEngine::GameObject& aDisplay)
{
  if(&aDisplay == GetParent())
  {
    mEnabled = true;
  }
}

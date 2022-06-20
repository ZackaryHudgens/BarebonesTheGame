#include "MenuAudioComponent.hpp"

#include "Signals.hpp"

using Barebones::MenuAudioComponent;

/******************************************************************************/
MenuAudioComponent::MenuAudioComponent()
  : AudioComponent()
{
  MenuActionHovered.Connect(*this, [this](UrsineEngine::GameObject& aObject,
                                          const MenuAction& aAction)
  {
    this->HandleActionHovered(aObject, aAction);
  });

  MenuActionExecuted.Connect(*this, [this](UrsineEngine::GameObject& aObject,
                                           const MenuAction& aAction)
  {
    this->HandleActionExecuted(aObject, aAction);
  });
}

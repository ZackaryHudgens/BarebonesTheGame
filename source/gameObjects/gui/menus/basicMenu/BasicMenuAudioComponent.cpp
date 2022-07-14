#include "BasicMenuAudioComponent.hpp"

using Barebones::BasicMenuAudioComponent;

/******************************************************************************/
BasicMenuAudioComponent::BasicMenuAudioComponent()
  : MenuAudioComponent()
{
}

/******************************************************************************/
void BasicMenuAudioComponent::HandleActionHovered(UrsineEngine::GameObject& aObject,
                                                 const MenuAction& aAction)
{
  if(&aObject == GetParent())
  {
    PlaySound("resources/audio/arrowMoved.wav");
  }
}

/******************************************************************************/
void BasicMenuAudioComponent::HandleActionExecuted(UrsineEngine::GameObject& aObject,
                                                  const MenuAction& aAction)
{
  if(&aObject == GetParent())
  {
  }
}

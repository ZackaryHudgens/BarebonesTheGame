#include "MainMenuAudioComponent.hpp"

using Barebones::MainMenuAudioComponent;

/******************************************************************************/
MainMenuAudioComponent::MainMenuAudioComponent()
  : MenuAudioComponent()
{
}

/******************************************************************************/
void MainMenuAudioComponent::HandleActionHovered(UrsineEngine::GameObject& aObject,
                                                 const MenuAction& aAction)
{
  if(&aObject == GetParent())
  {
    PlaySound("resources/audio/arrowMoved.wav");
  }
}

/******************************************************************************/
void MainMenuAudioComponent::HandleActionExecuted(UrsineEngine::GameObject& aObject,
                                                  const MenuAction& aAction)
{
  if(&aObject == GetParent())
  {
  }
}

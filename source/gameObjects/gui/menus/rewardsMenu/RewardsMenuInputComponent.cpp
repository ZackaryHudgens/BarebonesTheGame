#include "RewardsMenuInputComponent.hpp"

#include <GameObject.hpp>

#include "MenuLayoutComponent.hpp"

using Barebones::RewardsMenuInputComponent;

/******************************************************************************/
RewardsMenuInputComponent::RewardsMenuInputComponent()
  : InputComponent()
{
}

/******************************************************************************/
void RewardsMenuInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                               int aMods)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<MenuLayoutComponent>();
    if(layout != nullptr)
    {
      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_LEFT:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        {
          layout->HoverOverNextAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          layout->ExecuteCurrentAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ESCAPE:
        {
          parent->ScheduleForDeletion();
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
}

/******************************************************************************/
void RewardsMenuInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                int aMods)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<MenuLayoutComponent>();
    if(layout != nullptr)
    {
      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_LEFT:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        {
          layout->HoverOverNextAction();
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
}

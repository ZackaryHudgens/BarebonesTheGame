#include "BasicMenuInputComponent.hpp"

#include <GameObject.hpp>

#include "MenuLayoutComponent.hpp"

using Barebones::BasicMenuInputComponent;

/******************************************************************************/
BasicMenuInputComponent::BasicMenuInputComponent()
  : InputComponent()
{
}

/******************************************************************************/
void BasicMenuInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
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
        case UrsineEngine::KeyCode::eKEY_UP:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
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
void BasicMenuInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
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
        case UrsineEngine::KeyCode::eKEY_UP:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
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

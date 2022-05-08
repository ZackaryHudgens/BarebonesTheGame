#include "SpellMenuInputComponent.hpp"

#include "MenuLayoutComponent.hpp"

using Barebones::SpellMenuInputComponent;

/******************************************************************************/
SpellMenuInputComponent::SpellMenuInputComponent()
  : InputComponent()
{
}

/******************************************************************************/
void SpellMenuInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
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
        case UrsineEngine::KeyCode::eKEY_A:
        case UrsineEngine::KeyCode::eKEY_LEFT:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_D:
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        {
          layout->HoverOverNextAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          layout->SelectCurrentAction();
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
void SpellMenuInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
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
        case UrsineEngine::KeyCode::eKEY_A:
        case UrsineEngine::KeyCode::eKEY_LEFT:
        {
          layout->HoverOverPreviousAction();
          break;
        }
        case UrsineEngine::KeyCode::eKEY_D:
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

#include "MenuInputComponent.hpp"

#include "MenuLayoutComponent.hpp"

using Barebones::MenuInputComponent;

/******************************************************************************/
MenuInputComponent::MenuInputComponent()
  : Component()
  , mEnabled(true)
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
  });

  UrsineEngine::KeyRepeated.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
  {
    this->HandleKeyRepeated(aCode,
                            aMods);
  });
}

/******************************************************************************/
void MenuInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                          int aMods)
{
  if(mEnabled)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto layout = parent->GetFirstComponentOfType<MenuLayoutComponent>();
      if(layout != nullptr)
      {
        switch(aCode)
        {
          case UrsineEngine::KeyCode::eKEY_W:
          case UrsineEngine::KeyCode::eKEY_UP:
          {
            layout->HoverOverPreviousAction();
            break;
          }
          case UrsineEngine::KeyCode::eKEY_S:
          case UrsineEngine::KeyCode::eKEY_DOWN:
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
}

/******************************************************************************/
void MenuInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                           int aMods)
{
  if(mEnabled)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto layout = parent->GetFirstComponentOfType<MenuLayoutComponent>();
      if(layout != nullptr)
      {
        switch(aCode)
        {
          case UrsineEngine::KeyCode::eKEY_W:
          case UrsineEngine::KeyCode::eKEY_UP:
          {
            layout->HoverOverPreviousAction();
            break;
          }
          case UrsineEngine::KeyCode::eKEY_S:
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
}

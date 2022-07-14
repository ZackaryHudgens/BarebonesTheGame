#include "MenuLayoutComponent.hpp"

#include <algorithm>

#include "Signals.hpp"

using Barebones::MenuLayoutComponent;

/******************************************************************************/
MenuLayoutComponent::MenuLayoutComponent()
  : mCurrentlyHoveredAction(nullptr)
  , mWraparound(true)
{
  MenuActionEnabledChanged.Connect(*this, [this](MenuAction& aAction)
  {
    this->HandleMenuActionEnabledChanged(aAction);
  });
}

/******************************************************************************/
void MenuLayoutComponent::AddAction(std::unique_ptr<MenuAction> aAction)
{
  if(aAction != nullptr)
  {
    mActions.emplace_back(std::move(aAction));
    HandleActionAdded(*mActions.back());

    // If no action is currently hovered over, hover over this one.
    if(mCurrentlyHoveredAction == nullptr)
    {
      mCurrentlyHoveredAction = mActions.back().get();
      HandleActionHovered(*mCurrentlyHoveredAction);
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverNextAction()
{
  auto currentAction = std::find(mActions.begin(),
                                 mActions.end(),
                                 mCurrentlyHoveredAction);
  if(currentAction != mActions.end())
  {
    // If the current action is the last action, then loop around and hover
    // over the first action. Otherwise, hover over the next action.
    auto nextAction = std::next(currentAction);
    if(nextAction == mActions.end())
    {
      if(mWraparound)
      {
        mCurrentlyHoveredAction = mActions.front().get();
      }
    }
    else
    {
      mCurrentlyHoveredAction = (*nextAction).get();
    }

    HandleActionHovered(*mCurrentlyHoveredAction);

    auto parent = GetParent();
    if(parent != nullptr)
    {
      MenuActionHovered.Notify(*parent, *mCurrentlyHoveredAction);
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverPreviousAction()
{
  auto currentAction = std::find(mActions.begin(),
                                 mActions.end(),
                                 mCurrentlyHoveredAction);
  if(currentAction != mActions.end())
  {
    // If the current action is the first action, then loop around and hover
    // over the last action. Otherwise, hover over the previous action.
    if(currentAction == mActions.begin())
    {
      if(mWraparound)
      {
        mCurrentlyHoveredAction = mActions.back().get();
      }
    }
    else
    {
      mCurrentlyHoveredAction = (*std::prev(currentAction)).get();
    }

    HandleActionHovered(*mCurrentlyHoveredAction);

    auto parent = GetParent();
    if(parent != nullptr)
    {
      MenuActionHovered.Notify(*parent, *mCurrentlyHoveredAction);
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::ExecuteCurrentAction()
{
  if(mCurrentlyHoveredAction != nullptr)
  {
    if(mCurrentlyHoveredAction->IsEnabled())
    {
      mCurrentlyHoveredAction->Execute();
      HandleActionExecuted(*mCurrentlyHoveredAction);

      auto parent = GetParent();
      if(parent != nullptr)
      {
        MenuActionExecuted.Notify(*parent, *mCurrentlyHoveredAction);
      }
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::HandleMenuActionEnabledChanged(MenuAction& aAction)
{
  auto findAction = [aAction](const std::unique_ptr<MenuAction>& aActionToCompare)
  {
    return aActionToCompare->GetName() == aAction.GetName();
  };

  auto foundAction = std::find_if(mActions.begin(),
                                  mActions.end(),
                                  findAction);
  if(foundAction != mActions.end())
  {
    HandleActionEnabledChanged(*(*foundAction).get());
  }
}

#include "MenuLayoutComponent.hpp"

#include <algorithm>

#include "Signals.hpp"

using Barebones::MenuLayoutComponent;

/******************************************************************************/
MenuLayoutComponent::MenuLayoutComponent()
  : mCurrentlyHoveredAction(nullptr)
{
}

/******************************************************************************/
void MenuLayoutComponent::Initialize()
{
  ProtectedInitialize();
  MenuLayoutComponentInitialized.Notify(*this);
}

/******************************************************************************/
void MenuLayoutComponent::AddAction(std::unique_ptr<MenuAction> aAction)
{
  mActions.emplace_back(std::move(aAction));
  HandleActionAdded();

  // If no action is currently hovered over, hover over this one.
  if(mCurrentlyHoveredAction == nullptr)
  {
    mCurrentlyHoveredAction = mActions.back().get();
    HandleActionHovered();
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverNextAction()
{
  auto actions = GetActions();
  auto currentAction = std::find(actions.begin(),
                                 actions.end(),
                                 mCurrentlyHoveredAction);
  if(currentAction != actions.end())
  {
    // If the current action is the last action, then loop around and hover
    // over the first action. Otherwise, hover over the next action.
    auto nextAction = std::next(currentAction);
    if(nextAction == actions.end())
    {
      mCurrentlyHoveredAction = actions.front();
    }
    else
    {
      mCurrentlyHoveredAction = (*nextAction);
    }

    HandleActionHovered();
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverPreviousAction()
{
  auto actions = GetActions();
  auto currentAction = std::find(actions.begin(),
                                 actions.end(),
                                 mCurrentlyHoveredAction);
  if(currentAction != actions.end())
  {
    // If the current action is the first action, then loop around and hover
    // over the last action. Otherwise, hover over the previous action.
    if(currentAction == actions.begin())
    {
      mCurrentlyHoveredAction = actions.back();
    }
    else
    {
      mCurrentlyHoveredAction = (*std::prev(currentAction));
    }

    HandleActionHovered();
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
      HandleActionExecuted();
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::SetHidden(bool aHidden)
{
  mHidden = aHidden;
  HandleHiddenStatusChanged(mHidden);
}

/******************************************************************************/
std::vector<Barebones::MenuAction*> MenuLayoutComponent::GetActions()
{
  std::vector<MenuAction*> actions;

  for(auto& action : mActions)
  {
    actions.emplace_back(action.get());
  }

  return actions;
}

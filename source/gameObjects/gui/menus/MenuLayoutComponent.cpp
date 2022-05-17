#include "MenuLayoutComponent.hpp"

#include <algorithm>

#include "ActionBehaviorComponent.hpp"

using Barebones::MenuLayoutComponent;

/******************************************************************************/
MenuLayoutComponent::MenuLayoutComponent()
  : mCurrentlyHoveredAction(nullptr)
{
}

/******************************************************************************/
void MenuLayoutComponent::AddAction(std::unique_ptr<UrsineEngine::GameObject> aObject)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(aObject));
    mActions.emplace_back(parent->GetChildren().back());

    HandleActionAdded();

    // If no action is currently hovered over, hover over this one.
    if(mCurrentlyHoveredAction == nullptr)
    {
      mCurrentlyHoveredAction = parent->GetChildren().back();
      auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
      if(behaviorComp != nullptr)
      {
        behaviorComp->SetHovered(true);
      }

      HandleActionHovered();
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverNextAction()
{
  // Un-hover the currently selected action.
  if(mCurrentlyHoveredAction != nullptr)
  {
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      behaviorComp->SetHovered(false);
    }
  }

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
      mCurrentlyHoveredAction = mActions.front();
    }
    else
    {
      mCurrentlyHoveredAction = (*nextAction);
    }

    // Set the hovered property of the action.
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      behaviorComp->SetHovered(true);
    }

    HandleActionHovered();
  }
}

/******************************************************************************/
void MenuLayoutComponent::HoverOverPreviousAction()
{
  // Un-hover the currently selected action.
  if(mCurrentlyHoveredAction != nullptr)
  {
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      behaviorComp->SetHovered(false);
    }
  }

  auto currentAction = std::find(mActions.begin(),
                                 mActions.end(),
                                 mCurrentlyHoveredAction);
  if(currentAction != mActions.end())
  {
    if(currentAction == mActions.begin())
    {
      mCurrentlyHoveredAction = (*std::prev(mActions.end()));
    }
    else
    {
      mCurrentlyHoveredAction = (*std::prev(currentAction));
    }

    // Set the hovered property of the action.
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      behaviorComp->SetHovered(true);
    }

    HandleActionHovered();
  }
}

/******************************************************************************/
void MenuLayoutComponent::ExecuteCurrentAction()
{
  if(mCurrentlyHoveredAction != nullptr)
  {
    auto actionBehaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(actionBehaviorComp != nullptr)
    {
      if(actionBehaviorComp->IsEnabled())
      {
        actionBehaviorComp->Execute();

        HandleActionExecuted();
      }
    }
  }
}

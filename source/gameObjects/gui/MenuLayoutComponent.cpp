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

    // If no action is currently hovered over, hover over this one.
    if(mCurrentlyHoveredAction == nullptr)
    {
      mCurrentlyHoveredAction = parent->GetChildren().back();
      auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
      if(behaviorComp != nullptr)
      {
        behaviorComp->SetHovered(true);
      }
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
    // If the current action is the first action, then loop around and hover
    // over the last action. Otherwise, hover over the next action.
    auto prevAction = std::prev(currentAction);
    if(prevAction == mActions.begin())
    {
      mCurrentlyHoveredAction = mActions.back();
    }
    else
    {
      mCurrentlyHoveredAction = (*prevAction);
    }

    // Set the hovered property of the action.
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      behaviorComp->SetHovered(true);
    }
  }
}

/******************************************************************************/
void MenuLayoutComponent::SelectCurrentAction()
{
  if(mCurrentlyHoveredAction != nullptr)
  {
    auto behaviorComp = mCurrentlyHoveredAction->GetFirstComponentOfType<ActionBehaviorComponent>();
    behaviorComp->SetSelected(true);
  }
}

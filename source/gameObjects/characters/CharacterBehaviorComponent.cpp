#include "CharacterBehaviorComponent.hpp"

#include <iostream>

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mTargetPosition(0.0, 0.0, 0.0)
  , mSpeed(0.0)
  , mMoving(false)
  , mSelected(false)
{
}

/******************************************************************************/
void CharacterBehaviorComponent::Update()
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto position = glm::mix(parent->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
         std::abs(mTargetPosition.y - position.y) <= 0.005 &&
         std::abs(mTargetPosition.z - position.z) <= 0.005)
      {
        parent->SetPosition(mTargetPosition);
        mMoving = false;
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }

  ProtectedUpdate();
}

/******************************************************************************/
void CharacterBehaviorComponent::MoveCharacter(const glm::vec3& aPosition,
                                               double aSpeed)
{
  mTargetPosition = aPosition;
  mSpeed = aSpeed;
  mMoving = true;
}

/******************************************************************************/
void CharacterBehaviorComponent::SetSelected(bool aSelected)
{
  mSelected = aSelected;
  HandleSelectionChanged(aSelected);
  CharacterSelected.Notify(*this);
}

/******************************************************************************/
Barebones::MoveList CharacterBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                             const TileLocation& aLocation) const
{
  return MoveList();
}

/******************************************************************************/
Barebones::CharacterSelectedSignal Barebones::CharacterSelected;

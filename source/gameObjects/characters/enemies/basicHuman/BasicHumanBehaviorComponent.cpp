#include "BasicHumanBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

#include "PitchforkSkill.hpp"

using Barebones::BasicHumanBehaviorComponent;

/******************************************************************************/
BasicHumanBehaviorComponent::BasicHumanBehaviorComponent()
  : EnemyBehaviorComponent()
  , mWaitingForMove(false)
  , mHorizontalMovement(1)
  , mVerticalMovement(1)
{
  CharacterFinishedMoving.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMoving(aCharacter);
  });

  SetName("Humie");
  SetType(Type::eHUMAN);
  SetMaximumHealth(5);
  SetCurrentHealth(5);
}

/******************************************************************************/
void BasicHumanBehaviorComponent::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  CharacterTurnBegan.Notify(*this);

  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      // For now, just move the character to the left one space if possible.
      auto targetLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
      targetLocation.first -= 1;

      auto moveSkill = GetSkill("Move");
      if(moveSkill != nullptr)
      {
        if(moveSkill->IsTileValid(aBoard, targetLocation))
        {
          moveSkill->Execute(aBoard, targetLocation);
          mWaitingForMove = true;
          success = true;
        }
        else
        {
          // Check if we can use our pitchfork.
          auto pitchforkSkill = GetSkill("Pitchfork");
          if(pitchforkSkill != nullptr)
          {
            if(pitchforkSkill->IsTileValid(aBoard, targetLocation))
            {
              pitchforkSkill->Execute(aBoard, targetLocation);
            }
          }
        }
      }
    }
  }

  if(!success)
  {
    EndTurn();
  }
}

/******************************************************************************/
Barebones::TileList BasicHumanBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                              const TileLocation& aLocation) const
{
  TileList moves;

  auto layout = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(layout != nullptr)
  {
    TileLocation moveLocation = aLocation;

    // Determine movements to the left.
    for(int left = 0; left < mHorizontalMovement; ++left)
    {
      moveLocation.first = aLocation.first - left - 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move left.
        break;
      }
    }
    moveLocation.first = aLocation.first;

    // Determine movements to the right.
    for(int right = 0; right < mHorizontalMovement; ++right)
    {
      moveLocation.first = aLocation.first + right + 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move right.
        break;
      }
    }
    moveLocation.first = aLocation.first;

    // Determine upward movements.
    for(int up = 0; up < mVerticalMovement; ++up)
    {
      moveLocation.second = aLocation.second + up + 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move up.
        break;
      }
    }
    moveLocation.second = aLocation.second;

    // Determine downward movements.
    for(int down = 0; down < mVerticalMovement; ++down)
    {
      moveLocation.second = aLocation.second - down - 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move down.
        break;
      }
    }
  }

  return moves;
}

/******************************************************************************/
void BasicHumanBehaviorComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    AddSkill(std::make_unique<PitchforkSkill>(*parent));
  }
}

/******************************************************************************/
void BasicHumanBehaviorComponent::HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter)
{
  if(&aCharacter == this &&
     mWaitingForMove)
  {
    mWaitingForMove = false;
    EndTurn();
  }
}

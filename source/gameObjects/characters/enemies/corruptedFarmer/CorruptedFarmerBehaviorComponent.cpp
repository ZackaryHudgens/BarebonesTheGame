#include "CorruptedFarmerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

#include "PitchforkSkill.hpp"

using Barebones::CorruptedFarmerBehaviorComponent;

/******************************************************************************/
CorruptedFarmerBehaviorComponent::CorruptedFarmerBehaviorComponent()
  : EnemyBehaviorComponent()
  , mWaitingForMove(false)
  , mHorizontalMovement(1)
  , mVerticalMovement(1)
{
  CharacterFinishedMoving.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMoving(aCharacter);
  });

  SetName("Corrupted Farmer");
  SetType(Type::eHUMAN);
  SetMaximumHealth(5);
  SetCurrentHealth(5);
}

/******************************************************************************/
void CorruptedFarmerBehaviorComponent::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  CharacterTurnBegan.Notify(*this);

  GenerateGraph(aBoard);

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
void CorruptedFarmerBehaviorComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    AddSkill(std::make_unique<PitchforkSkill>(*parent));
  }
}

/******************************************************************************/
void CorruptedFarmerBehaviorComponent::HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter)
{
  if(&aCharacter == this &&
     mWaitingForMove)
  {
    mWaitingForMove = false;
    EndTurn();
  }
}

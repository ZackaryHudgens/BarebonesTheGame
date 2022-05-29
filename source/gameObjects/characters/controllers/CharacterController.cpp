#include "CharacterController.hpp"

#include <Environment.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterController;

/******************************************************************************/
CharacterController::CharacterController(UrsineEngine::GameObject& aCharacter)
  : mCharacter(&aCharacter)
  , mTimeStartedEnding(0.0)
  , mEndTurnDelay(0.3)
  , mEndingTurn(false)
{
}

/******************************************************************************/
void CharacterController::Update(double aTime)
{
  if(mEndingTurn)
  {
    auto elapsedTime = aTime - mTimeStartedEnding;
    if(elapsedTime >= mEndTurnDelay)
    {
      mEndingTurn = false;
      mTimeStartedEnding = 0.0;

      if(mCharacter != nullptr)
      {
        auto characterBehaviorComponent = mCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          CharacterTurnEnded.Notify(*characterBehaviorComponent);
        }
      }
    }
  }
}

/******************************************************************************/
void CharacterController::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  if(mCharacter != nullptr)
  {
    auto characterBehaviorComponent = mCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      CharacterTurnBegan.Notify(*characterBehaviorComponent);
    }
  }

  ProtectedTakeTurn(aBoard);
}

/******************************************************************************/
void CharacterController::EndTurn()
{
  mEndingTurn = true;
  mTimeStartedEnding = env.GetTime();
}

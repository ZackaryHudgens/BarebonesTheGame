#include "CharacterController.hpp"

#include <Environment.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterController;

/******************************************************************************/
CharacterController::CharacterController(UrsineEngine::GameObject& aCharacter)
  : mBoard(nullptr)
  , mCharacter(&aCharacter)
  , mEndingTurn(false)
  , mEndTurnDelay(0.5)
  , mTimeEndedTurn(0.0)
  , mWaitingForCamera(false)
{
  CameraFinishedMoving.Connect(mObserver, [this]()
  {
    this->HandleCameraFinishedMoving();
  });
}

/******************************************************************************/
void CharacterController::Update(double aTime)
{
  if(mEndingTurn)
  {
    auto elapsedTime = aTime - mTimeEndedTurn;
    if(elapsedTime >= mEndTurnDelay)
    {
      mEndingTurn = false;

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
      mWaitingForCamera = true;
      mBoard = &aBoard;
    }
  }
}

/******************************************************************************/
void CharacterController::EndTurn()
{
  mEndingTurn = true;
  mTimeEndedTurn = env.GetTime();
}

/******************************************************************************/
void CharacterController::HandleCameraFinishedMoving()
{
  if(mWaitingForCamera &&
     mBoard != nullptr)
  {
    mWaitingForCamera = false;
    ProtectedTakeTurn(*mBoard);
  }
}

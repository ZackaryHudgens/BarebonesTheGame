#include "CharacterController.hpp"

#include <Environment.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterController;

/******************************************************************************/
CharacterController::CharacterController(UrsineEngine::GameObject& aCharacter)
  : mBoard(nullptr)
  , mCharacter(&aCharacter)
  , mWaitingForCamera(false)
{
  CameraFinishedMoving.Connect(mObserver, [this]()
  {
    this->HandleCameraFinishedMoving();
  });
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
  if(mCharacter != nullptr)
  {
    auto characterBehaviorComponent = mCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      CharacterTurnEnded.Notify(*characterBehaviorComponent);
    }
  }
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

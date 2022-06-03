#include "CharacterController.hpp"

#include <Environment.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterController;

/******************************************************************************/
CharacterController::CharacterController(UrsineEngine::GameObject& aCharacter)
  : mCharacter(&aCharacter)
{
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
  if(mCharacter != nullptr)
  {
    auto characterBehaviorComponent = mCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      CharacterTurnEnded.Notify(*characterBehaviorComponent);
    }
  }
}

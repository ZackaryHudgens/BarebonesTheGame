#include "AIPlayerBehaviorComponent.hpp"

#include <algorithm>

#include "BoardLayoutComponent.hpp"

#include "EnemyBehaviorComponent.hpp"

#include "Signals.hpp"

#include <iostream>

using Barebones::AIPlayerBehaviorComponent;

/******************************************************************************/
AIPlayerBehaviorComponent::AIPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mCurrentCharacter(nullptr)
  , mBoard(nullptr)
  , mWaitingToTakeTurn(false)
{
  CharacterTurnEnded.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnEnded(aCharacter);
  });
}

/******************************************************************************/
void AIPlayerBehaviorComponent::Update(double aTime)
{
  // "mWaitingToTakeTurn" is used as a one-frame buffer between a character
  // ending its turn and the next character taking a turn.
  if(mWaitingToTakeTurn)
  {
    if(mCurrentCharacter != nullptr)
    {
      auto enemyBehaviorComponent = mCurrentCharacter->GetFirstComponentOfType<EnemyBehaviorComponent>();
      if(enemyBehaviorComponent != nullptr &&
         mBoard != nullptr)
      {
        mWaitingToTakeTurn = false;
        enemyBehaviorComponent->TakeTurn(*mBoard);
      }
    }
  }
}

/******************************************************************************/
void AIPlayerBehaviorComponent::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  mBoard = &aBoard;

  // Keep track of all characters on the enemy side.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    mCharacters = boardLayoutComponent->GetCharactersOnSide(Side::eENEMY);

    // Make the first character take a turn.
    if(!mCharacters.empty())
    {
      auto enemyBehaviorComponent = mCharacters.front()->GetFirstComponentOfType<EnemyBehaviorComponent>();
      if(enemyBehaviorComponent != nullptr)
      {
        mCurrentCharacter = mCharacters.front();
        enemyBehaviorComponent->TakeTurn(aBoard);
      }
    }
  }
}

/******************************************************************************/
void AIPlayerBehaviorComponent::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  if(mCurrentCharacter == aCharacter.GetParent())
  {
    // Find the next character in the list and set them as the current
    // character. If there isn't one, our turn has ended.
    auto foundCharacter = std::find(mCharacters.begin(),
                                    mCharacters.end(),
                                    mCurrentCharacter);
    if(foundCharacter != mCharacters.end())
    {
      auto nextCharacter = std::next(foundCharacter);
      if(nextCharacter == mCharacters.end())
      {
        // All the characters have taken a turn.
        EndTurn();
      }
      else
      {
        // Set the next character as the current one.
        mWaitingToTakeTurn = true;
        mCurrentCharacter = (*nextCharacter);
      }
    }
  }
}

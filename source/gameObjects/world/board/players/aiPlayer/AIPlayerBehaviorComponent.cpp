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
{
  CharacterTurnEnded.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnEnded(aCharacter);
  });
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
        enemyBehaviorComponent->TakeTurn(aBoard);
        mCurrentCharacter = mCharacters.front();
      }
    }
  }
}

/******************************************************************************/
void AIPlayerBehaviorComponent::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  if(mCurrentCharacter == aCharacter.GetParent())
  {
    // Find the next character in the list and make them take
    // a turn. If there isn't one, our turn has ended.
    auto foundCharacter = std::find(mCharacters.begin(),
                                    mCharacters.end(),
                                    mCurrentCharacter);
    if(foundCharacter != mCharacters.end())
    {
      auto nextCharacter = std::next(foundCharacter);
      if(nextCharacter == mCharacters.end())
      {
        // There is no next character.
        EndTurn();
      }
      else
      {
        // Make the next character take a turn.
        auto characterBehaviorComponent = (*nextCharacter)->GetFirstComponentOfType<EnemyBehaviorComponent>();
        if(characterBehaviorComponent != nullptr &&
           mBoard != nullptr)
        {
          characterBehaviorComponent->TakeTurn(*mBoard);
          mCurrentCharacter = (*nextCharacter);
        }
      }
    }
  }
}

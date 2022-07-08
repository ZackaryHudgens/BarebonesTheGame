#include "AIPlayerBehaviorComponent.hpp"

#include <algorithm>

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::AIPlayerBehaviorComponent;

/******************************************************************************/
AIPlayerBehaviorComponent::AIPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mCurrentCharacter(nullptr)
  , mWaitingToTakeTurn(false)
{
  CharacterTurnEnded.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnEnded(aCharacter);
  });

  SetSide(Side::eENEMY);
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
      auto board = GetBoard();
      auto characterBehaviorComponent = mCurrentCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr &&
         board != nullptr)
      {
        mWaitingToTakeTurn = false;
        characterBehaviorComponent->TakeTurn(*board);
      }
    }
  }
}

/******************************************************************************/
void AIPlayerBehaviorComponent::ProtectedTakeTurn()
{
  auto board = GetBoard();
  if(board != nullptr)
  {
    // Keep track of all characters on the enemy side.
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      mCharacters = boardLayoutComponent->GetCharactersOnSide(GetSide());

      // Make the first character take a turn.
      if(!mCharacters.empty())
      {
        auto characterBehaviorComponent = mCharacters.front()->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          mCurrentCharacter = mCharacters.front();
          characterBehaviorComponent->TakeTurn(*board);
        }
      }
      else
      {
        // If there are no characters, end the turn.
        EndTurn();
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

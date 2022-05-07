#include "MoveSkill.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
void MoveSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
    boardLayoutComponent->MoveCharacter(characterLocation,
                                        aLocation);

    SetUsesRemaining(mUsesRemaining - 1);
    if(mUsesRemaining <= 0)
    {
      SetEnabled(false);
    }
  }
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
    tiles = characterBehaviorComponent->GetMovements(aBoard,
                                                     characterLocation);
  }

  return tiles;
}

/******************************************************************************/
void MoveSkill::SetUsesRemaining(int aUses)
{
  mUsesRemaining = aUses;

  std::stringstream descriptionStream;
  descriptionStream << "Moves the character. ";
  descriptionStream << mUsesRemaining << " uses remaining this turn.";
  SetDescription(descriptionStream.str());
}

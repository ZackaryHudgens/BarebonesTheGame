#include "SlashSkill.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::SlashSkill;

/******************************************************************************/
SlashSkill::SlashSkill(UrsineEngine::GameObject& aCharacter)
  : Skill(aCharacter)
{
  SetName("Slash");
  SetDescription("Slashes with a sword.");
}

/******************************************************************************/
void SlashSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                  const TileLocation& aLocation)
{
}

/******************************************************************************/
Barebones::TileList SlashSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(GetCharacter()->GetName());

    // Check to the right.
    auto targetLocaton = characterLocation;
    targetLocaton.first = characterLocation.first + 1;
    if(IsEnemyAtLocation(aBoard,
                         characterLocation))
    {
      tiles.emplace_back(targetLocaton);
    }

    // Check to the left.
    targetLocaton.first = characterLocation.first - 1;
    if(IsEnemyAtLocation(aBoard,
                         characterLocation))
    {
      tiles.emplace_back(targetLocaton);
    }

    targetLocaton.first = characterLocation.first;

    // Check above.
    targetLocaton.second = characterLocation.second + 1;
    if(IsEnemyAtLocation(aBoard,
                         characterLocation))
    {
      tiles.emplace_back(targetLocaton);
    }

    // Check below.
    targetLocaton.second = characterLocation.second - 1;
    if(IsEnemyAtLocation(aBoard,
                         characterLocation))
    {
      tiles.emplace_back(targetLocaton);
    }
  }

  return tiles;
}

/******************************************************************************/
bool SlashSkill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                                   const TileLocation& aLocation)
{
  bool success = false;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto target = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(target != nullptr)
    {
      auto characterBehaviorComponent = target->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        if(characterBehaviorComponent->GetSide() == Side::eENEMY)
        {
          success = true;
        }
      }
    }
  }

  return success;
}

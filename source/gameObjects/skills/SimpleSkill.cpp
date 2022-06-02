#include "SimpleSkill.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::SimpleSkill;

/******************************************************************************/
SimpleSkill::SimpleSkill(UrsineEngine::GameObject& aCharacter, int aRange)
  : Skill(aCharacter)
  , mRange(aRange)
{
}

/******************************************************************************/
Barebones::TileList SimpleSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                               const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    // Check tiles to the right.
    auto targetLocation = aSourceLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.first += 1;
      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        tiles.emplace_back(targetLocation);
        break;
      }
    }

    // Check tiles to the left.
    targetLocation = aSourceLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.first -= 1;
      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        tiles.emplace_back(targetLocation);
        break;
      }
    }

    // Check tiles above.
    targetLocation = aSourceLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.second += 1;
      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        tiles.emplace_back(targetLocation);
        break;
      }
    }

    // Check tiles below.
    targetLocation = aSourceLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.second -= 1;
      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        tiles.emplace_back(targetLocation);
        break;
      }
    }
  }

  return tiles;
}

/******************************************************************************/
Barebones::TileList SimpleSkill::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                     const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto characterLocation = GetCharacterLocation(aBoard);

    // Check tiles to the right.
    auto targetLocation = characterLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.first += 1;
      tiles.emplace_back(targetLocation);

      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        break;
      }
    }

    // Check tiles to the left.
    targetLocation = characterLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.first -= 1;
      tiles.emplace_back(targetLocation);

      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        break;
      }
    }

    // Check tiles above.
    targetLocation = characterLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.second += 1;
      tiles.emplace_back(targetLocation);

      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        break;
      }
    }

    // Check tiles below.
    targetLocation = characterLocation;
    for(int i = 0; i < mRange; ++i)
    {
      targetLocation.second -= 1;
      tiles.emplace_back(targetLocation);

      auto target = boardLayoutComponent->GetCharacterAtLocation(targetLocation);
      if(target != nullptr)
      {
        break;
      }
    }
  }
  return tiles;
}

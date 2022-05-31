#include "BoneThrowSkill.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
  , mRange(2)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}

/******************************************************************************/
Barebones::TileList BoneThrowSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
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
Barebones::TileList BoneThrowSkill::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                        const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto parent = GetParent();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(parent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());

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

/******************************************************************************/
void BoneThrowSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aSourceLocation)
{
}

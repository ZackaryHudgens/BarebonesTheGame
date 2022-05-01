#include "FireballSpell.hpp"

#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "FireballSpellEffectBehaviorComponent.hpp"

using Barebones::FireballSpell;

/******************************************************************************/
FireballSpell::FireballSpell(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
  , mRadius(2)
{
  SetName("Fireball");

  std::stringstream ss;
  ss << "Deals 8d6...wait, hang on.\n\n";
  ss << "Deals 30 damage to each\n";
  ss << "creature within the radius.";
  SetDescription(ss.str());
}

/******************************************************************************/
Barebones::TileList FireballSpell::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    TileLocation tileLocation;

    // All tiles are valid for executing this skill.
    for(int c = 0; c < boardLayoutComponent->GetColumns(); ++c)
    {
      tileLocation.first = c;
      for(int r = 0; r < boardLayoutComponent->GetRows(); ++r)
      {
        tileLocation.second = r;
        tiles.emplace_back(tileLocation);
      }
    }
  }

  return tiles;
}

/******************************************************************************/
Barebones::TileList FireballSpell::GetTilesToHighlight(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto humanPlayerBehaviorComponent = parent->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    if(humanPlayerBehaviorComponent != nullptr)
    {
      auto playerLocation = humanPlayerBehaviorComponent->GetLocation();

      auto leftEdge = playerLocation.first - mRadius;
      auto rightEdge = playerLocation.first + mRadius;
      auto bottomEdge = playerLocation.second - mRadius;
      auto topEdge = playerLocation.second + mRadius;

      for(int column = leftEdge; column <= rightEdge; ++column)
      {
        for(int row = bottomEdge; row <= topEdge; ++row)
        {
          TileLocation affectedTile;
          affectedTile.first = column;
          affectedTile.second = row;
          tiles.emplace_back(affectedTile);
        }
      }
    }
  }

  return tiles;
}

/******************************************************************************/
void FireballSpell::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                     const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    for(auto& affectedTile : GetTilesToHighlight(aBoard))
    {
      // Place a spell effect on this tile.
      std::stringstream nameStream;
      auto tile = boardLayoutComponent->GetTileAtLocation(affectedTile);
      if(tile != nullptr)
      {
        // Create a GameObject with a unique name for the fireball sprite.
        nameStream << "fireballEffect" << affectedTile.first << affectedTile.second;
        auto spellEffectObject = std::make_unique<UrsineEngine::GameObject>(nameStream.str());
        nameStream.str("");

        // Add the spell effect to the GameObject, then retrieve the height of the sprite.
        spellEffectObject->AddComponent(std::make_unique<FireballSpellEffectBehaviorComponent>());
        auto fireballSprite = spellEffectObject->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();
        auto fireballHeight = fireballSprite->GetHeight();

        // Retrieve the height of the tile.
        double tileHeight = 0.0;
        auto tileMesh = tile->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
        if(tileMesh != nullptr)
        {
          tileHeight = tileMesh->GetHeight();
        }

        // Place the fireball sprite on the file.
        auto tilePos = tile->GetPosition();
        tilePos.y += ((tileHeight / 2.0) + (fireballHeight / 2.0));
        spellEffectObject->SetPosition(tilePos);

        // Finally, add the fireball sprite to the current scene.
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          scene->AddObject(std::move(spellEffectObject));
        }
      }

      // Deal damage to the character on this tile, if there is one.
      auto character = boardLayoutComponent->GetCharacterAtLocation(affectedTile);
      if(character != nullptr)
      {
        auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          characterBehaviorComponent->DealDamage(30);
        }
      }
    }
  }
}

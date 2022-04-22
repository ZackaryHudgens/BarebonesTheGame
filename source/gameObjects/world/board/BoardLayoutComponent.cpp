#include "BoardLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "Signals.hpp"

#include "BoardTurnManagerComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "TileFactory.hpp"
#include "TileBehaviorComponent.hpp"
#include "TileMeshComponent.hpp"

#include "SkillActionBehaviorComponent.hpp"

using Barebones::BoardLayoutComponent;

/******************************************************************************/
BoardLayoutComponent::BoardLayoutComponent()
  : Component()
  , mHoveredTile(nullptr)
  , mSkillUsedForHighlighting(nullptr)
  , mTileSpacing(0.2)
  , mColumns(7)
  , mRows(7)
  , mFinishedTiles(0)
{
  TileReadyForUse.Connect(*this, [this](UrsineEngine::GameObject& aTile)
  {
    this->HandleTileReadyForUse(aTile);
  });

  HumanPlayerMoved.Connect(*this, [this](HumanPlayerBehaviorComponent& aPlayer)
  {
    this->HandleHumanPlayerMoved(aPlayer);
  });

  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  SkillSelectedFromMenu.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillSelectedFromMenu(aSkill);
  });

  SkillExecuted.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillExecuted(aSkill);
  });

  SkillCancelled.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillCancelled(aSkill);
  });

  CharacterDied.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterDied(aCharacter);
  });
}

/******************************************************************************/
void BoardLayoutComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    std::stringstream ss;

    // For each column and row in the board, create and place a tile object.
    // Also add a nullptr into the characters list; as characters are added
    // and removed from the board, the characters list will be updated
    // as well.
    for(int x = 0; x < mColumns; ++x)
    {
      std::vector<UrsineEngine::GameObject*> row;
      std::vector<UrsineEngine::GameObject*> characters;

      for(int y = 0; y < mRows; ++y)
      {
        ss << "tile_" << x << "_" << y;
        auto tile = TileFactory::CreateTile(TileType::eDEFAULT, ss.str());

        // The z-position in world space corresponds to the y-position
        // on the 2D grid. It's made negative here so that (0, 0) on
        // the grid is in the bottom left.
        tile->SetPosition(glm::vec3((double)x + (mTileSpacing * x),
                                     0.0,
                                     -1 * (double)y - (mTileSpacing * y)));
        parent->AddChild(std::move(tile));
        row.emplace_back(parent->GetChild(ss.str()));
        characters.emplace_back(nullptr);
        ss.str("");
      }

      mTiles.emplace_back(row);
      mCharacters.emplace_back(characters);
    }
  }
}

/******************************************************************************/
bool BoardLayoutComponent::AddCharacterAtLocation(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                                  const TileLocation& aLocation)
{
  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    if(aLocation.first < mTiles.size() &&
       aLocation.first >= 0)
    {
      if(aLocation.second < mTiles[aLocation.first].size() &&
         aLocation.second >= 0)
      {
        // Move the character to stand on top of the tile.
        auto tile = mTiles[aLocation.first][aLocation.second];
        auto newPos = tile->GetPosition();
        newPos.y = tile->GetFirstComponentOfType<TileMeshComponent>()->GetHeight();
        aObject->SetPosition(newPos);

        // Add the character as a child object of the board.
        parent->AddChild(std::move(aObject));

        // Add the object to the characters list.
        mCharacters[aLocation.first][aLocation.second] = parent->GetChildren().back();
        success = true;
      }
    }
  }

  return success;
}

/******************************************************************************/
void BoardLayoutComponent::RemoveCharacterAtLocation(const TileLocation& aLocation)
{
  if(aLocation.first < mCharacters.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mCharacters[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      auto obj = mCharacters[aLocation.first][aLocation.second];
      if(obj != nullptr)
      {
        // The character will be deleted on the next update.
        obj->ScheduleForDeletion();
      }
    }
  }
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetTileAtLocation(const TileLocation& aLocation)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aLocation.first < mTiles.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mTiles[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      obj = mTiles[aLocation.first][aLocation.second];
    }
  }

  return obj;
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetCharacterAtLocation(const TileLocation& aLocation)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aLocation.first < mCharacters.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mCharacters[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      obj = mCharacters[aLocation.first][aLocation.second];
    }
  }

  return obj;
}

/******************************************************************************/
void BoardLayoutComponent::MoveCharacter(const TileLocation& aCurrentLocation,
                                         const TileLocation& aNewLocation)
{
  auto character = GetCharacterAtLocation(aCurrentLocation);
  auto newTile = GetTileAtLocation(aNewLocation);
  if(character != nullptr &&
     newTile != nullptr)
  {
    // First, check if there is already a character in the new location.
    if(GetCharacterAtLocation(aNewLocation) == nullptr)
    {
      // Next, move the character to the new position in world space.
      auto tileMesh = newTile->GetFirstComponentOfType<TileMeshComponent>();
      auto charBehaviorComp = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(tileMesh != nullptr &&
         charBehaviorComp != nullptr)
      {
        auto newPosition = newTile->GetPosition();
        newPosition.y = tileMesh->GetHeight();
        charBehaviorComp->MoveToPosition(newPosition,
                                         0.3);
      }

      // Finally, update the character map.
      mCharacters[aCurrentLocation.first][aCurrentLocation.second] = nullptr;
      mCharacters[aNewLocation.first][aNewLocation.second] = character;
    }
  }
}

/******************************************************************************/
Barebones::TileLocation BoardLayoutComponent::GetLocationOfCharacter(const std::string& aName)
{
  TileLocation tile(-1, -1);

  int x = 0;
  int y = 0;
  bool found = false;
  for(const auto& column : mCharacters)
  {
    y = 0;
    for(const auto& character : column)
    {
      if(character != nullptr)
      {
        if(character->GetName() == aName)
        {
          found = true;
          tile.first = x;
          tile.second = y;

          break;
        }
      }

      ++y;
    }

    if(found)
    {
      break;
    }
    else
    {
      ++x;
    }
  }

  return tile;
}

/******************************************************************************/
std::vector<UrsineEngine::GameObject*> BoardLayoutComponent::GetCharactersOnSide(const Side& aSide)
{
  std::vector<UrsineEngine::GameObject*> characters;

  for(auto& column : mCharacters)
  {
    for(auto& character : column)
    {
      if(character != nullptr)
      {
        auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          if(characterBehaviorComponent->GetSide() == aSide)
          {
            characters.emplace_back(character);
          }
        }
      }
    }
  }

  return characters;
}

/******************************************************************************/
void BoardLayoutComponent::HandleTileReadyForUse(UrsineEngine::GameObject& aTile)
{
  ++mFinishedTiles;

  if(mFinishedTiles == (mRows * mColumns))
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      // The board is ready, so begin taking turns.
      auto turnManagerComponent = parent->GetFirstComponentOfType<BoardTurnManagerComponent>();
      if(turnManagerComponent != nullptr)
      {
        turnManagerComponent->Start();
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
{
  // Only change the currently hovered tile if the player that moved is the
  // current player in the turn manager.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto turnManager = parent->GetFirstComponentOfType<BoardTurnManagerComponent>();
    if(turnManager != nullptr)
    {
      if(aPlayer.GetParent() == turnManager->GetCurrentPlayer())
      {
        auto location = aPlayer.GetLocation();
        if(location.first < mColumns &&
           location.first >= 0 &&
           location.second < mRows &&
           location.second >= 0)
        {
          // Un-hover the tile at the previous location.
          if(mHoveredTile != nullptr)
          {
            auto prevTileBehaviorComp = mHoveredTile->GetFirstComponentOfType<TileBehaviorComponent>();
            if(prevTileBehaviorComp != nullptr)
            {
              prevTileBehaviorComp->SetHovered(false);
            }
          }

          // Hover over the tile at the new location.
          auto newTile = GetTileAtLocation(location);
          if(newTile != nullptr)
          {
            auto newTileBehaviorComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
            if(newTileBehaviorComp != nullptr)
            {
              newTileBehaviorComp->SetHovered(true);
            }

            mHoveredTile = newTile;
          }

          // Update the highlighted tiles, if necessary.
          if(mSkillUsedForHighlighting != nullptr)
          {
            HandleSkillSelectedFromMenu(*mSkillUsedForHighlighting);
          }
        }
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  auto humanPlayerBehaviorComponent = dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer);
  if(humanPlayerBehaviorComponent != nullptr)
  {
    HandleHumanPlayerMoved(*humanPlayerBehaviorComponent);
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillSelectedFromMenu(Skill& aSkill)
{
  mSkillUsedForHighlighting = &aSkill;

  // First, un-highlight all highlighted tiles.
  for(auto tile : mHighlightedTiles)
  {
    auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
    if(tileBehaviorComponent != nullptr)
    {
      tileBehaviorComponent->SetHighlighted(false);
    }
  }
  mHighlightedTiles.clear();

  // Next, highlight all tiles affected by this skill.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto tileLocations = aSkill.GetTilesToHighlight(*parent);
    for(const auto tileLocation : tileLocations)
    {
      auto tile = GetTileAtLocation(tileLocation);
      if(tile != nullptr)
      {
        auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileBehaviorComponent != nullptr)
        {
          tileBehaviorComponent->SetHighlightColor(glm::vec3(0.682, 0.729, 0.537));
          tileBehaviorComponent->SetHighlighted(true);

          mHighlightedTiles.emplace_back(tile);
        }
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillExecuted(Skill& aSkill)
{
  if(&aSkill == mSkillUsedForHighlighting)
  {
    for(auto tile : mHighlightedTiles)
    {
      auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
      if(tileBehaviorComponent != nullptr)
      {
        tileBehaviorComponent->SetHighlighted(false);
      }
    }

    mHighlightedTiles.clear();
    mSkillUsedForHighlighting = nullptr;
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillCancelled(Skill& aSkill)
{
  HandleSkillExecuted(aSkill);
}

/******************************************************************************/
void BoardLayoutComponent::HandleCharacterDied(CharacterBehaviorComponent& aCharacter)
{
  // When a character dies, don't remove it right away; just set
  // the character at their location to nullptr.
  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    auto location = GetLocationOfCharacter(characterObject->GetName());
    if(location.first >= 0 &&
       location.second < mCharacters.size())
    {
      if(location.second >= 0 &&
         location.second < mCharacters.at(location.first).size())
      {
        mCharacters.at(location.first).at(location.second) = nullptr;
      }
    }
  }
}

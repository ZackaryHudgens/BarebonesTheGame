#include "BoardLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "TileFactory.hpp"
#include "TileBehaviorComponent.hpp"
#include "TileMeshComponent.hpp"

using Barebones::BoardLayoutComponent;

/******************************************************************************/
BoardLayoutComponent::BoardLayoutComponent()
  : Component()
  , mTileSpacing(0.2)
  , mColumns(7)
  , mRows(7)
{
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
void BoardLayoutComponent::MoveSelectedCharacter(const TileLocation& aLocation)
{
  // First, move the character to the new position in
  // world space.
  auto tile = GetTileAtLocation(aLocation);
  if(tile != nullptr &&
     mSelectedCharacter != nullptr)
  {
    auto tileMesh = tile->GetFirstComponentOfType<TileMeshComponent>();
    auto charComp = mSelectedCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(tileMesh != nullptr &&
       charComp != nullptr)
    {
      auto newPos = tile->GetPosition();
      newPos.y = tileMesh->GetHeight();
      charComp->MoveCharacter(newPos,
                              0.3);
    }
  }

  // Next, update the character map.
  bool found = false;
  for(int column = 0; column < mCharacters.size(); ++column)
  {
    for(int row = 0; row < mCharacters[column].size(); ++row)
    {
      if(mCharacters[column][row] == mSelectedCharacter)
      {
        // Set the character at the previous location to nullptr.
        mCharacters[column][row] = nullptr;

        // Set the character at the new location to the selected character.
        mCharacters[aLocation.first][aLocation.second] = mSelectedCharacter;
        found = true;
        break;
      }
    }

    if(found)
    {
      break;
    }
  }
}

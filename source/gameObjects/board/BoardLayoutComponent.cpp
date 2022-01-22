#include "BoardLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <iostream>

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
  , mColumns(5)
  , mRows(7)
{
  CharacterSelected.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleSelectionChanged(aCharacter);
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
bool BoardLayoutComponent::AddCharacterAtPosition(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                                  int aColumn,
                                                  int aRow)
{
  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    if(aColumn < mTiles.size() &&
       aColumn >= 0)
    {
      if(aRow < mTiles[aColumn].size() &&
         aRow >= 0)
      {
        // Move the character to stand on top of the tile.
        auto tile = mTiles[aColumn][aRow];
        auto newPos = tile->GetPosition();
        newPos.y = tile->GetFirstComponentOfType<TileMeshComponent>()->GetHeight();
        aObject->SetPosition(newPos);

        parent->AddChild(std::move(aObject));

        // Add the object to the characters list.
        if(aColumn < mCharacters.size() &&
           aColumn >= 0)
        {
          if(aRow < mCharacters[aColumn].size() &&
             aRow >= 0)
          {
            mCharacters[aColumn][aRow] = parent->GetChildren().back();
          }
        }
        success = true;
      }
    }
  }

  return success;
}

/******************************************************************************/
void BoardLayoutComponent::RemoveCharacterAtPosition(int aColumn,
                                                     int aRow)
{
  if(aColumn < mCharacters.size() &&
     aColumn >= 0)
  {
    if(aRow < mCharacters[aColumn].size() &&
       aRow >= 0)
    {
      auto obj = mCharacters[aColumn][aRow];
      if(obj != nullptr)
      {
        obj->ScheduleForDeletion();
      }
    }
  }
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetTileAtPosition(int aColumn,
                                                                  int aRow)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aColumn < mTiles.size() &&
     aColumn >= 0)
  {
    if(aRow < mTiles[aColumn].size() &&
       aRow >= 0)
    {
      obj = mTiles[aColumn][aRow];
    }
  }

  return obj;
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetCharacterAtPosition(int aColumn,
                                                                       int aRow)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aColumn < mCharacters.size() &&
     aColumn >= 0)
  {
    if(aRow < mCharacters[aColumn].size() &&
       aRow >= 0)
    {
      obj = mCharacters[aColumn][aRow];
    }
  }

  return obj;
}

/******************************************************************************/
void BoardLayoutComponent::HandleSelectionChanged(CharacterBehaviorComponent& aCharacter)
{
  // First, de-highlight any spaces that were previously highlighted.
  for(auto& column : mTiles)
  {
    for(auto& row : column)
    {
      if(row != nullptr)
      {
        auto tileComp = row->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileComp != nullptr)
        {
          tileComp->SetHighlighted(false);
        }
      }
    }
  }

  // When a character is selected, highlight each of the tiles
  // that it can move to.
  if(aCharacter.IsSelected())
  {
    auto parent = aCharacter.GetParent();
    if(parent != nullptr)
    {
      // Determine if this character is on the board. If it is,
      // determine the row and column.
      bool onBoard = false;
      TileLocation location;

      for(int column = 0; column < mCharacters.size(); ++column)
      {
        for(int row = 0; row < mCharacters[column].size(); ++row)
        {
          if(mCharacters[column][row] == parent)
          {
            location.first = column;
            location.second = row;
            onBoard = true;
            break;
          }
        }
      }

      if(onBoard)
      {
        // Determine which tiles to highlight.
        for(const auto& movement : aCharacter.GetMovements(location))
        {
          if(movement.first < mTiles.size() &&
             movement.first >= 0)
          {
            if(movement.second < mTiles[movement.first].size() &&
               movement.second >= 0)
            {
              // Highlight this tile.
              auto tileComp = mTiles[movement.first][movement.second]->GetFirstComponentOfType<TileBehaviorComponent>();
              if(tileComp != nullptr)
              {
                tileComp->SetHighlighted(true);
              }
            }
          }
        }
      }

      // Finally, update the currently selected character.
      mSelectedCharacter = aCharacter.IsSelected() ? parent : nullptr;
    }
  }
}

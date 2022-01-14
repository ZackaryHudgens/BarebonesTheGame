#include "BoardBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "TileFactory.hpp"
#include "TileBehaviorComponent.hpp"
#include "TileMeshComponent.hpp"

using Barebones::BoardBehaviorComponent;

/******************************************************************************/
BoardBehaviorComponent::BoardBehaviorComponent()
  : Component()
  , mScaleTime(0.03)
  , mTileSpacing(0.2)
  , mColumns(7)
  , mRows(7)
  , mInitialized(false)
{
  CharacterSelected.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleSelectionChanged(aCharacter);
  });
}

/******************************************************************************/
void BoardBehaviorComponent::Initialize()
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

        // The z-position corresponds to the y-position on a 2D grid. It's made
        // negative so that (0, 0) on the grid is in the bottom left.
        tile->SetPosition(glm::vec3((double)x + (mTileSpacing * x),
                                     0.0,
                                     -1 * (double)y - (mTileSpacing * y)));
        tile->SetScale(glm::vec3(0.01,
                                 0.01,
                                 0.01));
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
void BoardBehaviorComponent::Update()
{
  if(!mInitialized)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto children = parent->GetChildren();
      for(auto& child : children)
      {
        // For each tile, calculate their new scalar value via
        // interpolation. Because we scale each axis evenly, we can
        // just use the x-axis scale as our starting point ([0, 0]
        // in the matrix).
        if(child->GetFirstComponentOfType<TileMeshComponent>() != nullptr)
        {
          auto transform = child->GetScalarTransform();
          double scalar = transform[0][0];
          double newScalar = glm::mix(scalar, 1.0, mScaleTime);
          newScalar = std::min(newScalar, 1.0);

          child->SetScale(glm::vec3(newScalar,
                                    newScalar,
                                    newScalar));

          if(newScalar == 1.0)
          {
            mInitialized = true;
          }
        }
      }
    }
  }
}

/******************************************************************************/
bool BoardBehaviorComponent::AddObjectAtPosition(std::unique_ptr<UrsineEngine::GameObject> aObject,
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
void BoardBehaviorComponent::RemoveObjectAtPosition(int aColumn,
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
UrsineEngine::GameObject* BoardBehaviorComponent::GetObjectAtPosition(int aColumn,
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
void BoardBehaviorComponent::HandleSelectionChanged(CharacterBehaviorComponent& aCharacter)
{
  // When a character is selected, highlight each of the tiles
  // that it can move to.
  auto parent = aCharacter.GetParent();
  if(parent != nullptr)
  {
    // Determine if this character is on the board. If it is,
    // determine the column and row it's in.
    bool onBoard = false;
    TileLocation location;

    for(int c = 0; c < mCharacters.size(); ++c)
    {
      for(int r = 0; r < mCharacters[c].size(); ++r)
      {
        if(mCharacters[c][r] == parent)
        {
          location.first = c;
          location.second = r;
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
  }
}

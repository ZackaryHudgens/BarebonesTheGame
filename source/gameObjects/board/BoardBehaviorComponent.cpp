#include "BoardBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "TileFactory.hpp"
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
        mTiles.emplace_back(parent->GetChild(ss.str()));
        mCharacters.emplace_back(nullptr);
        ss.str("");
      }
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
    int index = (aColumn * mRows) + aRow;
    if(index < mTiles.size())
    {
      auto tile = mTiles[index];
      auto newPos = tile->GetPosition();
      newPos.y = tile->GetFirstComponentOfType<TileMeshComponent>()->GetHeight();
      aObject->SetPosition(newPos);

      parent->AddChild(std::move(aObject));
      mCharacters[index] = parent->GetChildren().back();
      success = true;
    }
  }

  return success;
}

/******************************************************************************/
void BoardBehaviorComponent::RemoveObjectAtPosition(int aColumn,
                                                    int aRow)
{
  int index = (aColumn * mRows) + aRow;
  if(index < mCharacters.size())
  {
    auto obj = mCharacters[index];
    if(obj != nullptr)
    {
      obj->ScheduleForDeletion();
    }
  }
}

/******************************************************************************/
UrsineEngine::GameObject* BoardBehaviorComponent::GetObjectAtPosition(int aColumn,
                                                                      int aRow)
{
  UrsineEngine::GameObject* obj = nullptr;

  int index = (aColumn * mRows) + aRow;
  if(index < mCharacters.size())
  {
    obj = mCharacters[index];
  }

  return obj;
}

/******************************************************************************/
void BoardBehaviorComponent::HandleSelectionChanged(CharacterBehaviorComponent& aCharacter)
{
  // When a character is selected, highlight each of the tiles
  // that it can move to.
  auto charParent = aCharacter.GetParent();
  if(charParent != nullptr)
  {
    auto charObj = std::find(mCharacters.begin(),
                             mCharacters.end(),
                             charParent);
    if(charObj != mCharacters.end())
    {
      int index = charObj - mCharacters.begin();
      
      // Use the character's movement options to determine
      // which tiles to highlight.
      int column = index % mColumns;
      int row = index - (column * mRows);

      int horizontalMovement = aCharacter.GetHorizontalDistance();
      int verticalMovement = aCharacter.GetVerticalDistance();
      int diagonalDistance = aCharacter.GetDiagonalDistance();
    }
  }
}

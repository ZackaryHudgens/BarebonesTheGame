#include "BoardBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "TileFactory.hpp"
#include "TileMeshComponent.hpp"

using Barebones::BoardBehaviorComponent;

/******************************************************************************/
BoardBehaviorComponent::BoardBehaviorComponent()
  : Component()
  , mScaleTime(0.03)
  , mColumns(5)
  , mRows(5)
  , mInitialized(false)
{
}

/******************************************************************************/
void BoardBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    std::stringstream ss;

    // For each column and row in the board, create and place a tile object.
    for(int c = 0; c < mColumns; ++c)
    {
      std::vector<UrsineEngine::GameObject*> row;
      for(int r = 0; r < mRows; ++r)
      {
        ss << "tile_" << c << "_" << r;
        auto tile = TileFactory::CreateTile(TileType::eDEFAULT, ss.str());

        tile->SetPosition(glm::vec3((double)c + (c * 0.5),
                                     0.0,
                                     -1 * ((double)r + (r * 0.5))));
        tile->SetScale(glm::vec3(0.01,
                                 0.01,
                                 0.01));
        parent->AddChild(std::move(tile));
        row.emplace_back(parent->GetChild(ss.str()));
        ss.str("");
      }
      mTileMap.emplace_back(row);
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
    if(aColumn < mTileMap.size())
    {
      if(aRow < mTileMap[aColumn].size())
      {
        auto tile = mTileMap[aColumn][aRow];
        auto newPos = tile->GetPosition();
        newPos.y = tile->GetFirstComponentOfType<TileMeshComponent>()->GetHeight();
        aObject->SetPosition(newPos);

        parent->AddChild(std::move(aObject));
        success = true;
      }
    }
  }

  return success;
}

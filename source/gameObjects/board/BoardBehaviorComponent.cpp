#include "BoardBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <GameObject.hpp>

#include "TileFactory.hpp"

using Barebones::BoardBehaviorComponent;

/******************************************************************************/
BoardBehaviorComponent::BoardBehaviorComponent()
  : Component()
  , mScaleTime(0.03)
  , mRows(5)
  , mColumns(5)
  , mInitialized(false)
{
}

/******************************************************************************/
void BoardBehaviorComponent::Load()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    std::stringstream ss;

    // For each row and column in the board, create and place a tile object.
    for(int r = 0; r < mRows; ++r)
    {
      for(int c = 0; c < mColumns; ++c)
      {
        ss << "tile_" << r << "_" << c;
        auto tile = TileFactory::CreateTile(TileType::eDEFAULT, ss.str());
        ss.str("");

        tile->SetPosition(glm::vec3((double)c,
                                     0.0,
                                     (double)r));
        tile->SetScale(glm::vec3(0.01,
                                 0.01,
                                 0.01));
        parent->AddChild(std::move(tile));
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

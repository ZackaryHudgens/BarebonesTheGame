#include "UsingSkillBoardInputState.hpp"

#include "BoardInputComponent.hpp"
#include "BoardLayoutComponent.hpp"
#include "DefaultBoardInputState.hpp"

#include "CharacterSkillComponent.hpp"

#include "TileBehaviorComponent.hpp"

#include <iostream>

using Barebones::UsingSkillBoardInputState;

/******************************************************************************/
UsingSkillBoardInputState::UsingSkillBoardInputState(UrsineEngine::GameObject& aObject,
                                                     CharacterSkillComponent& aSkill)
  : BoardInputState(aObject)
  , mSkill(&aSkill)
{
  // Upon entering this state, highlight all pertinent tiles as
  // dictated by the skill.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(inputComponent != nullptr &&
       layoutComponent != nullptr)
    {
      auto currentLocation = inputComponent->GetPlayerLocation();
      auto tilesToHighlight = mSkill->GetTilesToHighlight(*parent,
                                                          currentLocation);

      for(const auto& tileLocation : tilesToHighlight)
      {
        auto tile = layoutComponent->GetTileAtLocation(tileLocation);
        if(tile != nullptr)
        {
          auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
          if(tileBehaviorComponent != nullptr)
          {
            tileBehaviorComponent->SetHighlightColor(mSkill->GetHighlightColor());
            tileBehaviorComponent->SetHighlighted(true);

            mHighlightedTiles.emplace_back(tile);
          }
        }
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> UsingSkillBoardInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                        int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(inputComponent != nullptr)
    {
      auto currentLocation = inputComponent->GetPlayerLocation();

      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_UP:
        case UrsineEngine::KeyCode::eKEY_W:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                         currentLocation.second + 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                         currentLocation.second - 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first - 1,
                                                         currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first + 1,
                                                         currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If the current position is valid for executing the skill,
          // execute it and revert to a default board input state.
          if(mSkill != nullptr)
          {
            auto parent = GetParent();
            if(parent != nullptr)
            {
              auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
              if(inputComponent != nullptr)
              {
                if(mSkill->IsTileValid(*parent,
                                       inputComponent->GetPlayerLocation()))
                {
                  mSkill->Execute(*parent,
                                  inputComponent->GetPlayerLocation());
                  newState = std::make_unique<DefaultBoardInputState>(*parent);

                  // Finally, un-highlight all the tiles that were highlighted.
                  for(auto& tile : mHighlightedTiles)
                  {
                    auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
                    if(tileBehaviorComponent != nullptr)
                    {
                      tileBehaviorComponent->SetHighlighted(false);
                    }
                  }
                }
              }
            }
          }
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> UsingSkillBoardInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                         int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_ENTER:
    {
      break;
    }
    default:
    {
      newState = HandleKeyPressed(aCode,
                                  aMods);
      break;
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> UsingSkillBoardInputState::HandlePlayerMoved(const TileLocation& aPrevLocation,
                                                                                         const TileLocation& aNewLocation)
{
  std::unique_ptr<BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(layoutComponent != nullptr &&
       inputComponent != nullptr)
    {
      // Un-hover the tile at the previous location.
      auto prevTile = layoutComponent->GetTileAtLocation(aPrevLocation);
      if(prevTile != nullptr)
      {
        auto prevTileBehaviorComp = prevTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(prevTileBehaviorComp != nullptr)
        {
          prevTileBehaviorComp->SetHovered(false);
        }
      }

      // Hover over the tile at the new location.
      auto newTile = layoutComponent->GetTileAtLocation(aNewLocation);
      if(newTile != nullptr)
      {
        auto newTileBehaviorComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(newTileBehaviorComp != nullptr)
        {
          newTileBehaviorComp->SetHovered(true);
        }
      }
    }
  }

  return nullptr;
}

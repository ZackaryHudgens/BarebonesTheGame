#include "UsingSkillBoardInputState.hpp"

#include "BoardInputComponent.hpp"
#include "BoardLayoutComponent.hpp"
#include "DefaultBoardInputState.hpp"

#include "CharacterSkillComponent.hpp"

#include "TileBehaviorComponent.hpp"

using Barebones::UsingSkillBoardInputState;

/******************************************************************************/
UsingSkillBoardInputState::UsingSkillBoardInputState(UrsineEngine::GameObject& aObject,
                                                     UrsineEngine::GameObject& aSkill)
  : BoardInputState(aObject)
  , mSkill(&aSkill)
{
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
          MoveToTile(TileLocation(currentLocation.first,
                                  currentLocation.second + 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          MoveToTile(TileLocation(currentLocation.first,
                                  currentLocation.second - 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          MoveToTile(TileLocation(currentLocation.first - 1,
                                  currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          MoveToTile(TileLocation(currentLocation.first + 1,
                                  currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If the current position is valid for executing the skill,
          // execute it and revert to a default board input state.
          auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
          if(skillComponent != nullptr)
          {
            auto parent = GetParent();
            if(parent != nullptr)
            {
              auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
              if(inputComponent != nullptr)
              {
                if(skillComponent->IsTileValid(*parent,
                                               inputComponent->GetPlayerLocation()))
                {
                  skillComponent->Execute();

                  newState = std::make_unique<DefaultBoardInputState>(*parent);
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
void UsingSkillBoardInputState::HandlePlayerMoved(const TileLocation& aPrevLocation,
                                                  const TileLocation& aNewLocation)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layoutComponent != nullptr)
    {
      // Un-highlight the tile at the previous location.
      auto prevTile = layoutComponent->GetTileAtLocation(aPrevLocation);
      if(prevTile != nullptr)
      {
        auto prevTileBehaviorComp = prevTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(prevTileBehaviorComp != nullptr)
        {
          prevTileBehaviorComp->SetHighlighted(false);
        }
      }

      // Highlight the tile at the new location.
      auto newTile = layoutComponent->GetTileAtLocation(aNewLocation);
      if(newTile != nullptr)
      {
        auto newTileBehaviorComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(newTileBehaviorComp != nullptr)
        {
          newTileBehaviorComp->SetHighlighted(true,
                                              glm::vec3(0.5, 0.5, 0.5));
        }
      }
    }
  }
}

/******************************************************************************/
void UsingSkillBoardInputState::MoveToTile(const TileLocation& aLocation)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(layoutComponent != nullptr &&
       inputComponent != nullptr)
    {
      // If a tile exists at the given location, move to that tile.
      auto newTile = layoutComponent->GetTileAtLocation(aLocation);
      if(newTile != nullptr)
      {
        inputComponent->SetPlayerLocation(aLocation);
      }
    }
  }
}

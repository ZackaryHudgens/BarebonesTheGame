#include "UsingSkillBoardInputState.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterSkillComponent.hpp"
#include "DefaultBoardInputState.hpp"
#include "TileBehaviorComponent.hpp"

using Barebones::UsingSkillBoardInputState;

/******************************************************************************/
UsingSkillBoardInputState::UsingSkillBoardInputState(UrsineEngine::GameObject& aObject,
                                                     UrsineEngine::GameObject& aSkill,
                                                     int aXPos,
                                                     int aYPos)
  : BoardInputState(aObject, aXPos, aYPos)
  , mSkill(&aSkill)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> UsingSkillBoardInputState::ProtectedHandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                 int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    int x = GetPlayerXLocation();
    int y = GetPlayerYLocation();

    switch(aCode)
    {
      case UrsineEngine::KeyCode::eKEY_UP:
      case UrsineEngine::KeyCode::eKEY_W:
      {
        HoverOverTile(x,
                      y + 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_DOWN:
      case UrsineEngine::KeyCode::eKEY_S:
      {
        HoverOverTile(x,
                      y - 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_LEFT:
      case UrsineEngine::KeyCode::eKEY_A:
      {
        HoverOverTile(x - 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_RIGHT:
      case UrsineEngine::KeyCode::eKEY_D:
      {
        HoverOverTile(x + 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_ENTER:
      {
        // If the current position is valid for executing the skill,
        // execute it and revert to a default board input state.
        auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
        if(skillComponent != nullptr)
        {
          TileLocation playerLocation(GetPlayerXLocation(),
                                      GetPlayerYLocation());
          if(skillComponent->IsTileValid(*GetParent(),
                                         playerLocation))
          {
            skillComponent->Execute();
            
            newState = std::make_unique<DefaultBoardInputState>(*GetParent(),
                                                                GetPlayerXLocation(),
                                                                GetPlayerYLocation());
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

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> UsingSkillBoardInputState::ProtectedHandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                                  int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    int x = GetPlayerXLocation();
    int y = GetPlayerYLocation();

    switch(aCode)
    {
      case UrsineEngine::KeyCode::eKEY_UP:
      case UrsineEngine::KeyCode::eKEY_W:
      {
        HoverOverTile(x,
                      y + 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_DOWN:
      case UrsineEngine::KeyCode::eKEY_S:
      {
        HoverOverTile(x,
                      y - 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_LEFT:
      case UrsineEngine::KeyCode::eKEY_A:
      {
        HoverOverTile(x - 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_RIGHT:
      case UrsineEngine::KeyCode::eKEY_D:
      {
        HoverOverTile(x + 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_ENTER:
      {
        // If the current position is valid for executing the skill,
        // execute it and revert to a default board input state.
        auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
        if(skillComponent != nullptr)
        {
          TileLocation playerLocation(GetPlayerXLocation(),
                                      GetPlayerYLocation());
          if(skillComponent->IsTileValid(*GetParent(),
                                         playerLocation))
          {
            skillComponent->Execute();
            
            newState = std::make_unique<DefaultBoardInputState>(*GetParent(),
                                                                GetPlayerXLocation(),
                                                                GetPlayerYLocation());
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

  return newState;
}

/******************************************************************************/
void UsingSkillBoardInputState::HoverOverTile(int aXPos,
                                              int aYPos)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layout != nullptr)
    {
      // If a tile exists at the given location, set that tile to hovered.
      auto newTile = layout->GetTileAtPosition(aXPos,
                                               aYPos);
      if(newTile != nullptr)
      {
        int x = GetPlayerXLocation();
        int y = GetPlayerYLocation();

        // Un-hover the tile at the current location.
        auto oldTile = layout->GetTileAtPosition(x,
                                                 y);
        auto oldTileComp = oldTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(oldTileComp != nullptr)
        {
          oldTileComp->SetHovered(false);
        }

        // Set the hovered property of the tile at the new location.
        auto newTileComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        newTileComp->SetHovered(true);

        // Finally, update the player position.
        SetPlayerXLocation(aXPos);
        SetPlayerYLocation(aYPos);
      }
    }
  }
}

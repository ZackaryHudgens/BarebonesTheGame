#include "MovingCharacterBoardInputState.hpp"

#include "BoardLayoutComponent.hpp"
#include "DefaultBoardInputState.hpp"
#include "TileBehaviorComponent.hpp"

using Barebones::MovingCharacterBoardInputState;

/******************************************************************************/
MovingCharacterBoardInputState::MovingCharacterBoardInputState(UrsineEngine::GameObject& aObject,
                                                               int aXPos,
                                                               int aYPos)
  : BoardInputState(aObject, aXPos, aYPos)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> MovingCharacterBoardInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
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
        // If the tile at the player's current position is highlighted
        // (i.e. a valid movement), move the currently selected character
        // to that tile.
        auto parent = GetParent();
        if(parent != nullptr)
        {
          auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
          if(layout != nullptr)
          {
            auto tile = layout->GetTileAtPosition(x,
                                                  y);
            if(tile != nullptr)
            {
              auto tileComp = tile->GetFirstComponentOfType<TileBehaviorComponent>();
              if(tileComp != nullptr)
              {
                // If the tile is highlighted, this is a valid movement.
                if(tileComp->IsHighlighted())
                {
                  layout->MoveSelectedCharacter(x,
                                                y);

                  // Deselect the character.
                  auto character = layout->GetCharacterAtPosition(x,
                                                                  y);
                  auto charComp = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
                  if(charComp != nullptr)
                  {
                    charComp->SetSelected(false);
                  }

                  // Finally, swap back to the default state.
                  newState = std::make_unique<DefaultBoardInputState>(*parent,
                                                                      x,
                                                                      y);
                }
              }
            }
          }
        }
        break;
      }
      case UrsineEngine::KeyCode::eKEY_ESCAPE:
      {
        // Deselect the character and revert to the default state.
        auto parent = GetParent();
        if(parent != nullptr)
        {
          auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
          if(layout != nullptr)
          {
            auto character = layout->GetSelectedCharacter();
            if(character != nullptr)
            {
              auto charComp = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
              if(charComp != nullptr)
              {
                charComp->SetSelected(false);
              }
            }
          }

          newState = std::make_unique<DefaultBoardInputState>(*parent,
                                                              x,
                                                              y);
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
void MovingCharacterBoardInputState::HoverOverTile(int aXPos,
                                           int aYPos)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layout != nullptr)
    {
      // Only allow the player to hover over valid movement tiles. If a tile
      // exists at the given location and it's highlighted, set it to hovered.
      auto newTile = layout->GetTileAtPosition(aXPos,
                                               aYPos);
      if(newTile != nullptr)
      {
        auto newTileComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(newTileComp != nullptr)
        {
          if(newTileComp->IsHighlighted())
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
  }
}

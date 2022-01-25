#include "DefaultBoardInputState.hpp"

#include "BoardInputComponent.hpp"
#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

#include <iostream>

using Barebones::DefaultBoardInputState;

/******************************************************************************/
DefaultBoardInputState::DefaultBoardInputState(UrsineEngine::GameObject& aObject)
  : BoardInputState(aObject)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                     int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    int x = GetPlayerXLocation();
    int y = GetPlayerYLocation();

    std::cout << "currently at " << x << " " << y << std::endl;

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
        // If there is a character at the player's current position,
        // that character is now selected (or deselected if it's
        // already selected).
        auto parent = GetParent();
        if(parent != nullptr)
        {
          auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
          if(layout != nullptr)
          {
            auto character = layout->GetCharacterAtPosition(x,
                                                            y);
            if(character != nullptr)
            {
              auto charComp = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
              if(charComp != nullptr)
              {
                // Deselect the previously selected character.
                auto selectedCharacter = layout->GetSelectedCharacter();
                if(selectedCharacter != nullptr)
                {
                  auto selectedCharacterComp = selectedCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
                  if(selectedCharacterComp != nullptr)
                  {
                    selectedCharacterComp->SetSelected(false);
                  }
                }

                // If the previously selected character and the character
                // at the player's position are the same one, don't reselect it.
                if(selectedCharacter != character)
                {
                  charComp->SetSelected(true);
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

  return newState;
}

/******************************************************************************/
void DefaultBoardInputState::HoverOverTile(int aXPos,
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

        std::cout << "moving to " << aXPos << " " << aYPos << std::endl;

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

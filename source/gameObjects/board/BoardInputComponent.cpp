#include "BoardInputComponent.hpp"

#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

using Barebones::BoardInputComponent;

/******************************************************************************/
BoardInputComponent::BoardInputComponent()
  : Component()
  , mPlayerXLocation(0)
  , mPlayerYLocation(0)
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
  });
}

/******************************************************************************/
void BoardInputComponent::Load()
{
  // Set the hovered property of the tile at the player's
  // initial position.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layout != nullptr)
    {
      auto tile = layout->GetTileAtPosition(mPlayerXLocation,
                                            mPlayerYLocation);
      if(tile != nullptr)
      {
        auto tileComp = tile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileComp != nullptr)
        {
          tileComp->SetHovered(true);
        }
      }
    }
  }
}

/******************************************************************************/
void BoardInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                           int aMods)
{
  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_UP:
    case UrsineEngine::KeyCode::eKEY_W:
    {
      HoverOverTile(mPlayerXLocation,
                    mPlayerYLocation + 1);
      break;
    }
    case UrsineEngine::KeyCode::eKEY_DOWN:
    case UrsineEngine::KeyCode::eKEY_S:
    {
      HoverOverTile(mPlayerXLocation,
                    mPlayerYLocation - 1);
      break;
    }
    case UrsineEngine::KeyCode::eKEY_LEFT:
    case UrsineEngine::KeyCode::eKEY_A:
    {
      HoverOverTile(mPlayerXLocation - 1,
                    mPlayerYLocation);
      break;
    }
    case UrsineEngine::KeyCode::eKEY_RIGHT:
    case UrsineEngine::KeyCode::eKEY_D:
    {
      HoverOverTile(mPlayerXLocation + 1,
                    mPlayerYLocation);
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
          auto character = layout->GetCharacterAtPosition(mPlayerXLocation,
                                                          mPlayerYLocation);
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

/******************************************************************************/
void BoardInputComponent::HoverOverTile(int aXPos,
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
        // Un-hover the tile at the current location.
        auto oldTile = layout->GetTileAtPosition(mPlayerXLocation,
                                                 mPlayerYLocation);
        auto oldTileComp = oldTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(oldTileComp != nullptr)
        {
          oldTileComp->SetHovered(false);
        }

        // Set the hovered property of the tile at the new location.
        auto newTileComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        newTileComp->SetHovered(true);

        // Finally, update the player position.
        mPlayerXLocation = aXPos;
        mPlayerYLocation = aYPos;
      }
    }
  }
}

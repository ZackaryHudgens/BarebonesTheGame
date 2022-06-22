#include "HumanPlayerPlacingCharacterInputState.hpp"

#include <sstream>

#include <Environment.hpp>

#include "PlayerBehaviorComponent.hpp"
#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"

#include "MenuFactory.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerPlacingCharacterInputState;

/******************************************************************************/
HumanPlayerPlacingCharacterInputState::HumanPlayerPlacingCharacterInputState(UrsineEngine::GameObject& aPlayer,
                                                                             const CharacterType& aType,
                                                                             bool aRemove)
  : HumanPlayerInputState(aPlayer)
  , mType(aType)
  , mRemovalRequired(aRemove)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerPlacingCharacterInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                          int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  auto player = GetPlayer();
  auto board = GetBoard();
  if(player != nullptr &&
     board != nullptr)
  {
    auto playerBehaviorComponent = player->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(playerBehaviorComponent != nullptr &&
       boardLayoutComponent != nullptr)
    {
      auto currentLocation = playerBehaviorComponent->GetLocation();
      switch(aCode)
      {
        // For player movement, first check if a tile exists at the new location
        // on the board. If it does, update the player's location.
        case UrsineEngine::KeyCode::eKEY_UP:
        case UrsineEngine::KeyCode::eKEY_W:
        {
          TileLocation newLocation = currentLocation;
          newLocation.second += 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          TileLocation newLocation = currentLocation;
          newLocation.second -= 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          TileLocation newLocation = currentLocation;
          newLocation.first -= 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          TileLocation newLocation = currentLocation;
          newLocation.first += 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_Z:
        {
          CameraZoomChangeRequested.Notify(2.5);
          break;
        }
        case UrsineEngine::KeyCode::eKEY_X:
        {
          CameraZoomChangeRequested.Notify(0.0);
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ESCAPE:
        {
          // Create a pause menu and add it to the scene.
          auto pauseMenu = MenuFactory::CreateMenu(MenuType::ePAUSE, "pauseMenu");
          auto scene = env.GetCurrentScene();
          if(scene != nullptr)
          {
            scene->AddObject(std::move(pauseMenu));
          }
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          auto character = boardLayoutComponent->GetCharacterAtLocation(currentLocation);

          // If there isn't a character at this location, and we aren't
          // requiring a removal first, create a new character of the given type
          // and place it here.
          if(character == nullptr &&
             !mRemovalRequired)
          {
            std::stringstream nameStream;
            nameStream << "character_" << currentLocation.first << "_" << currentLocation.second;
            auto newCharacter = CharacterFactory::CreateCharacter(mType, nameStream.str());
            boardLayoutComponent->AddCharacterAtLocation(std::move(newCharacter), currentLocation);

            // Then, return to the default state.
            newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
            newState->SetBoard(*board);
          }

          // If there is a character at this location, and a removal is
          // required, first check if the character is controlled by the
          // player. If it is, remove it and set mRemovalRequired to false.
          if(character != nullptr &&
             mRemovalRequired)
          {
            auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
            if(characterBehaviorComponent != nullptr)
            {
              if(characterBehaviorComponent->GetSide() == playerBehaviorComponent->GetSide())
              {
                boardLayoutComponent->RemoveCharacterAtLocation(currentLocation);
                mRemovalRequired = false;
              }
            }
          }
          break;
        }
        case UrsineEngine::KeyCode::eKEY_Q:
        {
          // Return to the default state.
          newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
          newState->SetBoard(*board);
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
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerPlacingCharacterInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                                           int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_ESCAPE:
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

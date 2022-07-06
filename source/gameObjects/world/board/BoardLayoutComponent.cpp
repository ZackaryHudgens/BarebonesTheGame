#include "BoardLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <CoreSignals.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "BoardInitialState.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "TileBehaviorComponent.hpp"

using Barebones::BoardLayoutComponent;

/******************************************************************************/
BoardLayoutComponent::BoardLayoutComponent()
  : Component()
  , mMovingCharacter(nullptr)
  , mWaitingForMovingCharacter(false)
  , mFocusedTileLocation(0, 0)
  , mTileSpacing(0.2)
  , mColumns(7)
  , mRows(7)
{
  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  PlayerTurnEnded.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnEnded(aPlayer);
  });

  SkillSelected.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillSelected(aSkill);
  });

  SkillExecuted.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillExecuted(aSkill);
  });

  SkillCancelled.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillCancelled(aSkill);
  });

  CharacterFinishedMoving.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMoving(aCharacter);
  });

  CharacterDied.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterDied(aCharacter);
  });

  CameraFinishedInitialSequence.Connect(*this, [this](UrsineEngine::GameObject& aCamera)
  {
    this->HandleCameraFinishedInitialSequence(aCamera);
  });

  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
}

/******************************************************************************/
void BoardLayoutComponent::Initialize()
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
      std::vector<UrsineEngine::GameObject*> row;
      std::vector<UrsineEngine::GameObject*> characters;

      for(int y = 0; y < mRows; ++y)
      {
        ss << "tile_" << x << "_" << y;
        auto tile = TileFactory::CreateTile(TileType::eDEFAULT, ss.str());

        // The z-position in world space corresponds to the y-position
        // on the 2D grid. It's made negative here so that (0, 0) on
        // the grid is in the bottom left.
        tile->SetPosition(glm::vec3((double)x + (mTileSpacing * x),
                                     0.0,
                                     -1 * (double)y - (mTileSpacing * y)));
        parent->AddChild(std::move(tile));
        row.emplace_back(parent->GetChild(ss.str()));
        characters.emplace_back(nullptr);
        ss.str("");
      }

      mTiles.emplace_back(row);
      mCharacters.emplace_back(characters);
    }

    // Begin in the initial state.
    mState = std::make_unique<BoardInitialState>(*parent);
  }
}

/******************************************************************************/
void BoardLayoutComponent::Update(double aTime)
{
  if(!mWaitingForMovingCharacter &&
     mMovingCharacter != nullptr &&
     !mFollowedPath.empty())
  {
    auto characterLocation = GetLocationOfCharacter(mMovingCharacter->GetName());
    auto tileLocation = mFollowedPath.front();
    mFollowedPath.erase(mFollowedPath.begin());

    MoveCharacter(characterLocation, tileLocation);

    mWaitingForMovingCharacter = true;
  }
}

/******************************************************************************/
bool BoardLayoutComponent::AddTileAtLocation(const TileType& aTileType,
                                             const TileLocation& aLocation)
{
  bool success = false;

  auto tile = GetTileAtLocation(aLocation);
  if(tile == nullptr)
  {
    if(aLocation.first >= 0 &&
       aLocation.first < mColumns &&
       aLocation.second >= 0 &&
       aLocation.second < mRows)
    {
      auto parent = GetParent();
      if(parent != nullptr)
      {
        // Create the new tile and add it as a child GameObject.
        std::stringstream newTileName;
        newTileName << "tile_" << aLocation.first << "_" << aLocation.second;

        // If a child GameObject with this name already exists, but no tile
        // was found at this location in the tile map, then it's likely that
        // this function was called in the same frame as RemoveTileAtLocation()
        // and the tile hasn't been removed from the parent GameObject yet.
        // If that's the case, add "_new" to the name.
        if(parent->GetChild(newTileName.str()) != nullptr)
        {
          newTileName << "_new";
        }

        // Position the tile in world space. The z-position in world space
        // corresponds to the y-position on the 2D grid. It's made negative here
        // so that (0, 0) on the grid is in the bottom left.
        auto newTile = TileFactory::CreateTile(aTileType, newTileName.str());
        newTile->SetPosition(glm::vec3((double)aLocation.first + (mTileSpacing * aLocation.first),
                                        0.0,
                                        -1 * (double)aLocation.second - (mTileSpacing * aLocation.second)));

        // If there is a character at the tile's location, let the tile know.
        auto character = GetCharacterAtLocation(aLocation);
        if(character != nullptr)
        {
          auto tileBehaviorComponent = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
          if(tileBehaviorComponent != nullptr)
          {
            tileBehaviorComponent->HandleCharacterEntered(*character);
          }
        }

        parent->AddChild(std::move(newTile));
        mTiles.at(aLocation.first).at(aLocation.second) = parent->GetChildren().back();
      }
    }
  }

  return success;
}

/******************************************************************************/
void BoardLayoutComponent::RemoveTileAtLocation(const TileLocation& aLocation)
{
  auto tile = GetTileAtLocation(aLocation);
  if(tile != nullptr)
  {
    // If there is a character at the tile's location, let the tile know.
    auto character = GetCharacterAtLocation(aLocation);
    if(character != nullptr)
    {
      auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
      if(tileBehaviorComponent != nullptr)
      {
        tileBehaviorComponent->HandleCharacterExited(*character);
      }
    }

    tile->ScheduleForDeletion();
    mTiles.at(aLocation.first).at(aLocation.second) = nullptr;
  }
}

/******************************************************************************/
bool BoardLayoutComponent::AddCharacterAtLocation(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                                  const TileLocation& aLocation)
{
  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto tile = GetTileAtLocation(aLocation);
    if(tile != nullptr)
    {
      auto tileMeshComponent = tile->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      auto characterMeshComponent = aObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(tileMeshComponent != nullptr &&
         characterMeshComponent != nullptr)
      {
        // Set the character's position to be on top of the tile.
        auto newPos = tile->GetPosition();
        newPos.y += tileMeshComponent->GetHeight() / 2.0;
        newPos.y += characterMeshComponent->GetHeight() / 2.0;
        aObject->SetPosition(newPos);
      }

      // Add the character as a child object of the board.
      parent->AddChild(std::move(aObject));

      // Update the character map.
      mCharacters[aLocation.first][aLocation.second] = parent->GetChildren().back();
      success = true;
    }
  }

  return success;
}

/******************************************************************************/
void BoardLayoutComponent::RemoveCharacterAtLocation(const TileLocation& aLocation)
{
  if(aLocation.first < mCharacters.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mCharacters[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      auto obj = mCharacters[aLocation.first][aLocation.second];
      if(obj != nullptr)
      {
        // The character will be deleted at the end of the current update.
        obj->ScheduleForDeletion();
        mCharacters[aLocation.first][aLocation.second] = nullptr;
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::SetFocusedTileLocation(const TileLocation& aLocation)
{
  auto newTile = GetTileAtLocation(aLocation);
  if(newTile != nullptr)
  {
    mFocusedTileLocation = aLocation;

    auto parent = GetParent();
    if(parent != nullptr)
    {
      BoardFocusedTileChanged.Notify(*parent);
    }
  }
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetTileAtLocation(const TileLocation& aLocation)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aLocation.first < mTiles.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mTiles[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      obj = mTiles[aLocation.first][aLocation.second];
    }
  }

  return obj;
}

/******************************************************************************/
UrsineEngine::GameObject* BoardLayoutComponent::GetCharacterAtLocation(const TileLocation& aLocation)
{
  UrsineEngine::GameObject* obj = nullptr;

  if(aLocation.first < mCharacters.size() &&
     aLocation.first >= 0)
  {
    if(aLocation.second < mCharacters[aLocation.first].size() &&
       aLocation.second >= 0)
    {
      obj = mCharacters[aLocation.first][aLocation.second];
    }
  }

  return obj;
}

/******************************************************************************/
Barebones::TileLocation BoardLayoutComponent::GetLocationOfCharacter(const std::string& aName)
{
  TileLocation tile(-1, -1);

  int x = 0;
  int y = 0;
  bool found = false;
  for(const auto& column : mCharacters)
  {
    y = 0;
    for(const auto& character : column)
    {
      if(character != nullptr)
      {
        if(character->GetName() == aName)
        {
          found = true;
          tile.first = x;
          tile.second = y;

          break;
        }
      }

      ++y;
    }

    if(found)
    {
      break;
    }
    else
    {
      ++x;
    }
  }

  return tile;
}

/******************************************************************************/
std::vector<UrsineEngine::GameObject*> BoardLayoutComponent::GetCharactersOnSide(const Side& aSide)
{
  std::vector<UrsineEngine::GameObject*> characters;

  for(auto& column : mCharacters)
  {
    for(auto& character : column)
    {
      if(character != nullptr)
      {
        auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          if(characterBehaviorComponent->GetSide() == aSide)
          {
            characters.emplace_back(character);
          }
        }
      }
    }
  }

  return characters;
}

/******************************************************************************/
std::vector<UrsineEngine::GameObject*> BoardLayoutComponent::GetCharactersOfType(const Type& aType)
{
  std::vector<UrsineEngine::GameObject*> characters;

  for(auto& column : mCharacters)
  {
    for(auto& character : column)
    {
      if(character != nullptr)
      {
        auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr)
        {
          if(characterBehaviorComponent->GetType() == aType)
          {
            characters.emplace_back(character);
          }
        }
      }
    }
  }

  return characters;
}

/******************************************************************************/
void BoardLayoutComponent::MoveCharacterAlongPath(const TileLocation& aCharacterLocation,
                                                  const TileList& aPath)
{
  auto character = GetCharacterAtLocation(aCharacterLocation);
  if(character != nullptr)
  {
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      if(!aPath.empty())
      {
        mMovingCharacter = character;
        mFollowedPath = aPath;

        CharacterStartedMovingAlongPath.Notify(*characterBehaviorComponent);
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::MoveCharacter(const TileLocation& aCurrentLocation,
                                         const TileLocation& aTargetLocation)
{
  if(mMovingCharacter != nullptr)
  {
    auto tile = GetTileAtLocation(aTargetLocation);
    if(tile != nullptr)
    {
      auto tileMeshComponent = tile->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      auto characterBehaviorComponent = mMovingCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
      auto characterMeshComponent = mMovingCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(tileMeshComponent != nullptr &&
         characterBehaviorComponent != nullptr &&
         characterMeshComponent != nullptr)
      {
        // Move the character in world space.
        auto position = tile->GetPosition();
        position.y += tileMeshComponent->GetHeight() / 2.0;
        position.y += characterMeshComponent->GetHeight() / 2.0;
        characterBehaviorComponent->MoveToPosition(position, 0.3);

        // Update the character map.
        if(aCurrentLocation != aTargetLocation)
        {
          mCharacters[aTargetLocation.first][aTargetLocation.second] = mMovingCharacter;
          mCharacters[aCurrentLocation.first][aCurrentLocation.second] = nullptr;
        }
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  // For each character controlled by this player, let the tile they're on
  // know that a new turn has begun.
  auto characters = GetCharactersOnSide(aPlayer.GetSide());
  for(auto& character : characters)
  {
    auto characterLocation = GetLocationOfCharacter(character->GetName());
    auto tile = GetTileAtLocation(characterLocation);
    if(tile != nullptr)
    {
      auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
      if(tileBehaviorComponent != nullptr)
      {
        tileBehaviorComponent->HandleTurnBegan(*character);
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  // For each character controlled by this player, let the tile they're on
  // know that their turn has ended.
  auto characters = GetCharactersOnSide(aPlayer.GetSide());
  for(auto& character : characters)
  {
    auto characterLocation = GetLocationOfCharacter(character->GetName());
    auto tile = GetTileAtLocation(characterLocation);
    if(tile != nullptr)
    {
      auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
      if(tileBehaviorComponent != nullptr)
      {
        tileBehaviorComponent->HandleTurnEnded(*character);
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillSelected(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillSelected(aSkill);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillExecuted(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillExecuted(aSkill);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleSkillCancelled(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillCancelled(aSkill);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter)
{
  // When a character finishes moving, tell the tile at their new location.
  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    auto characterLocation = GetLocationOfCharacter(characterObject->GetName());
    auto tile = GetTileAtLocation(characterLocation);
    if(tile != nullptr)
    {
      auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
      if(tileBehaviorComponent != nullptr)
      {
        tileBehaviorComponent->HandleCharacterEntered(*characterObject);
      }
    }

    if(characterObject == mMovingCharacter)
    {
      // We are no longer waiting for this character to finish moving.
      mWaitingForMovingCharacter = false;

      // If the followed path is empty, then we have finished moving the
      // character.
      if(mFollowedPath.empty())
      {
        mMovingCharacter = nullptr;
        CharacterFinishedMovingAlongPath.Notify(aCharacter);
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleCharacterDied(CharacterBehaviorComponent& aCharacter)
{
  // When a character dies, don't remove it right away; just set
  // the character at their location to nullptr.
  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    auto location = GetLocationOfCharacter(characterObject->GetName());
    if(location.first >= 0 &&
       location.second < mCharacters.size())
    {
      if(location.second >= 0 &&
         location.second < mCharacters.at(location.first).size())
      {
        mCharacters.at(location.first).at(location.second) = nullptr;
      }
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleCameraFinishedInitialSequence(UrsineEngine::GameObject& aCamera)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleCameraFinishedInitialSequence();
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void BoardLayoutComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject)
{
  // When an object is about to be deleted, check if it had a
  // CharacterBehaviorComponent. If it did, check if there are any
  // characters left that are on the same side. If not, notify the
  // AllCharactersOfSideDefeated signal.
  auto characterBehaviorComponent = aObject->GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    auto characterSide = characterBehaviorComponent->GetSide();
    auto charactersOnSide = GetCharactersOnSide(characterSide);
    if(charactersOnSide.empty())
    {
      auto parent = GetParent();
      if(parent != nullptr)
      {
        AllCharactersOfSideDefeated.Notify(*parent, characterSide);
      }
    }
  }
}

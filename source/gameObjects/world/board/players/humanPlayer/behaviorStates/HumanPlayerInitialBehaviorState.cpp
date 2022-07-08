#include "HumanPlayerInitialBehaviorState.hpp"

#include <algorithm>
#include <sstream>

#include "HumanPlayerDefaultBehaviorState.hpp"

#include "PlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerInitialBehaviorState;

/******************************************************************************/
HumanPlayerInitialBehaviorState::HumanPlayerInitialBehaviorState(UrsineEngine::GameObject& aPlayer)
  : HumanPlayerBehaviorState(aPlayer)
{
  mSkeletonsToSpawn.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonsToSpawn.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonsToSpawn.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonsToSpawn.emplace_back(CharacterType::eBONE_THROWER);
  mSkeletonsToSpawn.emplace_back(CharacterType::eBONE_THROWER);
  mSkeletonsToSpawn.emplace_back(CharacterType::eBONE_THROWER);

  BoardFinishedInitialSequence.Connect(mObserver, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFinishedInitialSequence(aBoard);
  });
}

/******************************************************************************/
void HumanPlayerInitialBehaviorState::OnExit()
{
  // Upon exiting this state, request a new enemy wave.
  auto player = GetPlayer();
  if(player != nullptr)
  {
    auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
    if(playerBehaviorComponent != nullptr)
    {
      auto board = playerBehaviorComponent->GetBoard();
      if(board != nullptr)
      {
        NewEnemyWaveRequested.Notify(*board);
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerBehaviorState> HumanPlayerInitialBehaviorState::HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<HumanPlayerBehaviorState> newState = nullptr;

  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    auto foundCharacter = std::find(mSpawningSkeletons.begin(),
                                    mSpawningSkeletons.end(),
                                    characterObject);
    if(foundCharacter != mSpawningSkeletons.end())
    {
      mSpawningSkeletons.erase(foundCharacter);

      if(mSpawningSkeletons.empty())
      {
        // Revert to the default state.
        auto player = GetPlayer();
        if(player != nullptr)
        {
          newState = std::make_unique<HumanPlayerDefaultBehaviorState>(*player);
        }
      }
    }
  }

  return newState;
}

/******************************************************************************/
void HumanPlayerInitialBehaviorState::HandleBoardFinishedInitialSequence(UrsineEngine::GameObject& aBoard)
{
  std::stringstream nameStream;

  // Create a character for each type in our inventory and add them
  // to the board.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    int row = 0;
    int index = 0;
    for(const auto& characterType : mSkeletonsToSpawn)
    {
      TileLocation location(0, row);

      nameStream << "skeleton_" << index;
      auto character = CharacterFactory::CreateCharacter(characterType, nameStream.str());
      
      boardLayoutComponent->AddCharacterAtLocation(std::move(character), location);
      mSpawningSkeletons.emplace_back(boardLayoutComponent->GetCharacterAtLocation(location));

      nameStream.str("");
      ++index;
      ++row;
    }
  }
}

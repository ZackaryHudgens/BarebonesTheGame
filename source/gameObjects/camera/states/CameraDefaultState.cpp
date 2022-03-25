#include "CameraDefaultState.hpp"

#include "CameraFollowingCharacterState.hpp"
#include "CameraFollowingPlayerState.hpp"
#include "CameraObservingBoardState.hpp"

using Barebones::CameraDefaultState;

/******************************************************************************/
CameraDefaultState::CameraDefaultState(UrsineEngine::GameObject& aCamera)
  : CameraState(aCamera)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraDefaultState::HandleBoardFollowed(UrsineEngine::GameObject& aBoard)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // Swap to the Observing Board state, if possible.
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    newState = std::make_unique<CameraObservingBoardState>(*camera,
                                                           aBoard);
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraDefaultState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the player is human, swap to the Following Player state.
  if(dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer) != nullptr)
  {
    auto camera = GetCamera();
    auto playerParent = aPlayer.GetParent();
    if(camera != nullptr &&
       playerParent != nullptr)
    {
      newState = std::make_unique<CameraFollowingPlayerState>(*camera,
                                                              *playerParent);
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraDefaultState::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // Swap to the Following Character state, if possible.
  auto camera = GetCamera();
  auto characterParent = aCharacter.GetParent();
  if(camera != nullptr &&
     characterParent != nullptr)
  {
    newState = std::make_unique<CameraFollowingCharacterState>(*camera,
                                                               *characterParent);
  }

  return newState;
}

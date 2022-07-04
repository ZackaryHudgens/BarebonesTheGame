#include "CameraDefaultState.hpp"

#include "CameraFollowingCharacterState.hpp"
#include "CameraFollowingPlayerState.hpp"

using Barebones::CameraDefaultState;

/******************************************************************************/
CameraDefaultState::CameraDefaultState(UrsineEngine::GameObject& aCamera)
  : CameraState(aCamera)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraDefaultState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // Swap to the Following Player state, if possible.
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    newState = std::make_unique<CameraFollowingPlayerState>(*camera,
                                                            aPlayer);
  }

  return std::move(newState);
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

  return std::move(newState);
}

#include "CameraFollowingCharacterState.hpp"

#include <CoreSignals.hpp>

#include "CameraBehaviorComponent.hpp"
#include "CameraDefaultState.hpp"

#include "Signals.hpp"

using Barebones::CameraFollowingCharacterState;

/******************************************************************************/
CameraFollowingCharacterState::CameraFollowingCharacterState(UrsineEngine::GameObject& aCamera,
                                                             UrsineEngine::GameObject& aCharacter)
  : CameraMovingState(aCamera)
  , mCharacter(&aCharacter)
{
  UrsineEngine::ObjectMoved.Connect(mObserver, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectMoved(aObject);
  });
}

/******************************************************************************/
void CameraFollowingCharacterState::OnEnter()
{
  SetSpeed(0.3);
  HandleObjectMoved(mCharacter);
};

/******************************************************************************/
void CameraFollowingCharacterState::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
  if(mCharacter == aObject)
  {
    auto targetPos = aObject->GetPosition();
    targetPos.y += 5.0;
    targetPos.z += 5.0;

    SetTargetPosition(targetPos);
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the character that ended its turn is the same as the character
  // being followed, revert to the default state.
  if(aCharacter.GetParent() == mCharacter)
  {
    auto camera = GetCamera();
    if(camera != nullptr)
    {
      newState = std::make_unique<CameraDefaultState>(*camera);
    }
  }

  return std::move(newState);
}

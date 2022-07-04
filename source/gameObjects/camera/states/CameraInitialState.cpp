#include "CameraInitialState.hpp"

#include "CameraPanningToBoardState.hpp"

using Barebones::CameraInitialState;

/******************************************************************************/
CameraInitialState::CameraInitialState(UrsineEngine::GameObject& aCamera)
  : CameraState(aCamera)
{
}

/******************************************************************************/
void CameraInitialState::OnEnter()
{
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    // Initialize the camera rotation and position.
    camera->SetPosition(glm::vec3(0.0, 25.0, 0.0));
    camera->SetRotation(-40.0, glm::vec3(1.0, 0.0, 0.0));
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraInitialState::HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay)
{
  std::unique_ptr<CameraState> newState = nullptr;

  auto camera = GetCamera();
  if(camera != nullptr)
  {
    newState = std::make_unique<CameraPanningToBoardState>(*camera);
  }

  return std::move(newState);
}

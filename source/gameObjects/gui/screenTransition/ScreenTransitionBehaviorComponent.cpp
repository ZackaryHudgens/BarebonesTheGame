#include "ScreenTransitionBehaviorComponent.hpp"

#include <Environment.hpp>

#include "ScreenTransitionFadingInState.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::ScreenTransitionBehaviorComponent;

/******************************************************************************/
ScreenTransitionBehaviorComponent::ScreenTransitionBehaviorComponent()
  : mState(nullptr)
{
  ScreenTransitionRequested.Connect(*this, [this](const SceneType& aSceneType)
  {
    this->HandleScreenTransitionRequested(aSceneType);
  });
}

/******************************************************************************/
void ScreenTransitionBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a mesh that covers the entire overlay.
    parent->AddComponent(std::make_unique<UrsineEngine::MeshComponent>());
    auto mesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();

    mesh->AddIndex(0);
    mesh->AddIndex(1);
    mesh->AddIndex(3);
    mesh->AddIndex(3);
    mesh->AddIndex(1);
    mesh->AddIndex(2);

    auto width = env.GetGraphicsOptions().mOverlayWidth;
    auto height = env.GetGraphicsOptions().mOverlayHeight;

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
    vertex.mColor = BACKGROUND_COLOR;
    mesh->AddVertex(vertex);

    vertex.mPosition = glm::vec3(width, 0.0, 0.0);
    mesh->AddVertex(vertex);

    vertex.mPosition = glm::vec3(width, height, 0.0);
    mesh->AddVertex(vertex);

    vertex.mPosition = glm::vec3(0.0, height, 0.0);
    mesh->AddVertex(vertex);

    std::string vertexFile = "resources/shaders/UntexturedMeshWithFadeShader.vert";
    std::string fragmentFile = "resources/shaders/UntexturedMeshWithFadeShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
    mesh->AddShader("defaultShader", defaultShader);
    mesh->SetCurrentShader("defaultShader");

    mesh->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    mesh->SetHasTransparency(true);

    parent->SetPosition(glm::vec3(0.0, 0.0, 0.9));

    // Finally, begin in the FadingIn state.
    mState = std::make_unique<ScreenTransitionFadingInState>(*parent);
    mState->OnEnter();
  }
}

/******************************************************************************/
void ScreenTransitionBehaviorComponent::Update(double aTime)
{
  if(mState != nullptr)
  {
    auto newState = mState->Update(aTime);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void ScreenTransitionBehaviorComponent::HandleScreenTransitionRequested(const SceneType& aType)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleScreenTransitionRequested(aType);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

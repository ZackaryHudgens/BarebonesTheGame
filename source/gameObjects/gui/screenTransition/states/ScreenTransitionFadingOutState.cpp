#include "ScreenTransitionFadingOutState.hpp"

#include <Environment.hpp>
#include <MeshComponent.hpp>

#include "ScreenTransitionDefaultState.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::ScreenTransitionFadingOutState;

/******************************************************************************/
ScreenTransitionFadingOutState::ScreenTransitionFadingOutState(UrsineEngine::GameObject& aParent,
                                                               const SceneType& aSceneType)
  : ScreenTransitionState(aParent)
  , mSpeed(0.05)
  , mFadeValue(0.0)
  , mSceneToLoad(aSceneType)
{
}

/******************************************************************************/
void ScreenTransitionFadingOutState::OnEnter()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto mesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        shader->SetFloat("fadeValue", 0.0);
        shader->SetVec4("fadeColor", glm::vec4(LIGHT_COLOR, 1.0));

        mFadeValue = 0.0;
      }
    }
  }
}

/******************************************************************************/
void ScreenTransitionFadingOutState::OnExit()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    ScreenTransitionFinished.Notify(*parent);

    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      env.LoadScene(SceneFactory::CreateScene(mSceneToLoad));
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::ScreenTransitionState> ScreenTransitionFadingOutState::Update(double aTime)
{
  std::unique_ptr<ScreenTransitionState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto mesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        mFadeValue += mSpeed;

        shader->Activate();
        if(mFadeValue >= 1.0)
        {
          shader->SetFloat("fadeValue", 1.0);
          newState = std::make_unique<ScreenTransitionDefaultState>(*parent);
        }
        else
        {
          shader->SetFloat("fadeValue", mFadeValue);
        }
      }
    }
  }

  return newState;
}

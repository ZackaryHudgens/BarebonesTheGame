#include "CharacterSpawningState.hpp"

#include <MeshComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "CharacterDefaultState.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::CharacterSpawningState;

/******************************************************************************/
CharacterSpawningState::CharacterSpawningState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
  , mFadeValue(1.0)
  , mFadeSpeed(0.1)
{
}

/******************************************************************************/
void CharacterSpawningState::OnEnter()
{
  // Upon entering this state, set the fade color and initialize the fade value
  // so the character begins fading in during Update().
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto mesh = character->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        shader->SetFloat("fadeValue", mFadeValue);
        shader->SetVec4("fadeColor", glm::vec4(BACKGROUND_COLOR, 1.0));
      }
    }
  }
}

/******************************************************************************/
void CharacterSpawningState::OnExit()
{
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      CharacterFinishedSpawning.Notify(*characterBehaviorComponent);
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterSpawningState::Update(double aTime)
{
  std::unique_ptr<CharacterState> newState = nullptr;

  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto mesh = character->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        mFadeValue = glm::mix(mFadeValue, 0.0, mFadeSpeed);

        shader->Activate();
        shader->SetFloat("fadeValue", mFadeValue);

        if(mFadeValue <= 0.0)
        {
          shader->SetFloat("fadeValue", 0.0);

          // Revert to the default state.
          newState = std::make_unique<CharacterDefaultState>(*character);
        }
      }
    }
  }

  return newState;
}

#include "CharacterDyingState.hpp"

#include <MeshComponent.hpp>

#include "CharacterDefaultState.hpp"

#include "Colors.hpp"

using Barebones::CharacterDyingState;

/******************************************************************************/
CharacterDyingState::CharacterDyingState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
  , mFadeValue(0.0)
  , mFadeSpeed(0.1)
{
}

/******************************************************************************/
void CharacterDyingState::OnEnter()
{
  // Upon entering this state, set the fade color and initialize the fade value
  // so the character begins fading out during Update().
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
std::unique_ptr<Barebones::CharacterState> CharacterDyingState::Update(double aTime)
{
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto mesh = character->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        mFadeValue = glm::mix(mFadeValue, 1.0, mFadeSpeed);

        shader->Activate();
        shader->SetFloat("fadeValue", mFadeValue);

        if(mFadeValue >= 1.0)
        {
          shader->SetFloat("fadeValue", 1.0);

          // Delete the parent character now that it has finished
          // fading out.
          character->ScheduleForDeletion();
        }
      }
    }
  }

  return nullptr;
}

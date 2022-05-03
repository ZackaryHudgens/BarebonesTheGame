#include "CharacterDyingState.hpp"

#include <MeshComponent.hpp>

#include "CharacterDefaultState.hpp"

using Barebones::CharacterDyingState;

/******************************************************************************/
CharacterDyingState::CharacterDyingState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
  , mFadeValue(0.0)
  , mFadeSpeed(0.1)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterDyingState::Update(double aTime)
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
        mFadeValue = glm::mix(mFadeValue, 1.0, mFadeSpeed);

        shader->Activate();
        shader->SetFloat("fadeValue", mFadeValue);

        if(mFadeValue >= 0.95)
        {
          // This character has finished fading to black, so
          // schedule it for deletion.
          character->ScheduleForDeletion();

          // Revert to the default state.
          newState = std::make_unique<CharacterDefaultState>(*character);
        }
      }
    }
  }

  return newState;
}

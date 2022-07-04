#include "CharacterDefaultState.hpp"

#include "CharacterDyingState.hpp"
#include "CharacterMovingState.hpp"
#include "CharacterShakingState.hpp"

using Barebones::CharacterDefaultState;

/******************************************************************************/
CharacterDefaultState::CharacterDefaultState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterDefaultState::HandleMovementRequested(const glm::vec3& aPosition,
                                                                                          double aSpeed)
{
  std::unique_ptr<CharacterState> newState = nullptr;

  // Transition to the moving state.
  auto character = GetCharacter();
  if(character != nullptr)
  {
    newState = std::make_unique<CharacterMovingState>(*character, aPosition, aSpeed);
  }
  
  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterDefaultState::HandleDamageReceived()
{
  std::unique_ptr<CharacterState> newState = nullptr;

  // Transition to the shaking state.
  auto character = GetCharacter();
  if(character != nullptr)
  {
    newState = std::make_unique<CharacterShakingState>(*character);
  }
  
  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterDefaultState::HandleCharacterDied()
{
  std::unique_ptr<CharacterState> newState = nullptr;

  // Transition to the dying state.
  auto character = GetCharacter();
  if(character != nullptr)
  {
    newState = std::make_unique<CharacterDyingState>(*character);
  }
  
  return newState;
}

#include "CharacterShakingState.hpp"

using Barebones::CharacterShakingState;

/******************************************************************************/
CharacterShakingState::CharacterShakingState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterShakingState::Update(double aTime)
{
  return nullptr;
}

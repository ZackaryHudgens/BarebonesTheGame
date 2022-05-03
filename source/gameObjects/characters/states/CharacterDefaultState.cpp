#include "CharacterDefaultState.hpp"

using Barebones::CharacterDefaultState;

/******************************************************************************/
CharacterDefaultState::CharacterDefaultState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterDefaultState::Update(double aTime)
{
  return nullptr;
}

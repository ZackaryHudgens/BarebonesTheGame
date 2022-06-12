#include "BoardWaveManagerComponent.hpp"

using Barebones::BoardWaveManagerComponent;

/******************************************************************************/
BoardWaveManagerComponent::BoardWaveManagerComponent()
  : Component()
  , mWaveNumber(0)
{
}

/******************************************************************************/
void BoardWaveManagerComponent::GenerateEncounter(UrsineEngine::GameObject& aBoard)
{
}

/******************************************************************************/
void BoardWaveManagerComponent::HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                                                  const Side& aSide)
{
  switch(aSide)
  {
    case Side::eENEMY:
    {
      GenerateEncounter(aBoard);
      break;
    }
    default:
    {
      break;
    }
  }
}

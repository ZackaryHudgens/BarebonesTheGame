#include "EnemyBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::EnemyBehaviorComponent;

/******************************************************************************/
EnemyBehaviorComponent::EnemyBehaviorComponent()
  : CharacterBehaviorComponent()
{
}

/******************************************************************************/
void EnemyBehaviorComponent::EndTurn()
{
  CharacterTurnEnded.Notify(*this);
}

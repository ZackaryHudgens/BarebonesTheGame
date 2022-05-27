#include "EnemyBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

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

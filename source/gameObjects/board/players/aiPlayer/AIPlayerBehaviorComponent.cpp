#include "AIPlayerBehaviorComponent.hpp"

using Barebones::AIPlayerBehaviorComponent;

/******************************************************************************/
AIPlayerBehaviorComponent::AIPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
{
  SetName("Enemy");
}

/******************************************************************************/
void AIPlayerBehaviorComponent::ProtectedTakeTurn()
{
  // For now, just end the turn immediately.
  EndTurn();
}

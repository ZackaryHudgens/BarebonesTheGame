#include "AIPlayerBehaviorComponent.hpp"

using Barebones::AIPlayerBehaviorComponent;

/******************************************************************************/
AIPlayerBehaviorComponent::AIPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mWaitingForCharacter(false)
{
  SetName("Enemy");
}

/******************************************************************************/
void AIPlayerBehaviorComponent::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  EndTurn();
  // First, gather all the current enemies on the board.
}

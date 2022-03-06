#include "BasicHumanBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::BasicHumanBehaviorComponent;

/******************************************************************************/
BasicHumanBehaviorComponent::BasicHumanBehaviorComponent()
  : EnemyBehaviorComponent()
{
  SetMaximumHealth(5);
  SetCurrentHealth(5);
}

/******************************************************************************/
void BasicHumanBehaviorComponent::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  // For now, just move the character to the left one space if possible.
  auto parent = GetParent();
  auto boardLayout = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(parent != nullptr &&
     boardLayout != nullptr)
  {
    auto location = boardLayout->GetLocationOfCharacter(parent->GetName());

    // Check if there is a character to the left of this one. If there isn't,
    // move to that space. If there is, do nothing.
    TileLocation newLocation = location;
    newLocation.first -= 1;
    auto character = boardLayout->GetCharacterAtLocation(newLocation);
    if(character == nullptr)
    {
      boardLayout->MoveCharacter(location,
                                 newLocation);
    }
  }
}

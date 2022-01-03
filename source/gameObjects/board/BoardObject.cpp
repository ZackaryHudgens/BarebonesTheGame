#include "BoardObject.hpp"

#include "BoardBehaviorComponent.hpp"

using Barebones::BoardObject;

/******************************************************************************/
BoardObject::BoardObject(const std::string& aName)
  : GameObject(aName)
  , mRows(5)
  , mColumns(5)
{
  // Add the behavior component.
  AddComponent(std::make_unique<BoardBehaviorComponent>());
}

#include "BoardFactory.hpp"

#include "BoardBehaviorComponent.hpp"
#include "BoardInputComponent.hpp"
#include "BoardLayoutComponent.hpp"

using Barebones::BoardFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> BoardFactory::CreateBoard(const std::string& aName)
{
  auto board = std::make_unique<UrsineEngine::GameObject>(aName);
  board->AddComponent(std::make_unique<BoardBehaviorComponent>());
  board->AddComponent(std::make_unique<BoardInputComponent>());
  board->AddComponent(std::make_unique<BoardLayoutComponent>());
  return board;
}

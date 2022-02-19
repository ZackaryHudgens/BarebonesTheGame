#include "BoardFactory.hpp"

#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

using Barebones::BoardFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> BoardFactory::CreateBoard(const std::string& aName)
{
  auto board = std::make_unique<UrsineEngine::GameObject>(aName);
  board->AddComponent(std::make_unique<BoardLayoutComponent>());
  board->AddComponent(std::make_unique<BoardTurnManagerComponent>());
  return board;
}

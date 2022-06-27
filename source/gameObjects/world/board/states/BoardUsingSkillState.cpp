#include "BoardUsingSkillState.hpp"

#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

#include "Colors.hpp"

using Barebones::BoardUsingSkillState;

/******************************************************************************/
BoardUsingSkillState::BoardUsingSkillState(UrsineEngine::GameObject& aBoard,
                                           Skill& aSkill)
  : BoardState(aBoard)
  , mSkill(&aSkill)
{
}

/******************************************************************************/
void BoardUsingSkillState::OnEnter()
{
  auto board = GetBoard();
  if(board != nullptr)
  {
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
    }
  }
}

/******************************************************************************/
void BoardUsingSkillState::OnExit()
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardUsingSkillState::HandleSkillExecuted(Skill& aSkill)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardUsingSkillState::HandleSkillCancelled(Skill& aSkill)
{
  return nullptr;
}

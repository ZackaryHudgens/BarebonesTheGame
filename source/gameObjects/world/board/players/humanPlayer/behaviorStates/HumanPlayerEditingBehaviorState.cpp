#include "HumanPlayerEditingBehaviorState.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerDefaultBehaviorState.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerEditingBehaviorState;

/******************************************************************************/
HumanPlayerEditingBehaviorState::HumanPlayerEditingBehaviorState(UrsineEngine::GameObject& aPlayer,
                                                                 const CharacterType& aType)
  : HumanPlayerBehaviorState(aPlayer)
  , mSelectedSkill(nullptr)
{
  mCreateSkill.SetCharacterType(aType);
  mRemoveSkill.SetCharacterType(Type::eSKELETON);
}

/******************************************************************************/
void HumanPlayerEditingBehaviorState::OnEnter()
{
  // Upon entering this state, check the number of skeletons currently on the
  // board. If the maximum number of skeletons has already been reached, select
  // the RemoveCharacterSkill. Otherwise, select the CreateCharacterSkill.
  auto player = GetPlayer();
  if(player != nullptr)
  {
    auto humanPlayerBehaviorComponent = player->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    if(humanPlayerBehaviorComponent != nullptr)
    {
      auto board = humanPlayerBehaviorComponent->GetBoard();
      if(board != nullptr)
      {
        auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
        if(boardLayoutComponent != nullptr)
        {
          auto skeletons = boardLayoutComponent->GetCharactersOfType(Type::eSKELETON);
          auto maxSkeletons = humanPlayerBehaviorComponent->GetMaximumSkeletons();

          if(skeletons.size() >= maxSkeletons)
          {
            mRemoveSkill.Select(*board);
            mSelectedSkill = &mRemoveSkill;
          }
          else
          {
            mCreateSkill.Select(*board);
            mSelectedSkill = &mCreateSkill;
          }
        }
      }
    }
  }
}

/******************************************************************************/
void HumanPlayerEditingBehaviorState::OnExit()
{
  // Upon exiting this state, request a new wave of enemies.
  auto player = GetPlayer();
  if(player != nullptr)
  {
    auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
    if(playerBehaviorComponent != nullptr)
    {
      auto board = playerBehaviorComponent->GetBoard();
      if(board != nullptr)
      {
        NewEnemyWaveRequested.Notify(*board);
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerBehaviorState> HumanPlayerEditingBehaviorState::HandleSkillExecuted(Skill& aSkill)
{
  std::unique_ptr<HumanPlayerBehaviorState> newState = nullptr;

  if(&aSkill == mSelectedSkill)
  {
    if(mSelectedSkill == &mRemoveSkill)
    {
      // Now select the create skill.
      auto player = GetPlayer();
      if(player != nullptr)
      {
        auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
        if(playerBehaviorComponent != nullptr)
        {
          auto board = playerBehaviorComponent->GetBoard();
          if(board != nullptr)
          {
            mCreateSkill.Select(*board);
            mSelectedSkill = &mCreateSkill;
          }
        }
      }
    }
    else if(mSelectedSkill == &mCreateSkill)
    {
      auto player = GetPlayer();
      if(player != nullptr)
      {
        // Return to the default state.
        newState = std::make_unique<HumanPlayerDefaultBehaviorState>(*player);
      }
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerBehaviorState> HumanPlayerEditingBehaviorState::HandleSkillCancelled(Skill& aSkill)
{
  std::unique_ptr<HumanPlayerBehaviorState> newState = nullptr;

  if(&aSkill == mSelectedSkill)
  {
    auto player = GetPlayer();
    if(player != nullptr)
    {
      // Return to the default state.
      newState = std::make_unique<HumanPlayerDefaultBehaviorState>(*player);
    }
  }

  return newState;
}

#include "DefaultCharacterController.hpp"

#include "BoardLayoutComponent.hpp"

#include "DamageAction.hpp"

#include "Signals.hpp"

using Barebones::DefaultCharacterController;

/******************************************************************************/
DefaultCharacterController::DefaultCharacterController(UrsineEngine::GameObject& aCharacter)
  : CharacterController(aCharacter)
  , mBoard(nullptr)
  , mSkillToUse(nullptr)
  , mTileToUseSkillOn(-1, -1)
  , mWaitingForMove(false)
  , mWaitingForSkill(false)
{
  CharacterFinishedMovingAlongPath.Connect(mObserver, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMovingAlongPath(aCharacter);
  });

  SkillExecuted.Connect(mObserver, [this](Skill& aSkill)
  {
    this->HandleSkillExecuted(aSkill);
  });
}

/******************************************************************************/
void DefaultCharacterController::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  mBoard = &aBoard;

  bool takingTurn = false;

  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(boardLayoutComponent != nullptr &&
       characterBehaviorComponent != nullptr)
    {
      auto moveSkill = characterBehaviorComponent->GetSkill("Move");
      if(moveSkill != nullptr)
      {
        takingTurn = true;

        // Get each character on the opposing side.
        std::vector<UrsineEngine::GameObject*> opposingCharacters;
        switch(characterBehaviorComponent->GetSide())
        {
          case Side::eENEMY:
          {
            opposingCharacters = boardLayoutComponent->GetCharactersOnSide(Side::ePLAYER);
            break;
          }
          case Side::ePLAYER:
          {
            opposingCharacters = boardLayoutComponent->GetCharactersOnSide(Side::eENEMY);
            break;
          }
          default:
          {
            break;
          }
        }

        // Compare the location of this character to each opposing character's
        // location to determine the closest target.
        auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(character->GetName());
        TileLocation targetLocation(0, 0);
        double lowestDistance = INT_MAX;
        for(const auto& opposingCharacter : opposingCharacters)
        {
          auto opposingCharacterLocation = boardLayoutComponent->GetLocationOfCharacter(opposingCharacter->GetName());
          auto distance = std::sqrt(std::pow((characterLocation.first - opposingCharacterLocation.first), 2) +
                                    std::pow((characterLocation.second - opposingCharacterLocation.second), 2));
          if(distance < lowestDistance)
          {
            targetLocation = opposingCharacterLocation;
            lowestDistance = distance;
          }
        }

        // Determine the highest damaging skill this character has.
        Skill* highestDamagingSkill = nullptr;
        int highestDamage = 0;
        for(const auto& skill : characterBehaviorComponent->GetSkills())
        {
          auto damageAction = skill->GetFirstActionOfType<DamageAction>();
          if(damageAction != nullptr)
          {
            if(damageAction->GetDamage() > highestDamage)
            {
              highestDamagingSkill = skill;
            }
          }
        }

        // For each tile this character can move to, compare it to the
        // target location, then move to the closest tile.
        auto tiles = moveSkill->GetValidTiles(aBoard, characterLocation);
        TileLocation moveLocation(0, 0);
        lowestDistance = INT_MAX;
        for(const auto tile : tiles)
        {
          auto distance = std::sqrt(std::pow((targetLocation.first - tile.first), 2) +
                                    std::pow((targetLocation.second - tile.second), 2));
          if(distance < lowestDistance)
          {
            moveLocation = tile;
            lowestDistance = distance;

            // If this tile is valid for our highest damaging skill, then
            // we don't need to move any closer.
            if(highestDamagingSkill != nullptr)
            {
              if(highestDamagingSkill->IsTileValid(aBoard, moveLocation, targetLocation))
              {
                mSkillToUse = highestDamagingSkill;
                mTileToUseSkillOn = targetLocation;
                break;
              }
            }
          }
        }

        // Move to the closest tile.
        moveSkill->Execute(aBoard, moveLocation);
        mWaitingForMove = true;
      }
    }
  }

  if(!takingTurn)
  {
    EndTurn();
  }
}

/******************************************************************************/
void DefaultCharacterController::HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(aCharacter.GetParent() == GetCharacter() &&
     mWaitingForMove)
  {
    // If we have a skill to use, execute it and wait for it to finish.
    // Otherwise, end our turn now.
    if(mSkillToUse != nullptr)
    {
      mSkillToUse->Execute(*mBoard, mTileToUseSkillOn);
      mTileToUseSkillOn = TileLocation(-1, -1);
      mWaitingForMove = false;
      mWaitingForSkill = true;
    }
    else
    {
      EndTurn();
    }
  }
}

/******************************************************************************/
void DefaultCharacterController::HandleSkillExecuted(Skill& aSkill)
{
  if(&aSkill == mSkillToUse &&
     mWaitingForSkill)
  {
    mWaitingForSkill = false;
    mSkillToUse = nullptr;

    EndTurn();
  }
}

#include "DefaultCharacterController.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::DefaultCharacterController;

/******************************************************************************/
DefaultCharacterController::DefaultCharacterController(UrsineEngine::GameObject& aCharacter)
  : CharacterController(aCharacter)
  , mWaitingForMove(false)
  , mBoard(nullptr)
  , mSkillToUse(nullptr)
  , mTileToUseSkillOn(-1, -1)
{
  CharacterFinishedMovingAlongPath.Connect(mObserver, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMovingAlongPath(aCharacter);
  });
}

/******************************************************************************/
void DefaultCharacterController::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  mBoard = &aBoard;

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
        // Determine the highest damaging skill this character has.
        int highestDamage = 0;
        for(const auto& skill : characterBehaviorComponent->GetSkills())
        {
          if(skill->GetDamage() > highestDamage)
          {
            mSkillToUse = skill;
          }
        }

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

            // If we have a skill to use, and this tile is valid for using
            // that skill, then we don't need to move any closer.
            if(mSkillToUse != nullptr)
            {
              if(mSkillToUse->IsTileValid(aBoard, moveLocation, targetLocation))
              {
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
}

/******************************************************************************/
void DefaultCharacterController::HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(aCharacter.GetParent() == GetCharacter() &&
     mWaitingForMove)
  {
    if(mSkillToUse != nullptr)
    {
      mSkillToUse->Execute(*mBoard, mTileToUseSkillOn);
      mTileToUseSkillOn = TileLocation(-1, -1);
    }

    EndTurn();
  }
}

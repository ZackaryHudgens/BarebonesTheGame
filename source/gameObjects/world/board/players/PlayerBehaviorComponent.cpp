#include "PlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::PlayerBehaviorComponent;

/******************************************************************************/
PlayerBehaviorComponent::PlayerBehaviorComponent()
  : Component()
  , mControlledSide(Side::eNONE)
{
}

/******************************************************************************/
void PlayerBehaviorComponent::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  PlayerTurnBegan.Notify(*this);

  // Character skills refresh upon the start of the controlling player's
  // turn. To do this, gather each character on the board controlled by
  // this player, then enable their skills.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto controlledCharacters = boardLayoutComponent->GetCharactersOnSide(GetSide());
    for(auto& character : controlledCharacters)
    {
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        auto skills = characterBehaviorComponent->GetSkills();
        for(auto& skill : skills)
        {
          skill->SetEnabled(true);
        }
      }
    }
  }

  ProtectedTakeTurn(aBoard);
}

/******************************************************************************/
void PlayerBehaviorComponent::EndTurn()
{
  ProtectedEndTurn();
  PlayerTurnEnded.Notify(*this);
}

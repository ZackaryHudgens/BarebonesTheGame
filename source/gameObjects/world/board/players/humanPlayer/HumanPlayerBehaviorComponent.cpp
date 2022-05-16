#include "HumanPlayerBehaviorComponent.hpp"

#include "HumanPlayerInputComponent.hpp"

#include "Signals.hpp"

#include "DesecrateSpell.hpp"
#include "FireballSpell.hpp"

using Barebones::HumanPlayerBehaviorComponent;

/******************************************************************************/
HumanPlayerBehaviorComponent::HumanPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mLocation(0, 0)
  , mTakingTurn(false)
{
  SetSide(Side::ePLAYER);

  CharacterStartedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterStartedMovingAlongPath(aCharacter);
  });

  CharacterFinishedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMovingAlongPath(aCharacter);
  });
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    AddSpell(std::make_unique<DesecrateSpell>(*parent));
    AddSpell(std::make_unique<FireballSpell>(*parent));
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::SetLocation(const TileLocation& aLocation)
{
  mLocation = aLocation;
  HumanPlayerMoved.Notify(*this);
}

/******************************************************************************/
std::vector<Barebones::Skill*> HumanPlayerBehaviorComponent::GetSpells()
{
  std::vector<Skill*> spells;

  for(auto& spell : mSpells)
  {
    spells.emplace_back(spell.get());
  }

  return spells;
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  // Enable the input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
    if(inputComponent != nullptr)
    {
      mTakingTurn = true;
      inputComponent->SetEnabled(true);
      inputComponent->SetBoard(aBoard);
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::ProtectedEndTurn()
{
  // Disable the input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
    if(inputComponent != nullptr)
    {
      mTakingTurn = false;
      inputComponent->SetEnabled(false);
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::AddSpell(std::unique_ptr<Skill> aSpell)
{
  mSpells.emplace_back(std::move(aSpell));
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterStartedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(mTakingTurn)
  {
    // Disable the input component while a character is moving.
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
      if(inputComponent != nullptr)
      {
        inputComponent->SetEnabled(false);
      }
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(mTakingTurn)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
      if(inputComponent != nullptr)
      {
        inputComponent->SetEnabled(true);
      }
    }
  }
}

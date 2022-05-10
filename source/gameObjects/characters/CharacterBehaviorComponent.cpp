#include "CharacterBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <iostream>

#include <Environment.hpp>
#include <SpriteComponent.hpp>

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"

#include "CharacterDefaultState.hpp"
#include "CharacterDyingState.hpp"
#include "CharacterMovingState.hpp"
#include "CharacterShakingState.hpp"

#include "MoveSkill.hpp"

#include "StatusMessageBehaviorComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mMovementState(nullptr)
  , mStatusState(nullptr)
  , mSide(Side::eNONE)
  , mType(Type::eNONE)
  , mSpeed(1)
  , mMaximumHealth(1)
  , mCurrentHealth(1)
{
}

/******************************************************************************/
void CharacterBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Begin in the default state.
    mMovementState = std::make_unique<CharacterDefaultState>(*parent);
    mStatusState = std::make_unique<CharacterDefaultState>(*parent);

    // All characters have the move skill.
    AddSkill(std::make_unique<MoveSkill>(*GetParent()));
  }

  ProtectedInitialize();
}

/******************************************************************************/
void CharacterBehaviorComponent::Update(double aTime)
{
  // Update the movement state.
  if(mMovementState != nullptr)
  {
    auto newMovementState = mMovementState->Update(aTime);
    if(newMovementState != nullptr)
    {
      mMovementState.swap(newMovementState);
    }
  }

  // Update the status state.
  if(mStatusState != nullptr)
  {
    auto newStatusState = mStatusState->Update(aTime);
    if(newStatusState != nullptr)
    {
      mStatusState.swap(newStatusState);
    }
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::MoveToPosition(const glm::vec3& aPosition,
                                                double aSpeed)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Switch to the moving state.
    mMovementState = std::make_unique<CharacterMovingState>(*parent,
                                                            aPosition,
                                                            aSpeed);
  }
}

/******************************************************************************/
std::vector<Barebones::Skill*> CharacterBehaviorComponent::GetSkills()
{
  std::vector<Skill*> skills;

  for(auto& skill : mSkills)
  {
    skills.emplace_back(skill.get());
  }

  return skills;
}

/******************************************************************************/
Barebones::Skill* CharacterBehaviorComponent::GetSkill(const std::string& aName)
{
  Skill* skill = nullptr;

  auto findSkill = [&aName](const std::unique_ptr<Skill>& aSkill)
  {
    return aSkill->GetName() == aName;
  };

  auto foundSkill = std::find_if(mSkills.begin(),
                                 mSkills.end(),
                                 findSkill);
  if(foundSkill != mSkills.end())
  {
    skill = (*foundSkill).get();
  }

  return skill;
}

/******************************************************************************/
void CharacterBehaviorComponent::AddEffect(std::unique_ptr<Effect> aEffect)
{
  if(aEffect != nullptr)
  {
    // Display a status message when this effect is added.
    DisplayStatusMessage(aEffect->GetStatusMessage());

    mEffects.emplace_back(std::move(aEffect));
    EffectAddedToCharacter.Notify(*this, *mEffects.back());
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::RemoveEffect(const std::string& aName)
{
  auto findEffect = [aName](const std::unique_ptr<Effect>& aEffect)
  {
    return aEffect->GetName() == aName;
  };

  auto foundEffect = std::find_if(mEffects.begin(),
                                  mEffects.end(),
                                  findEffect);
  if(foundEffect != mEffects.end())
  {
    // Display a status message when this effect is removed.
    std::stringstream removedMessage;
    removedMessage << foundEffect->get()->GetName() << "\nremoved!";
    DisplayStatusMessage(removedMessage.str());

    EffectRemovedFromCharacter.Notify(*this, *(*foundEffect));
    mEffects.erase(foundEffect);
  }
}

/******************************************************************************/
std::vector<Barebones::Effect*> CharacterBehaviorComponent::GetEffects()
{
  std::vector<Effect*> effects;

  for(auto& effect : mEffects)
  {
    effects.emplace_back(effect.get());
  }

  return effects;
}

/******************************************************************************/
Barebones::TileList CharacterBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                             const TileLocation& aLocation) const
{
  TileList tiles;

  auto parent = GetParent();
  auto boardLayoutComponent = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(parent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto leftEdge = aLocation.first - 1;
    auto rightEdge = aLocation.first + 1;
    auto bottomEdge = aLocation.second - 1;
    auto topEdge = aLocation.second + 1;

    for(int column = leftEdge; column <= rightEdge; ++column)
    {
      for(int row = bottomEdge; row <= topEdge; ++row)
      {
        TileLocation newMove(column, row);

        // Before adding this as a valid move, check if there is a tile
        // at this location and that there isn't already a character there.
        if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
           boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
        {
          tiles.emplace_back(newMove);
        }
      }
    }
  }

  return tiles;
}

/******************************************************************************/
void CharacterBehaviorComponent::DealDamage(int aValue)
{
  // Apply the damage.
  SetCurrentHealth(GetCurrentHealth() - aValue);

  // Switch to the shaking state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mMovementState = std::make_unique<CharacterShakingState>(*parent);
  }

  // Create a status message to display the amount of damage dealt.
  std::stringstream damageText;
  damageText << aValue;
  DisplayStatusMessage(damageText.str());
}

/******************************************************************************/
void CharacterBehaviorComponent::AddSkill(std::unique_ptr<Skill> aSkill)
{
  mSkills.emplace_back(std::move(aSkill));
}

/******************************************************************************/
void CharacterBehaviorComponent::SetMaximumHealth(int aHealth)
{
  mMaximumHealth = aHealth;

  // If the current health is greater than the new maximum health,
  // set the current health to the new maximum.
  if(mCurrentHealth > mMaximumHealth)
  {
    SetCurrentHealth(mMaximumHealth);
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::SetCurrentHealth(int aHealth)
{
  mCurrentHealth = aHealth;

  CharacterHealthChanged.Notify(*this);

  // If the health is below 0, this character is now dying.
  if(mCurrentHealth <= 0)
  {
    CharacterDied.Notify(*this);

    auto parent = GetParent();
    if(parent != nullptr)
    {
      // Switch to the dying state.
      mStatusState = std::make_unique<CharacterDyingState>(*parent);
    }
  }
}

/******************************************************************************/
Barebones::TileAdjacencyMap CharacterBehaviorComponent::GenerateAdjacencyMap(UrsineEngine::GameObject& aBoard) const
{
  TileAdjacencyMap adjacencyMap;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto columns = boardLayoutComponent->GetColumns();
    auto rows = boardLayoutComponent->GetRows();

    for(int c = 0; c < columns; ++c)
    {
      for(int r = 0; r < rows; ++r)
      {
        TileLocation currentLocation(c, r);
        auto movements = GetMovements(aBoard, currentLocation);

        std::vector<TileEdge> edges;
        for(const auto& move : movements)
        {
          int distance = std::sqrt(std::pow((move.first - c), 2) +
                                   std::pow((move.second - r), 2));
          TileEdge edge(move, distance);
          edges.emplace_back(edge);
        }

        adjacencyMap.emplace(currentLocation, edges);
      }
    }
  }

  return adjacencyMap;
}

/******************************************************************************/
Barebones::TilePathList CharacterBehaviorComponent::GenerateShortestPathList(const TileLocation& aStartingLocation,
                                                                             const TileAdjacencyMap& aMap) const
{
  TilePathList pathList;



  return pathList;
}

/******************************************************************************/
void CharacterBehaviorComponent::DisplayStatusMessage(const std::string& aText)
{
  // Create a status message and add it to the scene.
  auto scene = env.GetCurrentScene();
  auto parent = GetParent();
  if(scene != nullptr &&
     parent != nullptr)
  {
    // Generate a name for the status message object.
    int nameIndex = 0;
    std::stringstream nameStream;
    nameStream << parent->GetName() << "StatusMessage" << aText;

    do
    {
      ++nameIndex;

      nameStream.str("");
      nameStream << parent->GetName() << "StatusMessage" << aText << nameIndex;
    }
    while(scene->GetObject(nameStream.str()) != nullptr);

    // Create the status message object.
    auto statusMessageObject = std::make_unique<UrsineEngine::GameObject>(nameStream.str());
    statusMessageObject->AddComponent(std::make_unique<StatusMessageBehaviorComponent>());
    auto statusMessageComponent = statusMessageObject->GetComponentsOfType<StatusMessageBehaviorComponent>().back();
    statusMessageComponent->SetText(aText);

    // Position the status message to be centered in front of the character.
    auto messagePos = parent->GetPosition();
    messagePos.z += 0.1;
    messagePos.x -= ((statusMessageComponent->GetTextComponent()->GetWidth() * 0.01) / 2.0);
    statusMessageObject->SetPosition(messagePos);
    statusMessageObject->SetScale(glm::vec3(0.01, 0.01, 1.0));

    // Add the status message to the scene.
    scene->AddObject(std::move(statusMessageObject));
  }
}

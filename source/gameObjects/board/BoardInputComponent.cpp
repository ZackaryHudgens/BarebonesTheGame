#include "BoardInputComponent.hpp"

#include "DefaultBoardInputState.hpp"
#include "UsingSkillBoardInputState.hpp"

#include "CharacterSkillComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "TileBehaviorComponent.hpp"

using Barebones::BoardInputComponent;

/******************************************************************************/
BoardInputComponent::BoardInputComponent()
  : Component()
  , mState(nullptr)
  , mPlayerLocation(0, 0)
  , mEnabled(true)
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
  });

  UrsineEngine::KeyRepeated.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
  {
    this->HandleKeyRepeated(aCode,
                            aMods);
  });

  SkillSelected.Connect(*this, [this](UrsineEngine::GameObject& aObject)
  {
    this->HandleSkillSelected(aObject);
  });
}

/******************************************************************************/
void BoardInputComponent::Load()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Initialize the state at position (0, 0).
    mState = std::make_unique<DefaultBoardInputState>(*parent);
  }
}

/******************************************************************************/
void BoardInputComponent::SetPlayerLocation(const TileLocation& aLocation)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layoutComponent != nullptr)
    {
      // Only move to this location if there is a tile there.
      auto tile = layoutComponent->GetTileAtLocation(aLocation);
      if(tile != nullptr)
      {
        auto prevLocation = mPlayerLocation;
        mPlayerLocation = aLocation;

        auto newState = mState->HandlePlayerMoved(prevLocation,
                                                  mPlayerLocation);
        if(newState != nullptr)
        {
          mState.swap(newState);
        }

        PlayerMoved.Notify(mPlayerLocation);
      }
    }
  }
}

/******************************************************************************/
void BoardInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                           int aMods)
{
  if(mEnabled)
  {
    if(mState != nullptr)
    {
      auto newState = mState->HandleKeyPressed(aCode,
                                               aMods);
      if(newState != nullptr)
      {
        mState.swap(newState);
      }
    }
  }
}

/******************************************************************************/
void BoardInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                            int aMods)
{
  if(mEnabled)
  {
    if(mState != nullptr)
    {
      auto newState = mState->HandleKeyRepeated(aCode,
                                                aMods);
      if(newState != nullptr)
      {
        mState.swap(newState);
      }
    }
  }
}

/******************************************************************************/
void BoardInputComponent::HandleSkillSelected(UrsineEngine::GameObject& aObject)
{
  // When a skill is selected, swap to the UsingSkill state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<UsingSkillBoardInputState>(*parent,
                                                         aObject);
  }
}

/******************************************************************************/
Barebones::PlayerMovedSignal Barebones::PlayerMoved;

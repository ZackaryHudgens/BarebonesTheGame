#include "BoardInputComponent.hpp"

#include "DefaultBoardInputState.hpp"
#include "UsingSkillBoardInputState.hpp"

#include "CharacterSkillComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "TileBehaviorComponent.hpp"

using Barebones::BoardInputComponent;

/******************************************************************************/
BoardInputComponent::BoardInputComponent()
  : InputComponent()
  , mState(nullptr)
  , mPlayerLocation(0, 0)
{
  SkillSelected.Connect(*this, [this](CharacterSkillComponent& aSkill)
  {
    this->HandleSkillSelected(aSkill);
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

/******************************************************************************/
void BoardInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                            int aMods)
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

/******************************************************************************/
void BoardInputComponent::HandleSkillSelected(CharacterSkillComponent& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillSelected(aSkill);

    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
Barebones::PlayerMovedSignal Barebones::PlayerMoved;

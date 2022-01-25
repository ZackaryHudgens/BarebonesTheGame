#include "BoardInputComponent.hpp"

#include "DefaultBoardInputState.hpp"
#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

using Barebones::BoardInputComponent;

/******************************************************************************/
BoardInputComponent::BoardInputComponent()
  : Component()
  , mState(nullptr)
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
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

    // Highlight the tile at the player's initial position.
    auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layout != nullptr)
    {
      auto tile = layout->GetTileAtPosition(mState->GetPlayerXLocation(),
                                            mState->GetPlayerYLocation());
      if(tile != nullptr)
      {
        auto tileComp = tile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileComp != nullptr)
        {
          tileComp->SetHovered(true);
        }
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

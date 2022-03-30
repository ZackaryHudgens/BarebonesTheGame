#include "TurnDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>
#include <MeshComponent.hpp>
#include <TextComponent.hpp>

#include "Signals.hpp"

#include "BoardTurnManagerComponent.hpp"

#include "PlayerBehaviorComponent.hpp"

using Barebones::TurnDisplayComponent;

/******************************************************************************/
TurnDisplayComponent::TurnDisplayComponent()
  : Component()
  , mNameText(nullptr)
  , mDisplayTime(1.0)
  , mInitialDisplayTime(0.0)
  , mDisplaying(false)
{
}

/******************************************************************************/
void TurnDisplayComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    // Add the player name text.
    auto playerName = std::make_unique<UrsineEngine::TextComponent>();
    playerName->SetFont("Alagard", "Medium");
    playerName->SetSize(48);
    playerName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("playerName");
    nameObject->AddComponent(std::move(playerName));
    parent->AddChild(std::move(nameObject));

    mNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();
  }
}

/******************************************************************************/
void TurnDisplayComponent::Update()
{
  if(mDisplaying)
  {
    double totalTime = env.GetTime() - mInitialDisplayTime;
    if(totalTime >= mDisplayTime)
    {
      mDisplaying = false;

      if(mNameText != nullptr)
      {
        mNameText->SetText("");
      }

      auto parent = GetParent();
      if(parent != nullptr)
      {
        parent->ScheduleForDeletion();
        TurnDisplayFinished.Notify(*this);
      }
    }
  }
}

/******************************************************************************/
void TurnDisplayComponent::DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer)
{
  if(mNameText != nullptr)
  {
    std::stringstream ss;
    ss << aPlayer.GetName() << "'s Turn";
    mNameText->SetText(ss.str());

    mDisplaying = true;
    mInitialDisplayTime = env.GetTime();
  }
}

#include "CharacterInfoDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"
#include <iostream>

using Barebones::CharacterInfoDisplayComponent;

/******************************************************************************/
CharacterInfoDisplayComponent::CharacterInfoDisplayComponent()
  : Component()
  , mBoard(nullptr)
  , mInfoText(nullptr)
{
  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  HumanPlayerMoved.Connect(*this, [this](HumanPlayerBehaviorComponent& aPlayer)
  {
    this->HandleHumanPlayerMoved(aPlayer);
  });
}

/******************************************************************************/
void CharacterInfoDisplayComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    // Create the information text and a GameObject to hold it.
    auto infoText = std::make_unique<UrsineEngine::TextComponent>();
    infoText->SetFont("Alagard", "Medium");
    infoText->SetSize(48);
    infoText->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto textObject = std::make_unique<UrsineEngine::GameObject>("characterInfoText");
    textObject->AddComponent(std::move(infoText));
    textObject->SetPosition(glm::vec3(10.0,
                                      overlayHeight - 100.0,
                                      0.9));

    parent->AddChild(std::move(textObject));
    mInfoText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();
  }
}

/******************************************************************************/
void CharacterInfoDisplayComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  auto humanPlayerBehaviorComponent = dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer);
  if(humanPlayerBehaviorComponent != nullptr)
  {
    HandleHumanPlayerMoved(*humanPlayerBehaviorComponent);
  }
}

/******************************************************************************/
void CharacterInfoDisplayComponent::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
{
  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      // If there is a character at the player's location, update the info text.
      // Otherwise, clear the info text.
      auto character = boardLayoutComponent->GetCharacterAtLocation(aPlayer.GetLocation());
      if(character != nullptr)
      {
        auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
        if(characterBehaviorComponent != nullptr &&
           mInfoText != nullptr)
        {
          std::stringstream ss;
          ss << characterBehaviorComponent->GetName() << ": "
             << characterBehaviorComponent->GetCurrentHealth() << "/"
             << characterBehaviorComponent->GetMaximumHealth();

          mInfoText->SetText(ss.str());
        }
      }
      else if(mInfoText != nullptr)
      {
        mInfoText->SetText("???");
      }
    }
  }
}

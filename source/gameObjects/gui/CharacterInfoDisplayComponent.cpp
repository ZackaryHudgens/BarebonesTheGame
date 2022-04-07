#include "CharacterInfoDisplayComponent.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterInfoDisplayComponent;

/******************************************************************************/
CharacterInfoDisplayComponent::CharacterInfoDisplayComponent()
  : Component()
  , mBoard(nullptr)
  , mTextBox(nullptr)
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
    // Add a text box to the parent.
    parent->AddComponent(std::make_unique<TextBoxComponent>());
    mTextBox = parent->GetFirstComponentOfType<TextBoxComponent>();

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    mTextBox->SetTexture(backgroundTexture);

    mTextBox->SetFont("Alagard", "Medium");
    mTextBox->SetTextSize(48);
    mTextBox->SetTextAlignment(TextAlignment::eLEFT);
    mTextBox->SetTextColor(glm::vec4(0.247, 0.314, 0.247, 1.0));
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
           mTextBox != nullptr)
        {
          std::stringstream ss;
          ss << characterBehaviorComponent->GetName() << ": "
             << characterBehaviorComponent->GetCurrentHealth() << "/"
             << characterBehaviorComponent->GetMaximumHealth();

          mTextBox->SetText(ss.str());
        }
      }
      else if(mTextBox != nullptr)
      {
        mTextBox->SetText("Empty Space");
      }
    }
  }
}

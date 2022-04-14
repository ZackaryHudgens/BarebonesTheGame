#include "InfoPanelBehaviorComponent.hpp"

#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::InfoPanelBehaviorComponent;

/******************************************************************************/
InfoPanelBehaviorComponent::InfoPanelBehaviorComponent()
  : Component()
  , mBoard(nullptr)
  , mTextBox(nullptr)
  , mFocusedLocation(0, 0)
  , mTextBoxHeight(100.0)
  , mTextBoxHorizontalPadding(130.0)
  , mTextBoxVerticalPadding(25.0)
{
  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  HumanPlayerMoved.Connect(*this, [this](HumanPlayerBehaviorComponent& aPlayer)
  {
    this->HandleHumanPlayerMoved(aPlayer);
  });

  CharacterTurnBegan.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnBegan(aCharacter);
  });

  CharacterFinishedMoving.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMoving(aCharacter);
  });
}

/******************************************************************************/
void InfoPanelBehaviorComponent::Initialize()
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
    mTextBox->SetTextSize(72);
    mTextBox->SetTextAlignment(TextAlignment::eLEFT);
    mTextBox->SetTextColor(glm::vec4(0.247, 0.314, 0.247, 1.0));

    mTextBox->SetHorizontalPadding(mTextBoxHorizontalPadding);
    mTextBox->SetVerticalPadding(mTextBoxVerticalPadding);

    // Set the dimensions of the text box so that it stretches
    // across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    mTextBox->SetWidth(overlayWidth);
    mTextBox->SetHeight(mTextBoxHeight);
    mTextBox->SetFixedWidth(true);
    mTextBox->SetFixedHeight(true);

    // Center the display on the screen.
    double horizontalCenter = overlayWidth / 2.0;
    parent->SetPosition(glm::vec3(horizontalCenter,
                                  overlayHeight - (mTextBoxHeight / 2.0),
                                  0.0));
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  auto humanPlayerBehaviorComponent = dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer);
  if(humanPlayerBehaviorComponent != nullptr)
  {
    HandleHumanPlayerMoved(*humanPlayerBehaviorComponent);
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
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
          ss << characterBehaviorComponent->GetName() << "   HP: "
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

  mFocusedLocation = aPlayer.GetLocation();
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    if(mTextBox != nullptr)
    {
      std::stringstream ss;
      ss << aCharacter.GetName() << "   HP: "
         << aCharacter.GetCurrentHealth() << "/"
         << aCharacter.GetMaximumHealth();

      mTextBox->SetText(ss.str());
    }
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter)
{
  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto characterObject = aCharacter.GetParent();
      if(characterObject != nullptr)
      {
        auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(characterObject->GetName());

        // Only update the info text if the character moved into the focused tile.
        if(mFocusedLocation == characterLocation)
        {
          if(mTextBox != nullptr)
          {
            std::stringstream ss;
            ss << aCharacter.GetName() << "   HP: "
               << aCharacter.GetCurrentHealth() << "/"
               << aCharacter.GetMaximumHealth();

            mTextBox->SetText(ss.str());
          }
        }
      }
    }
  }
}

#include "InfoPanelBehaviorComponent.hpp"

#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"
#include "Signals.hpp"

using Barebones::InfoPanelBehaviorComponent;

/******************************************************************************/
InfoPanelBehaviorComponent::InfoPanelBehaviorComponent()
  : Component()
  , mBoard(nullptr)
  , mTextBox(nullptr)
  , mFocusedLocation(0, 0)
  , mTextBoxHeight(70.0)
  , mTextBoxVerticalPadding(23.0)
{
  BoardFocusedTileChanged.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });

  CharacterTurnBegan.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnBegan(aCharacter);
  });

  CharacterFinishedMoving.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMoving(aCharacter);
  });

  CharacterHealthChanged.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterHealthChanged(aCharacter);
  });

  CharacterDied.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterDied(aCharacter);
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
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    mTextBox->SetTexture(backgroundTexture);

    mTextBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mTextBox->SetTextSize(BIG_FONT_SIZE);
    mTextBox->SetTextAlignment(TextAlignment::eCENTER);

    auto textShader = mTextBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", (glm::vec4(BACKGROUND_COLOR, 1.0)));
    }

    mTextBox->SetVerticalPadding(mTextBoxVerticalPadding);

    // Set the dimensions of the text box so that it stretches
    // across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    mTextBox->SetWidth(overlayWidth);
    mTextBox->SetHeight(mTextBoxHeight);
    mTextBox->SetFixedWidth(true);
    mTextBox->SetFixedHeight(true);

    mTextBox->SetText("");

    // Center the display on the screen.
    double horizontalCenter = overlayWidth / 2.0;
    parent->SetPosition(glm::vec3(horizontalCenter,
                                  overlayHeight - (mTextBoxHeight / 2.0),
                                  0.0));
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  if(mBoard == &aBoard)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      mFocusedLocation = boardLayoutComponent->GetFocusedTileLocation();
      UpdateText();
    }
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto characterObject = aCharacter.GetParent();
      if(characterObject != nullptr)
      {
        mFocusedLocation = boardLayoutComponent->GetLocationOfCharacter(characterObject->GetName());
        UpdateText();
      }
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
        auto location = boardLayoutComponent->GetLocationOfCharacter(characterObject->GetName());
        if(location == mFocusedLocation)
        {
          UpdateText();
        }
      }
    }
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleCharacterHealthChanged(CharacterBehaviorComponent& aCharacter)
{
  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto characterObject = aCharacter.GetParent();
      if(characterObject != nullptr)
      {
        auto location = boardLayoutComponent->GetLocationOfCharacter(characterObject->GetName());
        if(location == mFocusedLocation)
        {
          UpdateText();
        }
      }
    }
  }
}

/******************************************************************************/
void InfoPanelBehaviorComponent::HandleCharacterDied(CharacterBehaviorComponent& aCharacter)
{
  // If the character that died was at the focused location,
  // it may have already been removed from the board. In that case,
  // we can't rely on using GetLocationOfCharacter to check the dead
  // character's location, so we need to update the text regardless.
  UpdateText();
}

/******************************************************************************/
void InfoPanelBehaviorComponent::UpdateText()
{
  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      // If there is a character at the player's location, update the info text.
      // Otherwise, clear the info text.
      auto character = boardLayoutComponent->GetCharacterAtLocation(mFocusedLocation);
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
}

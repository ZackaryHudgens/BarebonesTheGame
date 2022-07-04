#include "ScrollingMessageBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "TextBoxComponent.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"

#include <iostream>

using Barebones::ScrollingMessageBehaviorComponent;

/******************************************************************************/
ScrollingMessageBehaviorComponent::ScrollingMessageBehaviorComponent(const std::string& aText,
                                                                     int aFontSize,
                                                                     double aSpeed,
                                                                     int aVerticalPadding)
  : Component()
  , mText(aText)
  , mFontSize(aFontSize)
  , mSpeed(aSpeed)
  , mTextBoxVerticalPadding(aVerticalPadding)
  , mMoving(true)
  , mTimeBecamePaused(0.0)
  , mTimeToSpendPaused(1.0)
  , mCurrentlyPaused(false)
  , mHasPaused(false)
{
}

/******************************************************************************/
void ScrollingMessageBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a text box and add it to the parent.
    parent->AddComponent(std::make_unique<TextBoxComponent>());
    auto textBox = parent->GetComponentsOfType<TextBoxComponent>().back();

    // Set the dimensions of the text box to stretch across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    textBox->SetWidth(overlayWidth);
    textBox->SetFixedWidth(true);

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    textBox->SetTexture(backgroundTexture);

    textBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    textBox->SetTextSize(mFontSize);
    textBox->SetTextAlignment(TextAlignment::eCENTER);
    textBox->SetVerticalPadding(mTextBoxVerticalPadding);
    textBox->SetText(mText);

    auto textShader = textBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    // Move the parent object to be just to the right of the overlay,
    // centered vertically.
    auto xPos = overlayWidth * 1.5;
    auto yPos = overlayHeight / 2.0;
    parent->SetPosition(glm::vec3(xPos, yPos, 0.1));
  }
}

/******************************************************************************/
void ScrollingMessageBehaviorComponent::Update(double aTime)
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto pos = parent->GetPosition();
      pos.x -= mSpeed;
      parent->SetPosition(pos);

      // If the text box is now in the center of the overlay,
      // pause for a moment so the player can read the text.
      double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
      if(!mHasPaused &&
         pos.x <= (overlayWidth / 2.0))
      {
        pos.x = (overlayWidth / 2.0);
        parent->SetPosition(pos);

        mHasPaused = true;
        mCurrentlyPaused = true;
        mMoving = false;

        mTimeBecamePaused = aTime;
      }
      else
      {
        auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
        if(pos.x <= -(overlayWidth / 2.0))
        {
          parent->ScheduleForDeletion();
        }
      }
    }
  }
  else if(mCurrentlyPaused)
  {
    auto timeSpentPaused = aTime - mTimeBecamePaused;
    if(timeSpentPaused >= mTimeToSpendPaused)
    {
      mMoving = true;
      mCurrentlyPaused = false;
    }
  }
}

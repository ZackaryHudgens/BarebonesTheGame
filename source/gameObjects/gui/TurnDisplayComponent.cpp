#include "TurnDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>

#include "Signals.hpp"

#include "PlayerBehaviorComponent.hpp"

using Barebones::TurnDisplayComponent;

/******************************************************************************/
TurnDisplayComponent::TurnDisplayComponent()
  : Component()
  , mTextBox(nullptr)
  , mTextBoxVerticalPadding(30.0)
  , mSpeed(200.0)
  , mMoving(false)
  , mTimeBecamePaused(0.0)
  , mTimeToSpendPaused(1.0)
  , mCurrentlyPaused(false)
  , mHasPaused(false)
{
}

/******************************************************************************/
void TurnDisplayComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a text box and add it to the parent.
    parent->AddComponent(std::make_unique<TextBoxComponent>());
    mTextBox = parent->GetComponentsOfType<TextBoxComponent>().back();

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    mTextBox->SetTexture(backgroundTexture);

    mTextBox->SetFont("Alagard", "Medium");
    mTextBox->SetTextSize(96);
    mTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mTextBox->SetTextColor(glm::vec4(0.125, 0.125, 0.125, 1.0));
    mTextBox->SetVerticalPadding(mTextBoxVerticalPadding);

    // Set the dimensions of the text box to stretch across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    mTextBox->SetWidth(overlayWidth);
    mTextBox->SetFixedWidth(true);

    // Move the parent object to be just to the right of the overlay,
    // centered vertically.
    auto xPos = overlayWidth * 1.5;
    auto yPos = overlayHeight / 2.0;
    parent->SetPosition(glm::vec3(xPos,
                                  yPos,
                                  0.1));
  }
}

/******************************************************************************/
void TurnDisplayComponent::Update(double aTime)
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
          TurnDisplayFinished.Notify(*this);
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

/******************************************************************************/
void TurnDisplayComponent::DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer)
{
  if(mTextBox != nullptr)
  {
    std::stringstream ss;
    ss << aPlayer.GetName() << "'s Turn";
    mTextBox->SetText(ss.str());

    mMoving = true;
  }
}

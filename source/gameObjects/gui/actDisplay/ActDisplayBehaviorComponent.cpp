#include "ActDisplayBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "Colors.hpp"
#include "Fonts.hpp"
#include "Signals.hpp"

using Barebones::ActDisplayBehaviorComponent;

/******************************************************************************/
ActDisplayBehaviorComponent::ActDisplayBehaviorComponent()
  : Component()
  , mActNameTextbox(nullptr)
  , mActDescriptionTextbox(nullptr)
  , mFadeSpeed(0.1)
  , mFadeValue(0.0)
  , mFadingIn(true)
  , mFadingOut(false)
{
  ActDisplayAdvanced.Connect(*this, [this](UrsineEngine::GameObject& aDisplay)
  {
    this->HandleActDisplayAdvanced(aDisplay);
  });
}

/******************************************************************************/
void ActDisplayBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create two text boxes and add them as child objects.
    auto actNameObject = std::make_unique<UrsineEngine::GameObject>("actName");
    actNameObject->AddComponent(std::make_unique<TextBoxComponent>());
    parent->AddChild(std::move(actNameObject));
    mActNameTextbox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    auto actDescriptionObject = std::make_unique<UrsineEngine::GameObject>("actDescription");
    actDescriptionObject->AddComponent(std::make_unique<TextBoxComponent>());
    parent->AddChild(std::move(actDescriptionObject));
    mActDescriptionTextbox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    mActNameTextbox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mActNameTextbox->SetTextSize(108);
    mActNameTextbox->SetTextAlignment(TextAlignment::eCENTER);

    auto textShader = mActNameTextbox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    mActDescriptionTextbox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mActDescriptionTextbox->SetTextSize(BIG_FONT_SIZE);
    mActDescriptionTextbox->SetTextAlignment(TextAlignment::eCENTER);

    textShader = mActDescriptionTextbox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    // Position the two text boxes to be centered on the screen.
    auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    auto centerWidth = overlayWidth / 2.0;
    auto centerHeight = overlayHeight / 2.0;

    mActNameTextbox->GetParent()->SetPosition(glm::vec3(centerWidth, centerHeight, 0.0));
    mActDescriptionTextbox->GetParent()->SetPosition(glm::vec3(centerWidth, centerHeight - 50.0, 0.0));
  }

  UpdateText();
}

/******************************************************************************/
void ActDisplayBehaviorComponent::Update(double aTime)
{
  if(mFadingIn)
  {
    mFadeValue += mFadeSpeed;

    if(mFadeValue >= 1.0)
    {
      mFadingIn = false;

      auto parent = GetParent();
      if(parent != nullptr)
      {
        ActDisplayReadyForInput.Notify(*parent);
      }
    }
  }
  else if(mFadingOut)
  {
    mFadeValue -= mFadeSpeed;

    if(mFadeValue <= 0.0)
    {
      mFadingOut = false;

      auto parent = GetParent();
      if(parent != nullptr)
      {
        ActDisplayFinished.Notify(*parent);
        parent->ScheduleForDeletion();
      }
    }
  }

  if(mActNameTextbox != nullptr)
  {
    auto textShader = mActNameTextbox->GetTextShader();
    textShader->Activate();
    textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, mFadeValue));
  }

  if(mActDescriptionTextbox != nullptr)
  {
    auto textShader = mActDescriptionTextbox->GetTextShader();
    textShader->Activate();
    textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, mFadeValue));
  }
}

/******************************************************************************/
void ActDisplayBehaviorComponent::DisplayTextForAct(const Act& aAct)
{
  switch(aAct)
  {
    case Act::eACT_ONE:
    {
      mActName = "Act One";
      mActDescription = "Castle Outskirts";
      break;
    }
    case Act::eACT_TWO:
    {
      mActName = "Act Two";
      mActDescription = "Castle Town";
      break;
    }
    case Act::eACT_THREE:
    {
      mActName = "Act Three";
      mActDescription = "Throne Room";
      break;
    }
    case Act::eFINALE:
    {
      mActName = "Finale";
      mActDescription = "????????????????????????????????????????????????????";
      break;
    }
    default:
    {
      break;
    }
  }

  UpdateText();
}

/******************************************************************************/
void ActDisplayBehaviorComponent::HandleActDisplayAdvanced(UrsineEngine::GameObject& aDisplay)
{
  if(&aDisplay == GetParent())
  {
    mFadingOut = true;
  }
}

/******************************************************************************/
void ActDisplayBehaviorComponent::UpdateText()
{
  if(mActNameTextbox != nullptr)
  {
    mActNameTextbox->SetText(mActName);
  }

  if(mActDescriptionTextbox != nullptr)
  {
    mActDescriptionTextbox->SetText(mActDescription);
  }
}

#include "StatusMessageBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Colors.hpp"
#include "Fonts.hpp"

using Barebones::StatusMessageBehaviorComponent;

/******************************************************************************/
StatusMessageBehaviorComponent::StatusMessageBehaviorComponent()
  : Component()
  , mTextComponent(nullptr)
{
}

/******************************************************************************/
void StatusMessageBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create the text.
    parent->AddComponent(std::make_unique<UrsineEngine::TextComponent>());
    mTextComponent = parent->GetComponentsOfType<UrsineEngine::TextComponent>().back();

    mTextComponent->SetRenderOption(GL_DEPTH_TEST, false);

    std::string vertexFile = "resources/shaders/OutlinedTextShader.vert";
    std::string fragmentFile = "resources/shaders/OutlinedTextShader.frag";
    UrsineEngine::Shader outlineTextShader(vertexFile, fragmentFile);
    outlineTextShader.Activate();
    outlineTextShader.SetVec4("textColor", glm::vec4(FOREGROUND_COLOR, 1.0));
    outlineTextShader.SetVec4("outlineColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    outlineTextShader.SetFloat("outlineWidth", 2.0);
    mTextComponent->AddShader("outlineTextShader", outlineTextShader);
    mTextComponent->SetCurrentShader("outlineTextShader");

    mTextComponent->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mTextComponent->SetSize(BIG_FONT_SIZE);
    mTextComponent->SetText(mText);
  }
}

/******************************************************************************/
void StatusMessageBehaviorComponent::Update(double aTime)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto pos = parent->GetPosition();
    pos.y += 0.02;
    parent->SetPosition(pos);

    if(pos.y >= 2.0)
    {
      parent->ScheduleForDeletion();
    }
  }
}

/******************************************************************************/
void StatusMessageBehaviorComponent::SetText(const std::string& aText)
{
  mText = aText;

  if(mTextComponent != nullptr)
  {
    mTextComponent->SetText(mText);
  }
}

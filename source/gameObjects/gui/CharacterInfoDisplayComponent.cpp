#include "CharacterInfoDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterInfoDisplayComponent;

/******************************************************************************/
CharacterInfoDisplayComponent::CharacterInfoDisplayComponent()
  : Component()
  , mBoard(nullptr)
  , mInfoText(nullptr)
  , mBackground(nullptr)
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

    // Create a background.
    auto menuBackground = std::make_unique<UrsineEngine::SpriteComponent>();
    menuBackground->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    menuBackground->SetHasTransparency(false);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader uiShader(vertexFile, fragmentFile);
    menuBackground->AddShader("uiShader", uiShader);
    menuBackground->SetCurrentShader("uiShader");

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    menuBackground->SetTexture(backgroundTexture);

    // Scale the background to stretch across the overlay.
    double textureWidth = backgroundTexture.GetData().mWidth;
    double textureHeight = backgroundTexture.GetData().mHeight;
    double xScalar = overlayWidth / textureWidth;
    double yScalar = 10.0;

    auto menuBackgroundObject = std::make_unique<UrsineEngine::GameObject>("menuBackground");
    menuBackgroundObject->AddComponent(std::move(menuBackground));
    menuBackgroundObject->SetScale(glm::vec3(xScalar,
                                             yScalar,
                                             1.0));

    double backgroundWidth = xScalar * textureWidth;
    double backgroundHeight = yScalar * textureHeight;
    menuBackgroundObject->SetPosition(glm::vec3(backgroundWidth / 2.0,
                                                overlayHeight - (backgroundHeight / 2.0),
                                                -0.9));
    parent->AddChild(std::move(menuBackgroundObject));
    mBackground = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();

    // Create the information text and a GameObject to hold it.
    auto infoText = std::make_unique<UrsineEngine::TextComponent>();
    infoText->SetFont("Alagard", "Medium");
    infoText->SetSize(72);
    infoText->SetColor(glm::vec4(0.247, 0.314, 0.247, 1.0));
    infoText->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto textObject = std::make_unique<UrsineEngine::GameObject>("characterInfoText");
    textObject->AddComponent(std::move(infoText));
    textObject->SetPosition(glm::vec3(125.0,
                                      overlayHeight - (backgroundHeight / 2.0),
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

          // Reposition the text to be centered vertically
          // with respect to the background.
          if(mBackground != nullptr)
          {
            auto backgroundObject = mBackground->GetParent();
            auto textObject = mInfoText->GetParent();
            if(backgroundObject != nullptr &&
               textObject != nullptr)
            {
              double textHeight = mInfoText->GetHeight();
              double backgroundYPos = backgroundObject->GetPosition().y;

              auto textPos = textObject->GetPosition();
              textPos.y = backgroundYPos - (textHeight / 2.0);
              textObject->SetPosition(textPos);
            }
          }
        }
      }
      else if(mInfoText != nullptr)
      {
        mInfoText->SetText("Empty Space");
      }
    }
  }
}

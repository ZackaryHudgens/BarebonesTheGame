#include "RewardsMenuLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>
#include <SpriteComponent.hpp>

#include "TextBoxComponent.hpp"

#include "CharacterFactory.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"

#include <iostream>

using Barebones::RewardsMenuLayoutComponent;

/******************************************************************************/
RewardsMenuLayoutComponent::RewardsMenuLayoutComponent()
  : MenuLayoutComponent()
  , mCursor(nullptr)
  , mCharacterScalar(15.0)
  , mTitleHeight(100)
  , mTitleVerticalPadding(25)
  , mDescriptionHeight(50)
  , mDescriptionVerticalPadding(15)
  , mCharacterBackgroundHeight(500)
  , mCharacterHorizontalSpacing(300)
{
}

/******************************************************************************/
void RewardsMenuLayoutComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a title text box.
    auto titleObject = std::make_unique<UrsineEngine::GameObject>("title");
    titleObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto textBox = titleObject->GetFirstComponentOfType<TextBoxComponent>();

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    textBox->SetTexture(backgroundTexture);
    
    textBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    textBox->SetTextSize(BIGGEST_FONT_SIZE);
    textBox->SetTextAlignment(TextAlignment::eCENTER);

    auto textShader = textBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    textBox->SetWidth(overlayWidth);
    textBox->SetHeight(mTitleHeight);
    textBox->SetFixedWidth(true);
    textBox->SetFixedHeight(true);

    textBox->SetVerticalPadding(mTitleVerticalPadding);
    textBox->SetText("Bones to Pick");

    double horizontalCenter = overlayWidth / 2.0;
    double textBoxHeight = textBox->GetHeight();
    titleObject->SetPosition(glm::vec3(horizontalCenter,
                                       overlayHeight - (textBoxHeight / 2.0),
                                       0.0));
    parent->AddChild(std::move(titleObject));

    // Create a description text box.
    auto descriptionObject = std::make_unique<UrsineEngine::GameObject>("description");
    descriptionObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto descriptionTextBox = descriptionObject->GetFirstComponentOfType<TextBoxComponent>();

    descriptionTextBox->SetTexture(backgroundTexture);
    
    descriptionTextBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    descriptionTextBox->SetTextSize(MEDIUM_FONT_SIZE);
    descriptionTextBox->SetTextAlignment(TextAlignment::eCENTER);

    textShader = descriptionTextBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    descriptionTextBox->SetWidth(overlayWidth);
    descriptionTextBox->SetHeight(mDescriptionHeight);
    descriptionTextBox->SetFixedWidth(true);
    descriptionTextBox->SetFixedHeight(true);

    descriptionTextBox->SetVerticalPadding(mDescriptionVerticalPadding);
    descriptionTextBox->SetText("To the victor go the spoils! Choose a skeleton to add to your entourage.");

    textBoxHeight = descriptionTextBox->GetHeight();
    descriptionObject->SetPosition(glm::vec3(horizontalCenter,
                                             overlayHeight - (textBoxHeight / 2.0) - mTitleHeight,
                                             0.0));
    parent->AddChild(std::move(descriptionObject));

    // Create a background mesh for the characters to sit in front of.
    auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("background");
    backgroundObject->AddComponent(std::make_unique<UrsineEngine::MeshComponent>());
    auto backgroundMesh = backgroundObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    backgroundMesh->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    backgroundMesh->AddTexture(backgroundTexture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader backgroundShader(vertexFile, fragmentFile);
    backgroundMesh->AddShader("default", backgroundShader);
    backgroundMesh->SetCurrentShader("default");

    backgroundMesh->AddIndex(0);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(2);

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
    vertex.mTexCoords = glm::vec2(0.0, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth, 0.0, 0.0);
    vertex.mTexCoords = glm::vec2(1.0, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth, mCharacterBackgroundHeight, 0.0);
    vertex.mTexCoords = glm::vec2(1.0, 1.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(0.0, mCharacterBackgroundHeight, 0.0);
    vertex.mTexCoords = glm::vec2(0.0, 1.0);
    backgroundMesh->AddVertex(vertex);

    auto backgroundYPos = (overlayHeight - mCharacterBackgroundHeight) / 2.0;
    backgroundObject->SetPosition(glm::vec3(0.0, backgroundYPos, -0.1));
    parent->AddChild(std::move(backgroundObject));

    // Create a cursor.
    auto cursorObject = std::make_unique<UrsineEngine::GameObject>("cursor");
    auto cursorSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    cursorSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture spriteTexture;
    spriteTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    spriteTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    spriteTexture.CreateTextureFromFile("resources/sprites/gui/menuArrow.png");
    cursorSprite->SetTexture(spriteTexture);

    UrsineEngine::Shader spriteShader(vertexFile, fragmentFile);
    cursorSprite->AddShader("default", spriteShader);
    cursorSprite->SetCurrentShader("default");

    cursorObject->AddComponent(std::move(cursorSprite));
    cursorObject->SetScale(glm::vec3(5.0, 5.0, 1.0));
    parent->AddChild(std::move(cursorObject));
    mCursor = parent->GetChildren().back();
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::HandleActionAdded()
{
  auto actions = GetActions();
  if(!actions.empty())
  {
    std::stringstream nameStream;
    nameStream << "characterAction_" << mCharacters.size();

    auto character = CharacterFactory::CreateCharacter(CharacterType::eBASIC_SKELETON,
                                                       nameStream.str());
    auto characterMesh = character->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(characterMesh != nullptr)
    {
      characterMesh->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    }

    auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    auto centerHeight = overlayHeight / 2.0;
    auto centerWidth = overlayWidth / 2.0;

    character->SetPosition(glm::vec3(mCharacters.size() * mCharacterHorizontalSpacing, centerHeight, 0.1));
    character->SetScale(glm::vec3(mCharacterScalar, mCharacterScalar, 1.0));

    auto parent = GetParent();
    if(parent != nullptr)
    {
      parent->AddChild(std::move(character));
      mCharacters.emplace_back(actions.back(), parent->GetChildren().back());
    }

    RepositionCharacters();
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
    auto findCharacter = [action](const CharacterActionPair& aPair)
    {
      return aPair.first == action;
    };

    auto foundCharacter = std::find_if(mCharacters.begin(),
                                       mCharacters.end(),
                                       findCharacter);
    if(foundCharacter != mCharacters.end())
    {
      auto characterPos = foundCharacter->second->GetPosition();
      characterPos.x -= 10;
      mCursor->SetPosition(characterPos);
    }
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::RepositionCharacters()
{
  auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
  auto totalCharacterWidth = mCharacterHorizontalSpacing * (mCharacters.size() - 1);
  auto distanceFromLeft = (overlayWidth - totalCharacterWidth) / 2.0;
  for(auto& characterPair : mCharacters)
  {
    auto characterPos = characterPair.second->GetPosition();
    characterPos.x = distanceFromLeft;
    characterPair.second->SetPosition(characterPos);
    distanceFromLeft += mCharacterHorizontalSpacing;
  }
}

#include "RewardsMenuLayoutComponent.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>
#include <SpriteComponent.hpp>

#include "TextBoxComponent.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "CharacterFactory.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"
#include "Signals.hpp"

using Barebones::RewardsMenuLayoutComponent;

/******************************************************************************/
RewardsMenuLayoutComponent::RewardsMenuLayoutComponent()
  : MenuLayoutComponent()
  , mCursor(nullptr)
  , mNameText(nullptr)
  , mStatsText(nullptr)
  , mFocusedCharacter(nullptr)
  , mShowWarning(false)
  , mCharacterScalar(10.0)
  , mTitleHeight(100)
  , mTitleVerticalPadding(25)
  , mDescriptionHeight(50)
  , mDescriptionVerticalPadding(15)
  , mCharacterBackgroundHeight(300)
  , mCharacterVerticalPadding(85)
  , mCharacterHorizontalPadding(300)
  , mCharacterNameVerticalPadding(50)
{
}

/******************************************************************************/
void RewardsMenuLayoutComponent::CreateActionForCharacterType(const CharacterType& aType)
{
  // Add an action for the new character type.
  std::stringstream nameStream;
  nameStream << "characterAction_" << mCharacters.size();

  auto newAction = std::make_unique<MenuAction>(nameStream.str());
  auto characterType = aType;
  auto actionFunction = [characterType]()
  {
    CharacterSelectedFromRewardsMenu.Notify(characterType);
  };
  newAction->SetFunction(actionFunction);
  AddAction(std::move(newAction));

  // Create a character of the given type, then add it to the parent
  // as a child object.
  auto character = CharacterFactory::CreateCharacter(aType, nameStream.str());
  auto characterSprite = character->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();
  if(characterSprite != nullptr)
  {
    characterSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    characterSprite->SetFrameOfAnimation(0);
  }

  character->SetScale(glm::vec3(mCharacterScalar,
                                mCharacterScalar,
                                1.0));

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(character));
    mCharacters.emplace_back(GetActions().back(), parent->GetChildren().back());

    if(mFocusedCharacter == nullptr)
    {
      mFocusedCharacter = mCharacters.back().second;
      UpdateCharacterInfo();
      CreateSkillTextBoxes();
    }
  }

  // Reposition elements.
  RepositionCharacters();
  RepositionCursor();
  RepositionCharacterInfo();
}

/******************************************************************************/
void RewardsMenuLayoutComponent::SetShowMaxSizeWarning(bool aShowWarning)
{
  mShowWarning = aShowWarning;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create the warning text box.
    auto warningObject = CreateTextBoxObject("warning");
    auto warningTextBox = warningObject->GetFirstComponentOfType<TextBoxComponent>();

    auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    auto horizontalCenter = overlayWidth / 2.0;

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");

    warningTextBox->SetTexture(backgroundTexture);
    warningTextBox->SetTextSize(MEDIUM_FONT_SIZE);

    warningTextBox->SetWidth(overlayWidth);
    warningTextBox->SetHeight(mDescriptionHeight);
    warningTextBox->SetFixedWidth(true);
    warningTextBox->SetFixedHeight(true);

    warningTextBox->SetVerticalPadding(mDescriptionVerticalPadding);

    std::stringstream descStream;
    descStream << "Your magic can only sustain 7 skeletons at a time.";
    descStream << " You'll have to get rid of one if you make another.";
    warningTextBox->SetText(descStream.str());

    warningObject->SetPosition(glm::vec3(horizontalCenter,
                                         overlayHeight - (mDescriptionHeight * 1.5) - mTitleHeight,
                                         0.0));
    parent->AddChild(std::move(warningObject));
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a title text box.
    auto titleObject = CreateTextBoxObject("title");
    auto titleTextBox = titleObject->GetFirstComponentOfType<TextBoxComponent>();

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    titleTextBox->SetTexture(backgroundTexture);

    titleTextBox->SetTextSize(BIGGEST_FONT_SIZE);

    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    titleTextBox->SetWidth(overlayWidth);
    titleTextBox->SetHeight(mTitleHeight);
    titleTextBox->SetFixedWidth(true);
    titleTextBox->SetFixedHeight(true);

    titleTextBox->SetVerticalPadding(mTitleVerticalPadding);
    titleTextBox->SetText("Bones to Pick!");

    double horizontalCenter = overlayWidth / 2.0;
    double textBoxHeight = titleTextBox->GetHeight();
    titleObject->SetPosition(glm::vec3(horizontalCenter,
                                       overlayHeight - (textBoxHeight / 2.0),
                                       0.0));
    parent->AddChild(std::move(titleObject));

    // Create a description text box.
    auto descriptionObject = CreateTextBoxObject("description");
    auto descriptionTextBox = descriptionObject->GetFirstComponentOfType<TextBoxComponent>();

    descriptionTextBox->SetTexture(backgroundTexture);
    descriptionTextBox->SetTextSize(MEDIUM_FONT_SIZE);

    descriptionTextBox->SetWidth(overlayWidth);
    descriptionTextBox->SetHeight(mDescriptionHeight);
    descriptionTextBox->SetFixedWidth(true);
    descriptionTextBox->SetFixedHeight(true);

    descriptionTextBox->SetVerticalPadding(mDescriptionVerticalPadding);

    std::stringstream descStream;
    descStream << "You'll make better use of them than they ever did.";
    descStream << " Choose a skeleton to add to your entourage.";
    descriptionTextBox->SetText(descStream.str());

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

    // Create a character name text box.
    parent->AddChild(CreateTextBoxObject("characterName"));
    mNameText = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();
    mNameText->SetTextSize(BIG_FONT_SIZE);

    // Create a character stats text box.
    parent->AddChild(CreateTextBoxObject("characterStats"));
    mStatsText = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();
    mStatsText->SetTextSize(MEDIUM_FONT_SIZE);

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
    cursorObject->SetRotation(-90.0, glm::vec3(0.0, 0.0, 1.0));
    parent->AddChild(std::move(cursorObject));
    mCursor = parent->GetChildren().back();
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
      mFocusedCharacter = foundCharacter->second;

      // Update the name and stats text.
      UpdateCharacterInfo();

      // Reposition elements.
      RepositionCharacters();
      RepositionCursor();
      RepositionCharacterInfo();

      // Remove all skill text boxes, then create new ones for the
      // focused character.
      for(auto& skillTextBox : mSkillTextBoxes)
      {
        auto skillTextBoxObject = skillTextBox->GetParent();
        if(skillTextBoxObject != nullptr)
        {
          skillTextBoxObject->ScheduleForDeletion();
        }
      }
      mSkillTextBoxes.clear();

      CreateSkillTextBoxes();
    }
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::HandleActionExecuted()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::RepositionCharacters()
{
  auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
  auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
  auto centerHeight = overlayHeight / 2.0;

  auto totalCharacterWidth = mCharacterHorizontalPadding * (mCharacters.size() - 1);
  auto distanceFromLeft = (overlayWidth - totalCharacterWidth) / 2.0;
  for(auto& characterPair : mCharacters)
  {
    characterPair.second->SetPosition(glm::vec3(mCharacters.size() * mCharacterHorizontalPadding,
                                                centerHeight,
                                                0.1));
    auto characterPos = characterPair.second->GetPosition();
    characterPos.x = distanceFromLeft;
    characterPair.second->SetPosition(characterPos);
    distanceFromLeft += mCharacterHorizontalPadding;
  }

  // Move the focused character up slightly.
  if(mFocusedCharacter != nullptr)
  {
    auto focusedPos = mFocusedCharacter->GetPosition();
    focusedPos.y += mCharacterVerticalPadding;
    mFocusedCharacter->SetPosition(focusedPos);
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::RepositionCursor()
{
  if(mFocusedCharacter != nullptr)
  {
    // Move the cursor above the selected character.
    if(mCursor != nullptr)
    {
      auto characterPos = mFocusedCharacter->GetPosition();
      auto characterMesh = mFocusedCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(characterMesh != nullptr)
      {
        characterPos.y += ((characterMesh->GetHeight() * mCharacterScalar) / 2.0);
      }

      characterPos.z += 0.1;
      mCursor->SetPosition(characterPos);
    }
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::UpdateCharacterInfo()
{
  if(mFocusedCharacter != nullptr)
  {
    if(mNameText != nullptr)
    {
      auto characterBehaviorComponent = mFocusedCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        mNameText->SetText(characterBehaviorComponent->GetName());
      }
    }

    if(mStatsText != nullptr)
    {
      auto characterBehaviorComponent = mFocusedCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        std::stringstream statStream;
        statStream << "Max HP: " << characterBehaviorComponent->GetMaximumHealth();
        statStream << " Speed: " << characterBehaviorComponent->GetSpeed();
        mStatsText->SetText(statStream.str());
      }
    }
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::RepositionCharacterInfo()
{
  if(mFocusedCharacter != nullptr)
  {
    // Move the character name and stats text boxes to below the focused character.
    if(mNameText != nullptr)
    {
      auto nameTextParent = mNameText->GetParent();
      if(nameTextParent != nullptr)
      {
        auto characterPos = mFocusedCharacter->GetPosition();
        characterPos.y -= mCharacterNameVerticalPadding;

        auto characterMesh = mFocusedCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
        if(characterMesh != nullptr)
        {
          characterPos.y -= ((characterMesh->GetHeight() * mCharacterScalar) / 2.0);
        }

        nameTextParent->SetPosition(characterPos);
      }
    }

    if(mStatsText != nullptr)
    {
      auto statsTextParent = mStatsText->GetParent();
      if(statsTextParent != nullptr)
      {
        if(mNameText != nullptr)
        {
          auto nameTextParent = mNameText->GetParent();
          if(nameTextParent != nullptr)
          {
            auto nameTextPos = nameTextParent->GetPosition();
            nameTextPos.y -= mCharacterNameVerticalPadding;
            statsTextParent->SetPosition(nameTextPos);
          }
        }
      }
    }
  }
}

/******************************************************************************/
void RewardsMenuLayoutComponent::CreateSkillTextBoxes()
{
  if(mFocusedCharacter != nullptr)
  {
    auto characterBehaviorComponent = mFocusedCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
      auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
      auto centerWidth = overlayWidth / 2.0;
      auto centerHeight = overlayHeight / 2.0;

      int skillTextBoxYCoordinate = centerHeight - (mCharacterBackgroundHeight / 2.0);

      UrsineEngine::Texture backgroundTexture;
      backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");

      for(const auto& skill : characterBehaviorComponent->GetSkills())
      {
        if(skill->GetName() != "Move")
        {
          std::stringstream nameStream;
          nameStream << mFocusedCharacter->GetName() << "_" << skill->GetName();
          auto skillTextBoxObject = CreateTextBoxObject(nameStream.str());
          auto skillTextBox = skillTextBoxObject->GetFirstComponentOfType<TextBoxComponent>();
          skillTextBox->SetTextSize(MEDIUM_FONT_SIZE);
          skillTextBox->SetTexture(backgroundTexture);

          skillTextBox->SetWidth(overlayWidth);
          skillTextBox->SetHeight(mDescriptionHeight);
          skillTextBox->SetFixedWidth(true);
          skillTextBox->SetFixedHeight(true);

          skillTextBox->SetVerticalPadding(mDescriptionVerticalPadding);

          std::stringstream skillTextStream;
          skillTextStream << skill->GetName() << ": " << skill->GetDescription();
          skillTextBox->SetText(skillTextStream.str());

          skillTextBoxObject->SetPosition(glm::vec3(overlayWidth / 2.0,
                                                    skillTextBoxYCoordinate,
                                                    0.1));
          skillTextBoxYCoordinate -= skillTextBox->GetHeight();

          auto parent = GetParent();
          if(parent != nullptr)
          {
            parent->AddChild(std::move(skillTextBoxObject));
            mSkillTextBoxes.emplace_back(parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>());
          }
        }
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> RewardsMenuLayoutComponent::CreateTextBoxObject(const std::string& aName)
{
  auto textObject = std::make_unique<UrsineEngine::GameObject>(aName);
  textObject->AddComponent(std::make_unique<TextBoxComponent>());
  auto textBox = textObject->GetFirstComponentOfType<TextBoxComponent>();
  
  textBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
  textBox->SetTextAlignment(TextAlignment::eCENTER);

  auto textShader = textBox->GetTextShader();
  if(textShader != nullptr)
  {
    textShader->Activate();
    textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
  }

  return std::move(textObject);
}

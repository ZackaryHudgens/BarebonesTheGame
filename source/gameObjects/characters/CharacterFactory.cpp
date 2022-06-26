#include "CharacterFactory.hpp"

#include <sstream>

#include <SpriteComponent.hpp>

#include "EffectListBehaviorComponent.hpp"
#include "HealthBarMeshComponent.hpp"

#include "DefaultCharacterMover.hpp"
#include "DiagonalCharacterMover.hpp"

#include "DefaultCharacterController.hpp"

#include "SkillFactory.hpp"

#include "Colors.hpp"

using Barebones::CharacterFactory;

double Barebones::CharacterFactory::mVerticalPadding = 0.2;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> CharacterFactory::CreateCharacter(const CharacterType& aType,
                                                                            const std::string& aName)
{
  // Create a new GameObject and attach a SpriteComponent and a
  // CharacterBehaviorComponent to it.
  auto newCharacter = std::make_unique<UrsineEngine::GameObject>(aName);
  newCharacter->AddComponent(std::make_unique<UrsineEngine::SpriteComponent>());
  newCharacter->AddComponent(std::make_unique<CharacterBehaviorComponent>());
  
  auto newCharacterBehaviorComponent = newCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto newCharacterSpriteComponent = newCharacter->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();

  // Set up the shader.
  std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);

  defaultShader.Activate();
  defaultShader.SetFloat("fadeValue", 0.0);
  defaultShader.SetVec4("fadeColor", glm::vec4(BACKGROUND_COLOR, 1.0));

  newCharacterSpriteComponent->AddShader("defaultShader", defaultShader);
  newCharacterSpriteComponent->SetCurrentShader("defaultShader");

  switch(aType)
  {
    case CharacterType::eBASIC_SKELETON:
    {
      newCharacterBehaviorComponent->SetName("Skelly");
      newCharacterBehaviorComponent->SetMover(std::make_unique<DiagonalCharacterMover>());
      newCharacterBehaviorComponent->SetMaximumHealth(10);
      newCharacterBehaviorComponent->SetCurrentHealth(10);
      newCharacterBehaviorComponent->SetSide(Side::ePLAYER);
      newCharacterBehaviorComponent->SetType(Type::eSKELETON);
      newCharacterBehaviorComponent->SetSpeed(4);

      newCharacterBehaviorComponent->AddSkill(SkillFactory::CreateSkill(SkillType::eCLAW));

      // Set up the spritesheet and animations.
      UrsineEngine::Texture spritesheet;
      spritesheet.CreateTextureFromFile("resources/sprites/skeletons/basicSkeletonSpritesheet.png");
      newCharacterSpriteComponent->SetTexture(spritesheet);

      newCharacterSpriteComponent->AddAnimation("walking");

      UrsineEngine::TextureClip clip;
      clip.mHeight = 16;
      clip.mWidth = 16;
      clip.mX = 0;
      clip.mY = 0;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      clip.mX = 16;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      newCharacterSpriteComponent->SetAnimation("walking");
      newCharacterSpriteComponent->SetSpeedOfAnimation(3.0);
      break;
    }
    case CharacterType::eBONE_THROWER:
    {
      newCharacterBehaviorComponent->SetName("Bone Thrower");
      newCharacterBehaviorComponent->SetMover(std::make_unique<DefaultCharacterMover>());
      newCharacterBehaviorComponent->SetMaximumHealth(5);
      newCharacterBehaviorComponent->SetCurrentHealth(5);
      newCharacterBehaviorComponent->SetSide(Side::ePLAYER);
      newCharacterBehaviorComponent->SetType(Type::eSKELETON);
      newCharacterBehaviorComponent->SetSpeed(3);

      newCharacterBehaviorComponent->AddSkill(SkillFactory::CreateSkill(SkillType::eBONE_THROW));

      // Set up the spritesheet and animations.
      UrsineEngine::Texture spritesheet;
      spritesheet.CreateTextureFromFile("resources/sprites/skeletons/basicSkeletonSpritesheet.png");
      newCharacterSpriteComponent->SetTexture(spritesheet);

      newCharacterSpriteComponent->AddAnimation("walking");

      UrsineEngine::TextureClip clip;
      clip.mHeight = 16;
      clip.mWidth = 16;
      clip.mX = 0;
      clip.mY = 0;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      clip.mX = 16;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      newCharacterSpriteComponent->SetAnimation("walking");
      newCharacterSpriteComponent->SetSpeedOfAnimation(3.0);
      break;
    }
    case CharacterType::eCORRUPTED_FARMER:
    {
      newCharacterBehaviorComponent->SetName("Corrupted Farmer");
      newCharacterBehaviorComponent->SetMover(std::make_unique<DefaultCharacterMover>());
      newCharacterBehaviorComponent->SetController(std::make_unique<DefaultCharacterController>(*newCharacter));
      newCharacterBehaviorComponent->SetMaximumHealth(5);
      newCharacterBehaviorComponent->SetCurrentHealth(5);
      newCharacterBehaviorComponent->SetSide(Side::eENEMY);
      newCharacterBehaviorComponent->SetType(Type::eHUMAN);
      newCharacterBehaviorComponent->SetSpeed(2);

      newCharacterBehaviorComponent->AddSkill(SkillFactory::CreateSkill(SkillType::eTENTACLE_SLAP));

      // Set up the spritesheet and animations.
      UrsineEngine::Texture spritesheet;
      spritesheet.CreateTextureFromFile("resources/sprites/enemies/basicHuman.png");
      newCharacterSpriteComponent->SetTexture(spritesheet);

      newCharacterSpriteComponent->AddAnimation("walking");

      UrsineEngine::TextureClip clip;
      clip.mHeight = 16;
      clip.mWidth = 16;
      clip.mX = 0;
      clip.mY = 0;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      clip.mX = 16;
      newCharacterSpriteComponent->AddFrameToAnimation("walking", clip);

      newCharacterSpriteComponent->SetAnimation("walking");
      newCharacterSpriteComponent->SetSpeedOfAnimation(3.0);
      break;
    }
    default:
    {
      break;
    }
  }

  // Add a health bar to this character as a child object.
  auto healthBarObject = std::make_unique<UrsineEngine::GameObject>("healthBar");
  auto healthBarMeshComponent = std::make_unique<HealthBarMeshComponent>();

  auto characterBehaviorComponent = newCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    healthBarMeshComponent->SetCharacter(*characterBehaviorComponent);
  }

  healthBarObject->AddComponent(std::move(healthBarMeshComponent));

  // Place the health bar above the character sprite.
  auto healthBarPos = newCharacter->GetPosition();
  auto characterMesh = newCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
  if(characterMesh != nullptr)
  {
    healthBarPos.y += (characterMesh->GetHeight() / 2.0);
    healthBarPos.y += mVerticalPadding;
    healthBarObject->SetPosition(healthBarPos);
  }

  // Add an effect list to this character as a child object.
  auto effectListObject = std::make_unique<UrsineEngine::GameObject>("effectList");
  auto effectListBehaviorComponent = std::make_unique<EffectListBehaviorComponent>();

  if(characterBehaviorComponent != nullptr)
  {
    effectListBehaviorComponent->SetCharacter(*characterBehaviorComponent);
  }

  effectListObject->AddComponent(std::move(effectListBehaviorComponent));

  // Place the effect list above the health bar.
  auto effectListPos = healthBarPos;
  effectListPos.y += mVerticalPadding;
  effectListObject->SetPosition(effectListPos);

  // Finally, add the extra objects to the character.
  newCharacter->AddChild(std::move(healthBarObject));
  newCharacter->AddChild(std::move(effectListObject));

  return std::move(newCharacter);
}

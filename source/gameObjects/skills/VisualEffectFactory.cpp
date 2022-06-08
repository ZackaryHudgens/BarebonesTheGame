#include "VisualEffectFactory.hpp"

#include "BoardLayoutComponent.hpp"

#include "AnimationVisualEffectBehaviorComponent.hpp"
#include "ProjectileVisualEffectBehaviorComponent.hpp"

using Barebones::VisualEffectFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> VisualEffectFactory::CreateVisualEffect(const std::string& aName,
                                                                                  const VisualEffectType& aType,
                                                                                  UrsineEngine::GameObject& aBoard,
                                                                                  const TileLocation& aSourceLocation,
                                                                                  const TileLocation& aTargetLocation)
{
  auto newObject = std::make_unique<UrsineEngine::GameObject>(aName);

  switch(aType)
  {
    case VisualEffectType::eCLAW:
    {
      auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
      if(boardLayoutComponent != nullptr)
      {
        auto character = boardLayoutComponent->GetCharacterAtLocation(aTargetLocation);
        if(character != nullptr)
        {
          std::string spritesheet = "resources/sprites/skills/claw.png";

          // Set up the frame data.
          std::vector<UrsineEngine::TextureClip> clips;
          UrsineEngine::TextureClip clip;
          clip.mHeight = 16;
          clip.mWidth = 16;
          clip.mX = 0;
          clip.mY = 0;
          clips.emplace_back(clip);

          clip.mX = 16;
          clips.emplace_back(clip);

          clip.mX = 32;
          clips.emplace_back(clip);

          newObject->AddComponent(std::make_unique<AnimationVisualEffectBehaviorComponent>(spritesheet,
                                                                                           clips,
                                                                                           15.0));
          newObject->SetPosition(character->GetPosition());
        }
      }

      break;
    }
    case VisualEffectType::eBONE_THROW:
    {
      newObject->SetScale(glm::vec3(0.7, 0.7, 1.0));

      glm::vec3 targetPosition(0.0, 0.0, 0.0);
      auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
      if(boardLayoutComponent != nullptr)
      {
        auto targetCharacter = boardLayoutComponent->GetCharacterAtLocation(aTargetLocation);
        if(targetCharacter != nullptr)
        { 
          targetPosition = targetCharacter->GetPosition();
        }
      }

      // Add a projectile behavior component to the visual effect object.
      newObject->AddComponent(std::make_unique<ProjectileVisualEffectBehaviorComponent>(targetPosition, 0.5));

      // Create a sprite and add it to the visual effect object.
      auto spriteComponent = std::make_unique<UrsineEngine::SpriteComponent>();
      spriteComponent->SetRenderOption(GL_DEPTH_TEST, false);

      UrsineEngine::Texture texture;
      texture.CreateTextureFromFile("resources/sprites/skills/bone.png");
      spriteComponent->SetTexture(texture);

      std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
      std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
      UrsineEngine::Shader shader(vertexFile, fragmentFile);
      spriteComponent->AddShader("default", shader);
      spriteComponent->SetCurrentShader("default");

      newObject->AddComponent(std::move(spriteComponent));

      // Set the visual effect object to start at the source location.
      auto sourceCharacter = boardLayoutComponent->GetCharacterAtLocation(aSourceLocation);
      if(sourceCharacter != nullptr)
      {
        newObject->SetPosition(sourceCharacter->GetPosition());
      }

      break;
    }
    case VisualEffectType::eTENTACLE_SLAP:
    {
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newObject);
};

#include "BoneThrowSkill.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

#include "AnimationVisualEffectBehaviorComponent.hpp"
#include "ProjectileVisualEffectBehaviorComponent.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 2)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> BoneThrowSkill::CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                             const TileLocation& aLocation)
{
  std::unique_ptr<UrsineEngine::GameObject> visualEffect = nullptr;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto targetCharacterObject = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(targetCharacterObject != nullptr)
    {
      // Create an effect in front of the target character.
      std::stringstream nameStream;
      nameStream << "boneVisualEffect_" << aLocation.first << "_" << aLocation.second;
      visualEffect = std::make_unique<UrsineEngine::GameObject>(nameStream.str());

      std::string spritesheet = "resources/sprites/clawEffectSpritesheet.png";

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

      visualEffect->AddComponent(std::make_unique<AnimationVisualEffectBehaviorComponent>(spritesheet,
                                                                                          clips,
                                                                                          1.0));
      visualEffect->AddComponent(std::make_unique<ProjectileVisualEffectBehaviorComponent>(targetCharacterObject->GetPosition(), 0.3));

      auto characterObject = boardLayoutComponent->GetCharacterAtLocation(GetCharacterLocation(aBoard));
      if(characterObject != nullptr)
      {
        visualEffect->SetPosition(characterObject->GetPosition());
      }
    }
  }

  return std::move(visualEffect);
}

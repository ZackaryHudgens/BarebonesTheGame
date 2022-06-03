#include "ClawSkill.hpp"

#include <sstream>

#include "CharacterBehaviorComponent.hpp"
#include "BoardLayoutComponent.hpp"

#include "AnimationVisualEffectBehaviorComponent.hpp"

using Barebones::ClawSkill;

/******************************************************************************/
ClawSkill::ClawSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 1)
{
  SetName("Claw");
  SetDescription("Slashes with bony claws.");
  SetDamage(3);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> ClawSkill::CreateVisualEffect(UrsineEngine::GameObject& aBoard,
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
      nameStream << "clawVisualEffect_" << aLocation.first << "_" << aLocation.second;
      visualEffect = std::make_unique<UrsineEngine::GameObject>(nameStream.str());

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

      visualEffect->AddComponent(std::make_unique<AnimationVisualEffectBehaviorComponent>(spritesheet,
                                                                                          clips,
                                                                                          15.0));
      visualEffect->SetPosition(targetCharacterObject->GetPosition());
    }
  }

  return std::move(visualEffect);
}

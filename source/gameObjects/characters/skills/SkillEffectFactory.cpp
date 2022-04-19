#include "SkillEffectFactory.hpp"

#include "ClawSkillEffectBehaviorComponent.hpp"

using Barebones::SkillEffectFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> SkillEffectFactory::CreateEffect(const SkillType& aType,
                                                                           const std::string& aName)
{
  auto newEffect = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case SkillType::eCLAW:
    {
      newEffect->AddComponent(std::make_unique<ClawSkillEffectBehaviorComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newEffect);
}

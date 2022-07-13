#include "SkillFactory.hpp"

#include "AreaOfEffectSkill.hpp"
#include "SingleTargetSkill.hpp"

#include "VisualEffectFactory.hpp"

#include "DamageAction.hpp"
#include "EffectAction.hpp"

using Barebones::SkillFactory;

/******************************************************************************/
std::unique_ptr<Barebones::Skill> SkillFactory::CreateSkill(const SkillType& aType)
{
  std::unique_ptr<Skill> newSkill = nullptr;

  switch(aType)
  {
    case SkillType::eCLAW:
    {
      auto skill = std::make_unique<SingleTargetSkill>();
      skill->SetName("Claw");
      skill->SetFluffDescription("Rakes the target with bony claws.");
      skill->SetRange(1);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(3);
      skill->AddAction(std::move(damageAction));

      skill->AddVisualEffect(VisualEffectType::eCLAW);

      newSkill = std::move(skill);
      break;
    }
    case SkillType::eBONE_THROW:
    {
      auto skill = std::make_unique<SingleTargetSkill>();
      skill->SetName("Bone Throw");
      skill->SetFluffDescription("Hurls a bone at the target.");
      skill->SetRange(2);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(2);
      skill->AddAction(std::move(damageAction));

      skill->AddVisualEffect(VisualEffectType::eBONE_THROW);

      newSkill = std::move(skill);
      break;
    }
    case SkillType::eTENTACLE_SLAP:
    {
      auto skill = std::make_unique<SingleTargetSkill>();
      skill->SetName("Tentacle Slap");
      skill->SetFluffDescription("Slaps the target with a slimy tentacle.");
      skill->SetRange(1);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(2);
      skill->AddAction(std::move(damageAction));

      auto effectAction = std::make_unique<EffectAction>();
      effectAction->SetEffectType(EffectType::eSLOW);
      skill->AddAction(std::move(effectAction));

      skill->AddVisualEffect(VisualEffectType::eCLAW);

      newSkill = std::move(skill);
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newSkill);
}

#include "SkillFactory.hpp"

#include "SingleTargetSkill.hpp"

#include "DamageAction.hpp"

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
      skill->SetRange(1);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(3);
      skill->AddAction(std::move(damageAction));

      newSkill = std::move(skill);
      break;
    }
    case SkillType::eBONE_THROW:
    {
      auto skill = std::make_unique<SingleTargetSkill>();
      skill->SetRange(2);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(2);
      skill->AddAction(std::move(damageAction));

      newSkill = std::move(skill);
      break;
    }
    case SkillType::eTENTACLE_SLAP:
    {
      auto skill = std::make_unique<SingleTargetSkill>();
      skill->SetRange(1);

      auto damageAction = std::make_unique<DamageAction>();
      damageAction->SetDamage(2);
      skill->AddAction(std::move(damageAction));

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

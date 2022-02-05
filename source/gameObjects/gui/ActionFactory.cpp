#include "ActionFactory.hpp"

#include "SkillActionBehaviorComponent.hpp"

using Barebones::ActionFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> ActionFactory::CreateAction(const ActionType& aType,
                                                                      const std::string& aName)
{
  auto newAction = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case ActionType::eSKILL:
    {
      newAction->AddComponent(std::make_unique<SkillActionBehaviorComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newAction);
}

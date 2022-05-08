#include "MenuFactory.hpp"

#include "SkillMenuInputComponent.hpp"
#include "SkillMenuLayoutComponent.hpp"
#include "SpellMenuInputComponent.hpp"
#include "SpellMenuLayoutComponent.hpp"

using Barebones::MenuFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> MenuFactory::CreateMenu(const MenuType& aType,
                                                                  const std::string& aName)
{
  auto newMenu = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case MenuType::eSKILL:
    {
      newMenu->AddComponent(std::make_unique<SkillMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SkillMenuLayoutComponent>());
      break;
    }
    case MenuType::eSPELL:
    {
      newMenu->AddComponent(std::make_unique<SpellMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SpellMenuLayoutComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return newMenu;
}

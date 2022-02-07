#include "MenuFactory.hpp"

#include "MenuInputComponent.hpp"
#include "SkillMenuLayoutComponent.hpp"

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
      newMenu->AddComponent(std::make_unique<MenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SkillMenuLayoutComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return newMenu;
}

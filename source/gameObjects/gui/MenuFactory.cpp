#include "MenuFactory.hpp"

#include "MenuInputComponent.hpp"
#include "MenuLayoutComponent.hpp"

using Barebones::MenuFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> MenuFactory::CreateMenu(const std::string& aName)
{
  auto newMenu = std::make_unique<UrsineEngine::GameObject>(aName);
  newMenu->AddComponent(std::make_unique<MenuInputComponent>());
  newMenu->AddComponent(std::make_unique<MenuLayoutComponent>());
  return newMenu;
}

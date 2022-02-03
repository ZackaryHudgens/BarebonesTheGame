#include "CharacterMenuBehaviorComponent.hpp"

using Barebones::CharacterMenuBehaviorComponent;

/******************************************************************************/
CharacterMenuBehaviorComponent::CharacterMenuBehaviorComponent()
  : Component()
  , mCharacterName(nullptr)
  , mCharacterHealth(nullptr)
{
  CharacterSelected.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleSelectionChanged(aCharacter);
  });
}

/******************************************************************************/
void CharacterMenuBehaviorComponent::Initialize()
{
  // Create text components and attach them to the parent GameObject.
  auto nameComp = std::make_unique<UrsineEngine::TextComponent>();
  nameComp->LoadFont("resources/Roboto-Regular.ttf");
  nameComp->SetFont("Roboto",
                    "Regular");
  nameComp->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  GetParent()->AddComponent(std::move(nameComp));
  mCharacterName = dynamic_cast<UrsineEngine::TextComponent*>(GetParent()->GetComponents().back());
}

/******************************************************************************/
void CharacterMenuBehaviorComponent::HandleSelectionChanged(CharacterBehaviorComponent& aCharacter)
{
  if(mCharacterName != nullptr)
  {
    if(aCharacter.IsSelected())
    {
      mCharacterName->SetText("woo");
    }
    else
    {
      mCharacterName->SetText("");
    }
  }
}

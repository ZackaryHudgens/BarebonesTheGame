#ifndef CHARACTERMENUBEHAVIORCOMPONENT_HPP
#define CHARACTERMENUBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <TextComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class CharacterMenuBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterMenuBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:

      /**
       * A handler function that gets called whenever the selection
       * status of a character changes.
       *
       * @param aCharacter The character that was selected.
       */
      void HandleSelectionChanged(CharacterBehaviorComponent& aCharacter);

      UrsineEngine::TextComponent* mCharacterName;
      UrsineEngine::TextComponent* mCharacterHealth;
  };
}

#endif

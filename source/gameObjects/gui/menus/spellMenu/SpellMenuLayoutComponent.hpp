#ifndef SPELLMENULAYOUTCOMPONENT_HPP
#define SPELLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include <TextBoxComponent.hpp>

namespace Barebones
{
  class SpellMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      SpellMenuLayoutComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:
      TextBoxComponent* mSpellNameTextBox;
      TextBoxComponent* mSpellDescriptionTextBox;

      int mSpellNameVerticalPadding;
      int mSpellDescriptionVerticalPadding;
      int mSpellNameHeight;
      int mSpellDescriptionHeight;
  };
}

#endif

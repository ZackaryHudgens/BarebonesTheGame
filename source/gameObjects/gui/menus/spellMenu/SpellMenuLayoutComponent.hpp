#ifndef SPELLMENULAYOUTCOMPONENT_HPP
#define SPELLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

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
  };
}

#endif

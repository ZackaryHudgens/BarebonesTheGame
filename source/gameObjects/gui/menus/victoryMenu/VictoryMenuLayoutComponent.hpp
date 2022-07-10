#ifndef VICTORYMENULAYOUTCOMPONENT_HPP
#define VICTORYMENULAYOUTCOMPONENT_HPP

#include "MainMenuLayoutComponent.hpp"

#include "Acts.hpp"

namespace Barebones
{
  class VictoryMenuLayoutComponent : public MainMenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      VictoryMenuLayoutComponent();

      /**
       * Sets the act to load and creates an action to load it.
       *
       * @param aAct The act to load from this menu.
       */
      void SetActToLoad(const Act& aAct);

    protected:

      /**
       * Initializes the component.
       */
      void ProtectedInitialize() override;
  };
}

#endif

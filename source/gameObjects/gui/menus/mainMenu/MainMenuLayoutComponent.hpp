#ifndef MAINMENULAYOUTCOMPONENT_HPP
#define MAINMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class MainMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      MainMenuLayoutComponent();

    protected:

      /**
       * A handler function that gets called whenever an action is added
       * to this menu.
       */
      void HandleActionAdded() override;

      /**
       * A handler function that gets called whenever the currently hovered
       * action changes.
       */
      void HandleActionHovered() override;

      /**
       * A handler function that gets called whenever an action is executed
       * from this menu.
       */
      void HandleActionExecuted() override;

    private:
      std::vector<TextBoxComponent*> mTextBoxes;
      TextBoxComponent* mHoveredTextBox;

      int mVerticalPadding;
  };
}

#endif

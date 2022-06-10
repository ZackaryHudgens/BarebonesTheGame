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
       * Initializes the component.
       */
      void ProtectedInitialize() override;

      /**
       * A handler function that gets called whenever the hidden status of
       * this menu changes.
       *
       * @param aHidden The new hidden status of the menu.
       */
      void HandleHiddenStatusChanged(bool aHidden) override;

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
       * A handler function that gets called whenever an action in this menu
       * is enabled or disabled.
       *
       * @param aAction The action that changed.
       */
      void HandleActionEnabledChanged(MenuAction& aAction) override;

    private:
      UrsineEngine::GameObject* mCursor;

      std::vector<TextBoxComponent*> mTextBoxes;
      TextBoxComponent* mHoveredTextBox;

      int mVerticalPadding;
      int mHorizontalPadding;
      int mTextboxHeight;
      int mTextBoxWidth;

      int mCursorHorizontalPadding;
  };
}

#endif

#ifndef BASICMENULAYOUTCOMPONENT_HPP
#define BASICMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class BasicMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicMenuLayoutComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

    protected:

      /**
       * A handler function that gets called whenever an action is added
       * to this menu.
       *
       * @param aAction The action that was added.
       */
      void HandleActionAdded(MenuAction& aAction) override;

      /**
       * A handler function that gets called whenever the currently hovered
       * action changes.
       *
       * @param aAction The action that was hovered.
       */
      void HandleActionHovered(MenuAction& aAction) override;

      /**
       * A handler function that gets called whenever an action in this menu
       * is enabled or disabled.
       *
       * @param aAction The action that changed.
       */
      void HandleActionEnabledChanged(MenuAction& aAction) override;

    private:

      /**
       * Repositions each text box to be centered horizontally and vertically.
       */
      void RepositionTextBoxes();

      /**
       * Repositions the cursor to be to the left of the currently
       * hovered action.
       *
       * @param aAction The currently hovered action.
       */
      void RepositionCursor(MenuAction& aAction);

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

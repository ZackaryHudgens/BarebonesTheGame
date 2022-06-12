#ifndef SKILLMENULAYOUTCOMPONENT_HPP
#define SKILLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include "Skill.hpp"
#include "TextBoxComponent.hpp"

namespace Barebones
{
  class SkillMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      SkillMenuLayoutComponent();

    protected:

      /**
       * Initializes the component.
       */
      void ProtectedInitialize() override;

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

      /**
       * Updates the cursor positions based on the text in mSkillNameTextBox.
       * Also changes their color if the user can't move in that direction.
       */
      void UpdateCursors();

      TextBoxComponent* mSkillNameTextBox;
      TextBoxComponent* mSkillDescriptionTextBox;

      UrsineEngine::GameObject* mLeftCursor;
      UrsineEngine::GameObject* mRightCursor;

      int mSkillNameHeight;
      int mSkillNameVerticalPadding;

      int mSkillDescriptionHeight;
      int mSkillDescriptionVerticalPadding;
  };
}

#endif

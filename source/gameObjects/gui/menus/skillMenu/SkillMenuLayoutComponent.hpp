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
      TextBoxComponent* mSkillNameTextBox;
      TextBoxComponent* mSkillDescriptionTextBox;

      int mSkillNameHeight;
      int mSkillNameVerticalPadding;

      int mSkillDescriptionHeight;
      int mSkillDescriptionVerticalPadding;
  };
}

#endif

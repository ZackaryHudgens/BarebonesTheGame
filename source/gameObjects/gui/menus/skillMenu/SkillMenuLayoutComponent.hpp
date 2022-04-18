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

      /**
       * Initializes the component.
       */
      void Initialize() override;

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
       * A handler function that gets called whenever an action is selected
       * from this menu.
       */
      void HandleActionSelected() override;

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

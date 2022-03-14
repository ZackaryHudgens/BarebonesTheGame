#ifndef SKILLMENULAYOUTCOMPONENT_HPP
#define SKILLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include <Signal.hpp>
#include <TextComponent.hpp>

#include "Skill.hpp"

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

      /**
       * Updates the component.
       */
      void Update() override;

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
      UrsineEngine::TextComponent* mSkillNameText;
      UrsineEngine::TextComponent* mSkillDescriptionText;

      double mIconSpacing;
  };

  typedef UrsineEngine::SignalT<Skill*> SkillSelectedFromMenuSignal;

  extern SkillSelectedFromMenuSignal SkillSelectedFromMenu;
}

#endif

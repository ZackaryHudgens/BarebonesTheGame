#ifndef SKILLMENULAYOUTCOMPONENT_HPP
#define SKILLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

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
       * A handler function that gets called whenever an action is selected
       * from this menu.
       */
      void HandleActionSelected() override;

    private:
      double mIconSpacing;

      glm::vec3 mTargetPosition;
      double mSpeed;
      bool mMoving;
  };
}

#endif

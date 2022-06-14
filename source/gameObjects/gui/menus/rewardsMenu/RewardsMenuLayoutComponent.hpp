#ifndef REWARDSMENULAYOUTCOMPONENT_HPP
#define REWARDSMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include <GameObject.hpp>

namespace Barebones
{
  class RewardsMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      RewardsMenuLayoutComponent();

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

    private:

      /**
       * Repositions all characters in the character map.
       */
      void RepositionCharacters();

      UrsineEngine::GameObject* mCursor;

      typedef std::pair<MenuAction*, UrsineEngine::GameObject*> CharacterActionPair;
      std::vector<CharacterActionPair> mCharacters;

      double mCharacterScalar;

      int mTitleHeight;
      int mTitleVerticalPadding;
      int mDescriptionHeight;
      int mDescriptionVerticalPadding;

      int mCharacterBackgroundHeight;

      int mCharacterHorizontalSpacing;
  };
}

#endif

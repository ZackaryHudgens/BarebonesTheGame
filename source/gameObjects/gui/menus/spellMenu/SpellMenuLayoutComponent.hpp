#ifndef SPELLMENULAYOUTCOMPONENT_HPP
#define SPELLMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include <SpriteComponent.hpp>
#include <TextBoxComponent.hpp>

namespace Barebones
{
  class SpellMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      SpellMenuLayoutComponent();

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
      UrsineEngine::SpriteComponent* mSpellbookSprite;
      TextBoxComponent* mSpellNameTextBox;
      TextBoxComponent* mSpellDescriptionTextBox;

      UrsineEngine::TextureClip mFirstSpellClip;
      UrsineEngine::TextureClip mLastSpellClip;
      UrsineEngine::TextureClip mCenterSpellClip;

      double mSpellbookScalar;
      int mSpellbookVerticalOffset;

      int mSpellNameHeight;
      int mSpellNameWidth;
      int mSpellNameVerticalPadding;
      int mSpellNameHorizontalOffset;
      int mSpellNameVerticalOffset;
      int mSpellDescriptionHeight;
      int mSpellDescriptionWidth;
      int mSpellDescriptionVerticalPadding;
      int mSpellDescriptionHorizontalOffset;
      int mSpellDescriptionVerticalOffset;
  };
}

#endif

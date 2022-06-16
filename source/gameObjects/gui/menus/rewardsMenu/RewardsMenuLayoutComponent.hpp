#ifndef REWARDSMENULAYOUTCOMPONENT_HPP
#define REWARDSMENULAYOUTCOMPONENT_HPP

#include "MenuLayoutComponent.hpp"

#include <GameObject.hpp>

#include "CharacterFactory.hpp"

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class RewardsMenuLayoutComponent : public MenuLayoutComponent
  {
    public:

      /**
       * Constructor.
       */
      RewardsMenuLayoutComponent();

      /**
       * Creates an action for the given character type.
       *
       * @param aType The type of character.
       */
      void CreateActionForCharacterType(const CharacterType& aType);

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
       * Repositions all characters in the character map.
       */
      void RepositionCharacters();

      /**
       * Repositions the cursor above the focused character.
       */
      void RepositionCursor();

      /**
       * Repositions the character name and stats text to be
       * under the focused character.
       */
      void RepositionCharacterInfo();

      /**
       * Updates the character name and stats text to reflect the
       * currently focused character.
       */
      void UpdateCharacterInfo();

      /**
       * Creates a text box for each skill on the focused character
       * (except the Move skill).
       */
      void CreateSkillTextBoxes();

      /**
       * Creates a GameObject with a TextBoxComponent, then returns it as
       * a unique_ptr.
       *
       * @param aName The name of the new GameObject.
       * @return A GameObject with a unique_ptr.
       */
      std::unique_ptr<UrsineEngine::GameObject> CreateTextBoxObject(const std::string& aName);

      UrsineEngine::GameObject* mCursor;

      TextBoxComponent* mNameText;
      TextBoxComponent* mStatsText;
      std::vector<TextBoxComponent*> mSkillTextBoxes;

      typedef std::pair<MenuAction*, UrsineEngine::GameObject*> CharacterActionPair;
      std::vector<CharacterActionPair> mCharacters;
      UrsineEngine::GameObject* mFocusedCharacter;

      double mCharacterScalar;

      int mTitleHeight;
      int mTitleVerticalPadding;
      int mDescriptionHeight;
      int mDescriptionVerticalPadding;

      int mCharacterBackgroundHeight;
      int mCharacterVerticalPadding;
      int mCharacterHorizontalPadding;

      int mCharacterNameVerticalPadding;
  };
}

#endif

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
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Creates an action for the given character type.
       *
       * @param aType The type of character.
       */
      void CreateActionForCharacterType(const CharacterType& aType);

      /**
       * Sets whether this menu should warn the user that selecting
       * a character means they will need to get rid of a character
       * on the board.
       *
       * @param aShowWarning Whether to display the warning.
       */
      void SetShowMaxSizeWarning(bool aShowWarning);

    protected:

      /**
       * A virtual function that gets called whenever the currently hovered
       * action changes.
       *
       * @param aAction The action that was hovered.
       */
      void HandleActionHovered(MenuAction& aAction) override;

      /**
       * A virtual function that gets called whenever an action is executed
       * from this menu.
       *
       * @param aAction The action that was executed.
       */
      void HandleActionExecuted(MenuAction& aAction) override;

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

      bool mShowWarning;

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

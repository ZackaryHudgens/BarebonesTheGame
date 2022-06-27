#ifndef INFOPANELBEHAVIORCOMPONENT_HPP
#define INFOPANELBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class InfoPanelBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      InfoPanelBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Associates this component with a board GameObject.
       *
       * @param aBoard The board to look up characters on.
       */
      void SetFollowedBoard(UrsineEngine::GameObject& aBoard) { mBoard = &aBoard; }

    private:

      /**
       * A handler function that gets called whenever a board's focused
       * tile changes.
       *
       * @param aBoard The board that updated.
       */
      void HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard);

      /**
       * A handler function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       */
      void HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character finishes moving.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character's health changes.
       *
       * @param aCharacter The character whose health changed.
       */
      void HandleCharacterHealthChanged(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character dies.
       *
       * @param aCharacter The character that died.
       */
      void HandleCharacterDied(CharacterBehaviorComponent& aCharacter);

      /**
       * Updates the text based on the focused location on the followed board.
       */
      void UpdateText();

      UrsineEngine::GameObject* mBoard;

      TextBoxComponent* mTextBox;

      TileLocation mFocusedLocation;

      double mTextBoxHeight;
      double mTextBoxVerticalPadding;
  };
}

#endif

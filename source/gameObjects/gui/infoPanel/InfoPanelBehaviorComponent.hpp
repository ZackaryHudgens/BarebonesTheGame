#ifndef INFOPANELBEHAVIORCOMPONENT_HPP
#define INFOPANELBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

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
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a human player changes
       * location.
       *
       * @param aPlayer The player whose location changed.
       */
      void HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer);

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

      UrsineEngine::GameObject* mBoard;

      TextBoxComponent* mTextBox;

      TileLocation mFocusedLocation;

      double mTextBoxHeight;
      double mTextBoxHorizontalPadding;
      double mTextBoxVerticalPadding;
  };
}

#endif

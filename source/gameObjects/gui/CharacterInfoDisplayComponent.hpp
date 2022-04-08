#ifndef CHARACTERINFODISPLAYCOMPONENT_HPP
#define CHARACTERINFODISPLAYCOMPONENT_HPP

#include <Component.hpp>

#include "HumanPlayerBehaviorComponent.hpp"

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class CharacterInfoDisplayComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterInfoDisplayComponent();

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

      UrsineEngine::GameObject* mBoard;

      TextBoxComponent* mTextBox;

      double mTextBoxHeight;
      double mTextBoxHorizontalPadding;
      double mTextBoxVerticalPadding;
  };
}

#endif

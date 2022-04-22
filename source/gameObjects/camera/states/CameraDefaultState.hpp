#ifndef CAMERADEFAULTSTATE_HPP
#define CAMERADEFAULTSTATE_HPP

#include "CameraState.hpp"

namespace Barebones
{
  class CameraDefaultState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraDefaultState(UrsineEngine::GameObject& aCamera);

      /**
       * A handler function that gets called whenever the parent camera
       * starts following a new board object.
       *
       * @param aBoard The newly-followed board object.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleBoardFollowed(UrsineEngine::GameObject& aBoard) override;

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer) override;

      /**
       * A handler function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter) override;

      /**
       * A handler function that gets called whenever a skill is selected from
       * a menu.
       *
       * @param aSkill The skill that was selected.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleSkillSelectedFromMenu(Skill& aSkill) override;
  };
}

#endif

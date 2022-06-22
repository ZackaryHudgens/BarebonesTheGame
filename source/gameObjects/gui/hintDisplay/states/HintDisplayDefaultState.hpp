#ifndef HINTDISPLAYDEFAULTSTATE_HPP
#define HINTDISPLAYDEFAULTSTATE_HPP

#include "HintDisplayState.hpp"

#include <GameObject.hpp>

namespace Barebones
{
  class HintDisplayDefaultState : public HintDisplayState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject that owns this state.
       */
      HintDisplayDefaultState(UrsineEngine::GameObject& aParent);

      /**
       * Gets called by the hint display when it enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called by the hint display when it exits this state.
       */
      void OnExit() override;

    private:

      /**
       * Creates and places the pause icon and text.
       */
      void CreatePauseIconAndText();

      /**
       * Creates and places WASD/UDLR icons and movement text.
       */
      void CreateMovementIconsAndText();

      /**
       * Creates and places the select keyboard icon and text.
       */
      void CreateSelectIconAndText();

      /**
       * Creates and places the camera icon and keyboard hint icon.
       */
      void CreateCameraIcons();

      std::vector<UrsineEngine::GameObject*> mElements;

      UrsineEngine::GameObject* mCameraIcon;

      int mElementPadding;
      double mIconScale;
  };
}

#endif

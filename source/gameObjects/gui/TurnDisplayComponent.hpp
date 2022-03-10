#ifndef TURNDISPLAYCOMPONENT_HPP
#define TURNDISPLAYCOMPONENT_HPP

#include <Component.hpp>
#include <Signal.hpp>
#include <TextComponent.hpp>

namespace Barebones
{
  class TurnDisplayComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      TurnDisplayComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

      /**
       * Displays a "turn began" message for the given player.
       *
       * @param aPlayer The player whose turn began.
       */
      void DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer);

    private:
      UrsineEngine::TextComponent* mNameText;
      UrsineEngine::MeshComponent* mBackground;

      double mDisplayTime;
      double mInitialDisplayTime;

      bool mDisplaying;
  };

  typedef UrsineEngine::SignalT<TurnDisplayComponent&> TurnDisplayFinishedSignal;
  extern TurnDisplayFinishedSignal TurnDisplayFinished;
}

#endif

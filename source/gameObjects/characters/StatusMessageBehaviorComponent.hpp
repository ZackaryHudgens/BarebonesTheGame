#ifndef STATUSMESSAGEBEHAVIORCOMPONENT_HPP
#define STATUSMESSAGEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <TextComponent.hpp>

namespace Barebones
{
  class StatusMessageBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      StatusMessageBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

    private:
      UrsineEngine::TextComponent* mTextComponent;
  };
}

#endif

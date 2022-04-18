#ifndef CLAWSKILLEFFECTBEHAVIORCOMPONENT_HPP
#define CLAWSKILLEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

namespace Barebones
{
  class ClawSkillEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ClawSkillEffectBehaviorComponent();

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
      double mDisplayTime;
      double mTimeInitialized;
  };
}

#endif

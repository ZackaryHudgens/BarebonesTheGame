#ifndef BACKGROUNDMESHCOMPONENT_HPP
#define BACKGROUNDMESHCOMPONENT_HPP

#include <MeshComponent.hpp>

namespace Barebones
{
  class BackgroundMeshComponent : public UrsineEngine::MeshComponent
  {
    public:

      /**
       * Constructor.
       */
      BackgroundMeshComponent();

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:
      double mHorizontalRepetition;
      double mVerticalRepetition;

      double mHorizontalScrollSpeed;
      double mVerticalScrollSpeed;
  };
}

#endif

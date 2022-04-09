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
       */
      void Update() override;

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

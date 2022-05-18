#ifndef SCENEFACTORY_HPP
#define SCENEFACTORY_HPP

#include <Scene.hpp>

namespace Barebones
{
  enum class SceneType
  {
    eMAIN_MENU,
    eBOARD
  };

  class SceneFactory
  {
    public:

      /**
       * Creates a scene based on the given type and returns it as a
       * std::unique_ptr.
       *
       * @param aType The type of scene to create.
       */
      static std::unique_ptr<UrsineEngine::Scene> CreateScene(const SceneType& aType);
  };
}

#endif

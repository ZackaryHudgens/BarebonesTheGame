#ifndef SCENEFACTORY_HPP
#define SCENEFACTORY_HPP

#include <Scene.hpp>

#include "Acts.hpp"

namespace Barebones
{
  enum class SceneType
  {
    eMAIN_MENU,
    eBOARD_ACT_ONE,
    eBOARD_ACT_TWO,
    eBOARD_ACT_THREE,
    eBOARD_FINALE
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

    private:

      /**
       * Adds all the necessary GameObjects to the given scene to make
       * a playable board scene.
       *
       * @param aScene The scene to make playable.
       * @param aAct The act to use.
       */
      static void AddBoardToScene(UrsineEngine::Scene& aScene,
                                  const Act& aAct);
  };
}

#endif

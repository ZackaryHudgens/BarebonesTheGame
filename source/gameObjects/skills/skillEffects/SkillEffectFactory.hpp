#ifndef SKILLEFFECTFACTORY_HPP
#define SKILLEFFECTFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class SkillType
  {
    eCLAW
  };

  class SkillEffectFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of skill given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of skill effect to create.
       * @param aName The name of the new effect.
       * @return A unique pointer to a new game object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateEffect(const SkillType& aType,
                                                                    const std::string& aName);
  };
}

#endif

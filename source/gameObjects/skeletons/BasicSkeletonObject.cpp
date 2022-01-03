#include "BasicSkeletonObject.hpp"

#include "BasicSkeletonSpriteComponent.hpp"

using Barebones::BasicSkeletonObject;

/******************************************************************************/
BasicSkeletonObject::BasicSkeletonObject(const std::string& aName)
  : SkeletonObject(aName)
{
  AddComponent(std::make_unique<BasicSkeletonSpriteComponent>());
}

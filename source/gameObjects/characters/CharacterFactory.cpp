#include "CharacterFactory.hpp"

#include "BasicSkeletonBehaviorComponent.hpp"
#include "BasicSkeletonSpriteComponent.hpp"

using Barebones::CharacterFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> CharacterFactory::CreateCharacter(const CharacterType& aType,
                                                                            const std::string& aName)
{
  auto newCharacter = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case CharacterType::eBASIC_SKELETON:
    {
      newCharacter->AddComponent(std::make_unique<BasicSkeletonSpriteComponent>());
      newCharacter->AddComponent(std::make_unique<BasicSkeletonBehaviorComponent>());
      newCharacter->Load();
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newCharacter);
}

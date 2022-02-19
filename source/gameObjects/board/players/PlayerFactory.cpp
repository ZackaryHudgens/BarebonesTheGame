#include "PlayerFactory.hpp"

#include "HumanPlayerBehaviorComponent.hpp"
#include "HumanPlayerInputComponent.hpp"

using Barebones::PlayerFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> PlayerFactory::CreatePlayer(const PlayerType& aType,
                                                                      const std::string& aName)
{
  auto newPlayer = std::make_unique<UrsineEngine::GameObject>(aName);

  switch(aType)
  {
    case PlayerType::eARTIFICIAL:
    {
      break;
    }
    case PlayerType::eHUMAN:
    {
      newPlayer->AddComponent(std::make_unique<HumanPlayerBehaviorComponent>());
      newPlayer->AddComponent(std::make_unique<HumanPlayerInputComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return newPlayer;
};

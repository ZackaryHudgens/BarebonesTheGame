#include "TileFactory.hpp"

#include "DefaultTileBehaviorComponent.hpp"
#include "DefaultTileMeshComponent.hpp"
#include "DesecratedTileBehaviorComponent.hpp"
#include "DesecratedTileMeshComponent.hpp"

using Barebones::TileFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> TileFactory::CreateTile(const TileType& aType,
                                                                  const std::string& aName)
{
  auto newTile = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case TileType::eDEFAULT:
    {
      newTile->AddComponent(std::make_unique<DefaultTileBehaviorComponent>());
      newTile->AddComponent(std::make_unique<DefaultTileMeshComponent>());
      break;
    }
    case TileType::eDESECRATED:
    {
      newTile->AddComponent(std::make_unique<DesecratedTileBehaviorComponent>());
      newTile->AddComponent(std::make_unique<DesecratedTileMeshComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newTile);
}

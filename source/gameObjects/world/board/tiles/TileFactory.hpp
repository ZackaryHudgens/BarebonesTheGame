#ifndef TILEFACTORY_HPP
#define TILEFACTORY_HPP

#include <GameObject.hpp>

namespace Barebones
{
  enum class TileType
  {
    eDEFAULT,
    eDESECRATED
  };

  class TileFactory
  {
    public:

      /**
       * Creates a GameObject and adds the proper components
       * based on the type of tile given, then returns it as
       * a std::unique_ptr.
       *
       * @param aType The type of tile to create.
       * @param aName The name of the new tile.
       * @return A unique pointer to a new tile object.
       */
      static std::unique_ptr<UrsineEngine::GameObject> CreateTile(const TileType& aType,
                                                                  const std::string& aName);
  };
}

#endif

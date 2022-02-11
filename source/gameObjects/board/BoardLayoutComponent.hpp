#ifndef BOARDLAYOUTCOMPONENT_HPP
#define BOARDLAYOUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  typedef std::pair<int, int> TileLocation;
  typedef std::vector<TileLocation> TileList;

  class BoardLayoutComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardLayoutComponent();

      /**
       * When initializing, creates a number of TileObjects according to the
       * board's row and column count.
       */
      void Initialize() override;

      /**
       * Adds a character to the board at the given location by taking
       * ownership of it and adding it as a child GameObject.
       *
       * @param aObject The character to add.
       * @param aLocation The location to add the character to.
       * @return True if successful, false otherwise.
       */
      bool AddCharacterAtLocation(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                  const TileLocation& aLocation);

      /**
       * Removes a character at the given location.
       *
       * @param aLocation The location to remove a character from.
       */
      void RemoveCharacterAtLocation(const TileLocation& aLocation);

      /**
       * Returns a pointer to the tile on the board at a given location.
       *
       * @param aLocation The location to access.
       * @return A pointer to a GameObject, or nullptr if the given location
       *         is out of bounds.
       */
      UrsineEngine::GameObject* GetTileAtLocation(const TileLocation& aLocation);

      /**
       * Returns a pointer to the character on the board at a given location.
       *
       * @param aLocation The location to access.
       * @return A pointer to a GameObject, or nullptr if no character
       *         is occupying the given space.
       */
      UrsineEngine::GameObject* GetCharacterAtLocation(const TileLocation& aLocation);

      /**
       * Moves a character at the first location to the second location.
       *
       * @param aCurrentLocation The current location of the character.
       * @param aNewLocation The new location for the character.
       */
      void MoveCharacter(const TileLocation& aCurrentLocation,
                         const TileLocation& aNewLocation);

      /**
       * Returns the location of the character with the given name, or
       * (-1, -1) if there is no character with the given name.
       *
       * @param aName The name of the GameObject for the desired character.
       * @return The location of the corresponding character, or (-1, -1)
       *         if no character was found.
       */
      TileLocation GetLocationOfCharacter(const std::string& aName);

    private:
      std::vector<std::vector<UrsineEngine::GameObject*>> mTiles;
      std::vector<std::vector<UrsineEngine::GameObject*>> mCharacters;

      double mTileSpacing;

      int mColumns;
      int mRows;
  };
}

#endif

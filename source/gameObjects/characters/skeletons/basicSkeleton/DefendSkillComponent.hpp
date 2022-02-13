#ifndef DEFENDSKILLCOMPONENT_HPP
#define DEFENDSKILLCOMPONENT_HPP

#include "CharacterSkillComponent.hpp"

namespace Barebones
{
  class DefendSkillComponent : public CharacterSkillComponent
  {
    public:

      /**
       * Constructor.
       */
      DefendSkillComponent();

      /**
       * Returns a MeshComponent to be used as an icon for this skill.
       *
       * @return A MeshComponent to be used as an icon.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() override;

      /**
       * Returns a list of tiles to highlight when using this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       * @param aLocation The reference position.
       * @return A list of tiles to highlight.
       */
      TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                   const TileLocation& aLocation) override;

      /**
       * Returns true if the given position is valid for using this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       * @param aLocation The reference position.
       * @return True if the given position is valid, false otherwise.
       */
      bool IsTileValid(UrsineEngine::GameObject& aBoard,
                       const TileLocation& aLocation) override;

    protected:

      /**
       * A handler function that gets called whenever the user selects
       * this skill.
       */
      void ProtectedSelect() override;

      /**
       * A handler function that gets called whenever the user executes
       * this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;
  };
}

#endif

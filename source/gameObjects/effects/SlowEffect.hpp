#ifndef SLOWEFFECT_HPP
#define SLOWEFFECT_HPP

#include "Effect.hpp"

namespace Barebones
{
  class SlowEffect : public Effect
  {
    public:

      /**
       * Constructor.
       */
      SlowEffect();

      /**
       * Returns an icon for this effect as a MeshComponent.
       *
       * @return An icon mesh for this effect.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() const override;

      /**
       * A handler function that gets called whenever this effect is
       * added to a character.
       *
       * @param aCharacter The character this effect was added to.
       */
      void HandleAddedToCharacter(CharacterBehaviorComponent& aCharacter) override;

      /**
       * A handler function that gets called whenever this effect is
       * removed from a character.
       *
       * @param aCharacter The character this effect was removed from.
       */
      void HandleRemovedFromCharacter(CharacterBehaviorComponent& aCharacter) override;

    private:
      int mCharacterSpeed;
  };
}

#endif

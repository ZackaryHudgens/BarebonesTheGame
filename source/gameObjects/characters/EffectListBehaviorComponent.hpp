#ifndef EFFECTLISTBEHAVIORCOMPONENT_HPP
#define EFFECTLISTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class EffectListBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      EffectListBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Sets the character to display health for.
       *
       * @param aCharacter The character to display health for.
       */
      void SetCharacter(CharacterBehaviorComponent& aCharacter);

    private:

      /**
       * A handler function that gets called whenever an effect is added
       * to a character.
       *
       * @param aCharacter The character that received an effect.
       * @param aEffect The effect that was added.
       */
      void HandleEffectAddedToCharacter(CharacterBehaviorComponent& aCharacter,
                                        Effect& aEffect);

      /**
       * A handler function that gets called whenever an effect is removed
       * from a character.
       *
       * @param aCharacter The character that lost an effect.
       * @param aEffect The effect that was removed.
       */
      void HandleEffectRemovedFromCharacter(CharacterBehaviorComponent& aCharacter,
                                            Effect& aEffect);

      /**
       * Repositions the icons in the list.
       */
      void RepositionIcons();

      std::vector<UrsineEngine::GameObject*> mIcons;

      CharacterBehaviorComponent* mCharacter;

      int mIconsPerRow;
      double mHorizontalPadding;
      double mVerticalPadding;
      double mIconScale;
  };
}

#endif

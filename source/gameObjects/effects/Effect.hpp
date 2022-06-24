#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <GameObject.hpp>

#include <MeshComponent.hpp>

namespace Barebones
{
  class CharacterBehaviorComponent;

  class Effect
  {
    public:

      /**
       * Constructor.
       */
      Effect();
      virtual ~Effect() {}

      /**
       * Returns the name of this effect.
       *
       * @return The name of this effect.
       */
      std::string GetName() const { return mName; }

      /**
       * Returns the description of this effect.
       *
       * @return The description of this effect.
       */
      std::string GetDescription() const { return mDescription; }

      /**
       * Returns the status message for this effect.
       *
       * @return The status message for this effect.
       */
      std::string GetStatusMessage() const { return mStatusMessage; }

      /**
       * A virtual function that returns an icon for this effect as
       * a MeshComponent.
       *
       * @return An icon mesh for this effect.
       */
      virtual std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() const { return nullptr; }

      /**
       * A virtual function that gets called whenever this effect is
       * added to a character.
       *
       * @param aCharacter The character this effect was added to.
       */
      virtual void HandleAddedToCharacter(CharacterBehaviorComponent& aCharacter) {}

      /**
       * A virtual function that gets called whenever this effect is
       * removed from a character.
       *
       * @param aCharacter The character this effect was removed from.
       */
      virtual void HandleRemovedFromCharacter(CharacterBehaviorComponent& aCharacter) {}

    protected:

      /**
       * Sets the name of this effect.
       *
       * @param aName The name of this effect.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Sets the description of this effect.
       *
       * @param aDescription The description of this effect.
       */
      void SetDescription(const std::string& aDescription) { mDescription = aDescription; }

      /**
       * Sets the status message for this effect.
       *
       * @param aMessage The status message for this effect.
       */
      void SetStatusMessage(const std::string& aMessage) { mStatusMessage = aMessage; }

    private:
      std::string mName;
      std::string mDescription;
      std::string mStatusMessage;
  };
}

#endif

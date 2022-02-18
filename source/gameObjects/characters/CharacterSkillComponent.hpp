#ifndef CHARACTERSKILLCOMPONENT_HPP
#define CHARACTERSKILLCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>
#include <MeshComponent.hpp>

#include "BoardLayoutComponent.hpp"

namespace Barebones
{
  class CharacterSkillComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterSkillComponent();

      /**
       * Selects this skill for execution.
       */
      void Select();

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation);

      /**
       * A virtual function that returns a MeshComponent to be used as an icon
       * for this skill. Inheriting skills should override this to provide
       * their own icons.
       *
       * @return A MeshComponent to be used as an icon.
       */
      virtual std::unique_ptr<UrsineEngine::MeshComponent> GetIcon();

      /**
       * A virtual function that returns true if the given position is a
       * valid position for using this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       * @param aLocation The reference position.
       * @return True if the given position is valid, false otherwise.
       */
      virtual bool IsTileValid(UrsineEngine::GameObject& aBoard,
                               const TileLocation& aLocation) { return true; }

      /**
       * Sets the name of the skill.
       *
       * @param aName The name of the skill.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Sets the description of the skill.
       *
       * @param aDescription The description of the skill.
       */
      void SetDescription(const std::string& aDescription) { mDescription = aDescription; }

      /**
       * Returns the name of the skill.
       *
       * @return The name of the skill.
       */
      std::string GetName() const { return mName; }

      /**
       * Returns the description of the skill.
       *
       * @return The description of the skill.
       */
      std::string GetDescription() const { return mDescription; }

      /**
       * Returns the color to use when highlighting tiles for this skill.
       *
       * @return The color to use when highlighting tiles for this skill.
       */
      glm::vec3 GetHighlightColor() const { return mHighlightColor; }

    protected:

      /**
       * A virtual function that gets called whenever the user selects
       * this skill. Inheriting skills should override this function
       * to provide the desired behavior.
       */
      virtual void ProtectedSelect() {};

      /**
       * A virtual function that gets called whenever the user executes
       * this skill. Inheriting skills should override this function
       * to provide the desired behavior.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                    const TileLocation& aLocation) {};

      /**
       * Sets the color to use when highlighting tiles for this skill.
       *
       * @param aColor The color to use when highlighting tiles for this skill.
       */
      void SetHighlightColor(const glm::vec3& aColor) { mHighlightColor = aColor; }

    private:
      glm::vec3 mHighlightColor;

      std::string mDescription;
      std::string mName;
  };

  typedef UrsineEngine::SignalT<CharacterSkillComponent&> SkillSelectedSignal;
  typedef UrsineEngine::SignalT<CharacterSkillComponent&> SkillExecutedSignal;

  extern SkillSelectedSignal SkillSelected;
  extern SkillExecutedSignal SkillExecuted;
}

#endif

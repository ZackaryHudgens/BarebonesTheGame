#ifndef CHARACTERSKILLCOMPONENT_HPP
#define CHARACTERSKILLCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>
#include <MeshComponent.hpp>

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
       */
      void Execute();

      /**
       * A virtual function that returns a MeshComponent to be used as an icon
       * for this skill. Inheriting skills should override this to provide
       * their own icons.
       *
       * @return A MeshComponent to be used as an icon.
       */
      virtual std::unique_ptr<UrsineEngine::MeshComponent> GetIcon();

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
       */
      virtual void ProtectedExecute() {};

    private:
      std::string mDescription;
      std::string mName;
  };

  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> SkillSelectedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> SkillExecutedSignal;

  extern SkillSelectedSignal SkillSelected;
  extern SkillExecutedSignal SkillExecuted;
}

#endif

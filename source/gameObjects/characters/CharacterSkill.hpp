#ifndef CHARACTERSKILL_HPP
#define CHARACTERSKILL_HPP

#include <string>

namespace Barebones
{
  class CharacterSkill
  {
    public:

      /**
       * Constructor.
       */
      CharacterSkill();

      /**
       * A virtual function that gets called whenever the user selects
       * this skill. Inheriting skills should override this function
       * to provide the desired behavior.
       */
      virtual void Select() = 0;

      /**
       * A virtual function that gets called whenever the user executes
       * this skill. Inheriting skills should override this function
       * to provide the desired behavior.
       */
      virtual void Esecute() = 0;

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

    private:
      std::string mDescription;
      std::string mName;
  };
}

#endif

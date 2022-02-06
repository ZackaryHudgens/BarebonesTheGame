#ifndef MOVESKILLCOMPONENT_HPP
#define MOVESKILLCOMPONENT_HPP

#include "CharacterSkillComponent.hpp"

namespace Barebones
{
  class MoveSkillComponent : public CharacterSkillComponent
  {
    public:

      /**
       * Constructor.
       */
      MoveSkillComponent();

      /**
       * Returns a MeshComponent to be used as an icon for this skill.
       *
       * @return A MeshComponent to be used as an icon.
       */
      std::unique_ptr<UrsineEngine::MeshComponent> GetIcon() override;

    protected:

      /**
       * A handler function that gets called whenever the user selects
       * this skill.
       */
      void ProtectedSelect() override;

      /**
       * A handler function that gets called whenever the user executes
       * this skill.
       */
      void ProtectedExecute() override;
  };
}

#endif

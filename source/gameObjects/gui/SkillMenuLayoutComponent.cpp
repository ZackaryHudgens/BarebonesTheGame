#include "SkillMenuLayoutComponent.hpp"

#include <MeshComponent.hpp>

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mIconSpacing(100.0)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
  int xDistance = 100;
  int index = 1;
  for(auto& action : GetActions())
  {
    action->SetPosition(glm::vec3(xDistance * index,
                                  100.0,
                                  0.0));
    ++index;
  }
}

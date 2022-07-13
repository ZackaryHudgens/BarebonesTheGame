#include "EffectAction.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "SlowEffect.hpp"

using Barebones::EffectAction;

/******************************************************************************/
EffectAction::EffectAction()
  : SkillAction()
  , mType(EffectType::eNONE)
{
}

/******************************************************************************/
void EffectAction::Execute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto character = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(character != nullptr)
    {
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        switch(mType)
        {
          case EffectType::eSLOW:
          {
            characterBehaviorComponent->AddEffect(std::make_unique<SlowEffect>());
            break;
          }
          default:
          {
            break;
          }
        }
      }
    }
  }
}

/******************************************************************************/
void EffectAction::SetEffectType(const EffectType& aType)
{
  mType = aType;

  switch(mType)
  {
    case EffectType::eSLOW:
    {
      SetDescription("Applies slow.");
      break;
    }
    default:
    {
      break;
    }
  }
}

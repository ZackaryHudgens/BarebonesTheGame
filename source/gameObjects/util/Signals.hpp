#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <GameObject.hpp>
#include <Signal.hpp>

namespace Barebones
{
  class CharacterBehaviorComponent;
  class InputComponent;
  class PlayerBehaviorComponent;
  class Skill;
  class TurnDisplayComponent;

  /**
   * Character signals
   */
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&> CharacterDiedSignal;

  extern CharacterDiedSignal CharacterDied;

  /**
   * Player signals
   */
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerMovedSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnBeganSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnEndedSignal;

  extern PlayerMovedSignal     PlayerMoved;
  extern PlayerTurnBeganSignal PlayerTurnBegan;
  extern PlayerTurnEndedSignal PlayerTurnEnded;

  /**
   * Tile signals
   */
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> TileReadyForUseSignal;

  extern TileReadyForUseSignal TileReadyForUse;

  /**
   * Input signals
   */
  typedef UrsineEngine::SignalT<InputComponent&> InputComponentInitializedSignal;

  extern InputComponentInitializedSignal InputComponentInitialized;

  /**
   * GUI Signals
   */
  typedef UrsineEngine::SignalT<TurnDisplayComponent&> TurnDisplayFinishedSignal;
  typedef UrsineEngine::SignalT<Skill&> SkillSelectedFromMenuSignal;

  extern TurnDisplayFinishedSignal TurnDisplayFinished;
  extern SkillSelectedFromMenuSignal SkillSelectedFromMenu;
}

#endif

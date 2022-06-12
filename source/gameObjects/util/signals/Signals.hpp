#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <GameObject.hpp>
#include <Signal.hpp>

#include "Side.hpp"

namespace Barebones
{
  class CharacterBehaviorComponent;
  class Effect;
  class InputComponent;
  class PlayerBehaviorComponent;
  class HumanPlayerBehaviorComponent;
  class Skill;
  class TurnDisplayComponent;
  class MenuLayoutComponent;
  class MenuAction;

  /**
   * Character signals
   */
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterFinishedMovingSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterStartedMovingAlongPathSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterFinishedMovingAlongPathSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterTurnBeganSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterTurnEndedSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterHealthChangedSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterDiedSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&, Effect&> EffectAddedToCharacterSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&, Effect&> EffectRemovedFromCharacterSignal;

  extern CharacterFinishedMovingSignal          CharacterFinishedMoving;
  extern CharacterStartedMovingAlongPathSignal  CharacterStartedMovingAlongPath;
  extern CharacterFinishedMovingAlongPathSignal CharacterFinishedMovingAlongPath;
  extern CharacterTurnBeganSignal               CharacterTurnBegan;
  extern CharacterTurnEndedSignal               CharacterTurnEnded;
  extern CharacterHealthChangedSignal           CharacterHealthChanged;
  extern CharacterDiedSignal                    CharacterDied;
  extern EffectAddedToCharacterSignal           EffectAddedToCharacter;
  extern EffectRemovedFromCharacterSignal       EffectRemovedFromCharacter;

  /**
   * Skill signals
   */
  typedef UrsineEngine::SignalT<Skill&>                    SkillSelectedSignal;
  typedef UrsineEngine::SignalT<Skill&>                    SkillExecutedSignal;
  typedef UrsineEngine::SignalT<Skill&>                    SkillCancelledSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> SkillVisualEffectFinishedSignal;

  extern SkillSelectedSignal  SkillSelected;
  extern SkillExecutedSignal  SkillExecuted;
  extern SkillCancelledSignal SkillCancelled;
  extern SkillVisualEffectFinishedSignal SkillVisualEffectFinished;

  /**
   * Player signals
   */
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnBeganSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnEndedSignal;
  typedef UrsineEngine::SignalT<HumanPlayerBehaviorComponent&> HumanPlayerMovedSignal;

  extern PlayerTurnBeganSignal  PlayerTurnBegan;
  extern PlayerTurnEndedSignal  PlayerTurnEnded;
  extern HumanPlayerMovedSignal HumanPlayerMoved;

  /**
   * Tile signals
   */
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> TileReadyForUseSignal;

  extern TileReadyForUseSignal TileReadyForUse;

  /**
   * Board signals
   */
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> BoardReadyForUseSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&, Side&> AllCharactersOfSideDefeatedSignal;

  extern BoardReadyForUseSignal BoardReadyForUse;
  extern AllCharactersOfSideDefeatedSignal AllCharactersOfSideDefeated;

  /**
   * Input signals
   */
  typedef UrsineEngine::SignalT<InputComponent&> InputComponentInitializedSignal;

  extern InputComponentInitializedSignal InputComponentInitialized;

  /**
   * GUI Signals
   */
  typedef UrsineEngine::SignalT<MenuLayoutComponent&> MenuLayoutComponentInitializedSignal;
  typedef UrsineEngine::SignalT<MenuAction&> MenuActionEnabledChangedSignal;

  extern MenuLayoutComponentInitializedSignal MenuLayoutComponentInitialized;
  extern MenuActionEnabledChangedSignal MenuActionEnabledChanged;

  /**
   * Camera signals
   */
  typedef UrsineEngine::SignalT<double> CameraZoomChangeRequestedSignal;
  typedef UrsineEngine::SignalT<> CameraFinishedMovingSignal;

  extern CameraZoomChangeRequestedSignal CameraZoomChangeRequested;
  extern CameraFinishedMovingSignal CameraFinishedMoving;
}

#endif

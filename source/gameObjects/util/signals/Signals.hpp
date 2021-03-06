#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <GameObject.hpp>
#include <Signal.hpp>

#include "CharacterFactory.hpp"
#include "SceneFactory.hpp"

#include "Side.hpp"

namespace Barebones
{
  class CharacterBehaviorComponent;
  class Effect;
  class InputComponent;
  class PlayerBehaviorComponent;
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
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&>          CharacterFinishedSpawningSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&, Effect&> EffectAddedToCharacterSignal;
  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&, Effect&> EffectRemovedFromCharacterSignal;

  extern CharacterFinishedMovingSignal          CharacterFinishedMoving;
  extern CharacterStartedMovingAlongPathSignal  CharacterStartedMovingAlongPath;
  extern CharacterFinishedMovingAlongPathSignal CharacterFinishedMovingAlongPath;
  extern CharacterTurnBeganSignal               CharacterTurnBegan;
  extern CharacterTurnEndedSignal               CharacterTurnEnded;
  extern CharacterHealthChangedSignal           CharacterHealthChanged;
  extern CharacterDiedSignal                    CharacterDied;
  extern CharacterFinishedSpawningSignal        CharacterFinishedSpawning;
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

  extern PlayerTurnBeganSignal  PlayerTurnBegan;
  extern PlayerTurnEndedSignal  PlayerTurnEnded;

  /**
   * Tile signals
   */
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> TileReadyForUseSignal;

  extern TileReadyForUseSignal TileReadyForUse;

  /**
   * Board signals
   */
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> BoardFinishedInitialSequenceSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> BoardFocusedTileChangedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&, Side&> AllCharactersOfSideDefeatedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> NewEnemyWaveRequestedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> WaveFinishedSpawningSignal;

  extern BoardFinishedInitialSequenceSignal BoardFinishedInitialSequence;
  extern BoardFocusedTileChangedSignal BoardFocusedTileChanged;
  extern AllCharactersOfSideDefeatedSignal AllCharactersOfSideDefeated;
  extern NewEnemyWaveRequestedSignal NewEnemyWaveRequested;
  extern WaveFinishedSpawningSignal WaveFinishedSpawning;

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
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&, MenuAction&> MenuActionHoveredSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&, MenuAction&> MenuActionExecutedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> ActDisplayReadyForInputSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> ActDisplayAdvancedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> ActDisplayFinishedSignal;
  typedef UrsineEngine::SignalT<const CharacterType&> CharacterSelectedFromRewardsMenuSignal;
  typedef UrsineEngine::SignalT<const std::string&> DisplayHintRequestedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> ScreenTransitionFinishedSignal;
  typedef UrsineEngine::SignalT<const SceneType&> ScreenTransitionRequestedSignal;

  extern MenuLayoutComponentInitializedSignal MenuLayoutComponentInitialized;
  extern MenuActionEnabledChangedSignal MenuActionEnabledChanged;
  extern MenuActionHoveredSignal MenuActionHovered;
  extern MenuActionExecutedSignal MenuActionExecuted;
  extern ActDisplayReadyForInputSignal ActDisplayReadyForInput;
  extern ActDisplayAdvancedSignal ActDisplayAdvanced;
  extern ActDisplayFinishedSignal ActDisplayFinished;
  extern CharacterSelectedFromRewardsMenuSignal CharacterSelectedFromRewardsMenu;
  extern DisplayHintRequestedSignal DisplayHintRequested;
  extern ScreenTransitionFinishedSignal ScreenTransitionFinished;
  extern ScreenTransitionRequestedSignal ScreenTransitionRequested;

  /**
   * Camera signals
   */
  typedef UrsineEngine::SignalT<> CameraZoomChangeRequestedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> CameraFinishedInitialSequenceSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> CameraFinishedMovingToCharacterSignal;

  extern CameraZoomChangeRequestedSignal CameraZoomChangeRequested;
  extern CameraFinishedInitialSequenceSignal CameraFinishedInitialSequence;
  extern CameraFinishedMovingToCharacterSignal CameraFinishedMovingToCharacter;
}

#endif

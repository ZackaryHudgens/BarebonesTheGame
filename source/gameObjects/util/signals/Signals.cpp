#include "Signals.hpp"

/**
 * Character signals
 */
Barebones::CharacterFinishedMovingSignal          Barebones::CharacterFinishedMoving;
Barebones::CharacterStartedMovingAlongPathSignal  Barebones::CharacterStartedMovingAlongPath;
Barebones::CharacterFinishedMovingAlongPathSignal Barebones::CharacterFinishedMovingAlongPath;
Barebones::CharacterTurnBeganSignal               Barebones::CharacterTurnBegan;
Barebones::CharacterTurnEndedSignal               Barebones::CharacterTurnEnded;
Barebones::CharacterHealthChangedSignal           Barebones::CharacterHealthChanged;
Barebones::CharacterDiedSignal                    Barebones::CharacterDied;
Barebones::CharacterFinishedSpawningSignal        Barebones::CharacterFinishedSpawning;
Barebones::EffectAddedToCharacterSignal           Barebones::EffectAddedToCharacter;
Barebones::EffectRemovedFromCharacterSignal       Barebones::EffectRemovedFromCharacter;

/**
 * Skill signals
 */
Barebones::SkillSelectedSignal  Barebones::SkillSelected;
Barebones::SkillExecutedSignal  Barebones::SkillExecuted;
Barebones::SkillCancelledSignal Barebones::SkillCancelled;
Barebones::SkillVisualEffectFinishedSignal Barebones::SkillVisualEffectFinished;

/**
 * Player signals
 */
Barebones::PlayerTurnBeganSignal  Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal  Barebones::PlayerTurnEnded;

/**
 * Tile signals
 */
Barebones::TileReadyForUseSignal Barebones::TileReadyForUse;

/**
 * Board signals
 */
Barebones::BoardFinishedInitialSequenceSignal Barebones::BoardFinishedInitialSequence;
Barebones::BoardFocusedTileChangedSignal Barebones::BoardFocusedTileChanged;
Barebones::AllCharactersOfSideDefeatedSignal Barebones::AllCharactersOfSideDefeated;
Barebones::NewEnemyWaveRequestedSignal Barebones::NewEnemyWaveRequested;
Barebones::WaveFinishedSpawningSignal Barebones::WaveFinishedSpawning;

/**
 * Input signals
 */
Barebones::InputComponentInitializedSignal Barebones::InputComponentInitialized;

/**
 * GUI Signals
 */
Barebones::MenuLayoutComponentInitializedSignal Barebones::MenuLayoutComponentInitialized;
Barebones::MenuActionEnabledChangedSignal Barebones::MenuActionEnabledChanged;
Barebones::MenuActionHoveredSignal Barebones::MenuActionHovered;
Barebones::MenuActionExecutedSignal Barebones::MenuActionExecuted;
Barebones::ActDisplayReadyForInputSignal Barebones::ActDisplayReadyForInput;
Barebones::ActDisplayAdvancedSignal Barebones::ActDisplayAdvanced;
Barebones::ActDisplayFinishedSignal Barebones::ActDisplayFinished;
Barebones::CharacterSelectedFromRewardsMenuSignal Barebones::CharacterSelectedFromRewardsMenu;
Barebones::DisplayHintRequestedSignal Barebones::DisplayHintRequested;
Barebones::ScreenTransitionFinishedSignal Barebones::ScreenTransitionFinished;
Barebones::ScreenTransitionRequestedSignal Barebones::ScreenTransitionRequested;

/**
 * Camera signals
 */
Barebones::CameraZoomChangeRequestedSignal Barebones::CameraZoomChangeRequested;
Barebones::CameraFinishedInitialSequenceSignal Barebones::CameraFinishedInitialSequence;
Barebones::CameraFinishedMovingToCharacterSignal Barebones::CameraFinishedMovingToCharacter;

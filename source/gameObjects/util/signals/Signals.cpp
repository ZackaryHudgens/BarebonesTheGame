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
Barebones::SkillSelectedSignal                    Barebones::SkillSelected;
Barebones::SkillExecutedSignal                    Barebones::SkillExecuted;
Barebones::SkillCancelledSignal                   Barebones::SkillCancelled;
Barebones::EffectAddedToCharacterSignal           Barebones::EffectAddedToCharacter;
Barebones::EffectRemovedFromCharacterSignal       Barebones::EffectRemovedFromCharacter;

/**
 * Player signals
 */
Barebones::PlayerTurnBeganSignal  Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal  Barebones::PlayerTurnEnded;
Barebones::HumanPlayerMovedSignal Barebones::HumanPlayerMoved;

/**
 * Tile signals
 */
Barebones::TileReadyForUseSignal Barebones::TileReadyForUse;

/**
 * Input signals
 */
Barebones::InputComponentInitializedSignal Barebones::InputComponentInitialized;

/**
 * GUI Signals
 */
Barebones::TurnDisplayFinishedSignal   Barebones::TurnDisplayFinished;

/**
 * Settings signals
 */
Barebones::CameraZoomChangeRequestedSignal Barebones::CameraZoomChangeRequested;

#include "Signals.hpp"

/**
 * Character signals
 */
Barebones::CharacterFinishedMovingSignal Barebones::CharacterFinishedMoving;
Barebones::CharacterTurnEndedSignal      Barebones::CharacterTurnEnded;
Barebones::CharacterDiedSignal           Barebones::CharacterDied;
Barebones::SkillExecutedSignal           Barebones::SkillExecuted;
Barebones::SkillCancelledSignal          Barebones::SkillCancelled;

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
Barebones::SkillSelectedFromMenuSignal Barebones::SkillSelectedFromMenu;

#include "Signals.hpp"

/**
 * Character signals
 */
Barebones::CharacterDiedSignal Barebones::CharacterDied;

/**
 * Player signals
 */
Barebones::PlayerMovedSignal     Barebones::PlayerMoved;
Barebones::PlayerTurnBeganSignal Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal Barebones::PlayerTurnEnded;

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
Barebones::TurnDisplayFinishedSignal  Barebones::TurnDisplayFinished;
Barebones::SkillSelectedFromMenuSignal Barebones::SkillSelectedFromMenu;

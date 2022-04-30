#include "DesecratedEffect.hpp"

using Barebones::DesecratedEffect;

/******************************************************************************/
DesecratedEffect::DesecratedEffect()
  : Effect()
{
  SetName("Desecrated");
  SetDescription("Loses 2 HP at end of turn if human. Heals 2 HP at end of turn if skeleton.");
  SetStatusMessage("Desecrated!");
}

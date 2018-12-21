#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#include "player.h"

void saveStats(Player p);
void loadStats(Player *p);
void resetStats(Player *p);

#endif // STATS_H_INCLUDED

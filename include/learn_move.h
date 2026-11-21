#ifndef GUARD_LEARN_MOVE_H
#define GUARD_LEARN_MOVE_H

void TeachMoveRelearnerMove(void);
// Mom's relearner: teaches `mon` (level-up and Egg moves), then calls exitCallback.
void ShowMoveRelearnerForMon(struct Pokemon *mon, MainCallback exitCallback);

#endif // GUARD_LEARN_MOVE_H

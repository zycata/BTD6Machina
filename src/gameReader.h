#ifndef gameReader_H
#define gameReader_H

namespace gameInfo {
    int getCash();
    int getStartRound();
    int getCurRound();
    int getLives();
    int getTowersPlaced();
    int getTotalAbilities();
    int getLogNumber();
    bool roundChanged();
    bool isGameOver();
    bool isGameWon();
}
// implemented now
#endif
#ifndef gameReader_H
#define gameReader_H

namespace gameInfo {
    void initialize();
    int getCash();
    int getStartRound();
    int getCurRound();
    int getLives();
    int getTowersPlaced();
    int getTotalAbilities();
    int getLogNumber();
    bool roundChanged();
    bool didGameOver();
    bool didGameWon();
}
// implemented 
#endif
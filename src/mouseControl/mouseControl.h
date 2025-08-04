
#pragma once
#ifndef mouseControl_H
#define mouseControl_H

namespace mouseControl {
    void initializeWindow();
    void useAbility(int abilityIndex);
    bool placeTower(int tower, int x, int y);
    void upgradeTower(int x, int y, int path);
    bool findWindow();
    bool initializeMouseControls();
    void ClickStartNextRound();
    void restartGameWhenOver(bool roundinitialandchimps);
}



#endif

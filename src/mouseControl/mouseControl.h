#ifndef mouseControl_H
#define mouseControl_H

namespace mouseControl {
    bool placeTower(int tower, int x, int y);
    void upgradeTower(int x, int y, int path);
    bool findWindow();
    bool initializeMouseControls();
}



#endif

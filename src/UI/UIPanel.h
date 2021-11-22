//
//  UIPanel.h
//  kinect
//
//  Created by Daniel Almeida on 31/10/2021.
//

#ifndef UIPanel_h
#define UIPanel_h

#include "AppData.h"

class UIPanel {
public:
    ofxGuiGroup panel;
    unsigned int width;
    unsigned int column;
    AppData *appData;
    
    UIPanel() {
        width = 150;
    }
    
    void setup(AppData *_appData, unsigned int _column = 0) {
        appData = _appData;
        column = _column;
        panel.setup();
        panel.setWidthElements(width);
        panel.setPosition(width*column, 0);
        panel.elementSpacing = 0;
        panel.groupSpacing = 4;
        panel.childrenLeftIndent = 4;
        panel.setHeaderBackgroundColor(ofColor::darkorange);
        panel.setUseTTF(true);
        panel.loadFont("Roboto-Medium.ttf", 10);
    }

    
    void draw() {
        panel.draw();
    }
};

#endif /* UIPanel_h */

//
//  AppGUI.h
//  emptyExample
//
//  Created by Daniel Almeida on 25/07/2021.
//

#ifndef AppGUI_h
#define AppGUI_h

#include "ofxGui.h"
#include "UI/ShaderBatch.h"
#include "UI/Shaders.h"


class AppGUI {
  
public:
    ShaderBatchUI shaderBatchUI;
    ShadersUI shadersUI;
    AppData *appData;
    
    
    /*!
     Sets up all the panels
     */
    void init(AppData *_appData) {
        appData = _appData;
        shaderBatchUI.setup(appData);
        shadersUI.setup(appData);
    };
    
    /*!
     Drawss all shaders
     */
    void draw() {
        shadersUI.draw();
        shaderBatchUI.draw();
    }
    
};

#endif /* AppGUI_h */

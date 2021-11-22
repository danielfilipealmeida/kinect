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
#include "UI/Inputs.h"

class AppGUI {
  
public:
    bool show;
    
    ShaderBatchUI shaderBatchUI;
    ShadersUI shadersUI;
    InputsUI inputsUI;
    AppData *appData;
    
    
    /*!
     Sets up all the panels
     */
    void init(AppData *_appData) {
        show = true;
        appData = _appData;
        shaderBatchUI.setup(appData, 0);
        shadersUI.setup(appData, 1);
        inputsUI.setup(appData, 2);
    };
    
    /*!
     Draws all shaders
     */
    void draw() {
        if (!show) return;
        
        shadersUI.draw();
        shaderBatchUI.draw();
        inputsUI.draw();
    }
    
};

#endif /* AppGUI_h */

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
    
    
    /*!
     Sets up all the panels
     */
    void init(AppShaders* shaders, ShaderBatch* shaderBatch) {
        shaderBatchUI.setup(shaders, shaderBatch);
        shadersUI.setup(shaders);
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

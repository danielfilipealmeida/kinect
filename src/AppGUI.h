//
//  AppGUI.h
//  emptyExample
//
//  Created by Daniel Almeida on 25/07/2021.
//

#ifndef AppGUI_h
#define AppGUI_h

#include "ofxGui.h"


class AppGUI {
  
public:
    ofxPanel shadersPanel, shaderBatchPanel;
    
    /*!
     Sets up the user interface for all shaders
     */
    void setupShaderPanel(AppShaders* shaders) {
        shadersPanel.setup();
        shadersPanel.setName("All Shaders");
        shaders->each([this, shaders](std::string shaderName, ofShader* shader) {
            //shadersPanel.add(shaders->getParameterForShader(shaderName));
        });
    }
    
    /*!
     Sets up the user interface for a shader batch
     */
    void setupShaderBatchPanel(AppShaders* shaders, ShaderBatch* shaderBatch) {
        shaderBatchPanel.setup();
        shaderBatchPanel.setName("Shader Batch");
        shaderBatch->each([this, shaders](std::string shaderName, ofShader* shader) {
            shaderBatchPanel.add(shaders->getParameterForShader(shaderName));
        });
    }
    
    /*!
     Sets up all the panels
     */
    void init(AppShaders* shaders, ShaderBatch* shaderBatch) {
        setupShaderPanel(shaders);
        setupShaderBatchPanel(shaders, shaderBatch);
    };
    
    /*!
     Drawss all shaders
     */
    void draw() {
        shadersPanel.draw();
        shaderBatchPanel.draw();
    }
    
};

#endif /* AppGUI_h */

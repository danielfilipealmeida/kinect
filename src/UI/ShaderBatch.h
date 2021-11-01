//
//  ShaderBatch.h
//  kinect
//
//  Created by Daniel Almeida on 31/10/2021.
//

#ifndef ShaderBatchUI_h
#define ShaderBatchUI_h


#include "UIPanel.h"
#include "AppData.h"

class ShaderBatchUI : public UIPanel {
    
public:
    ShaderBatchUI() {}
    
    void setup(AppData *_appData) {
        UIPanel::setup(_appData, 1);
        panel.setName("Shader Batch");
        appData->shaderBatch.each([this](std::string shaderName, ofShader* shader) {
            panel.add(this->appData->shaders.getParameterForShader(shaderName));
        });
    }
    
    void draw() {
        panel.draw();
    }
    
};

#endif /* ShaderBatch_h */

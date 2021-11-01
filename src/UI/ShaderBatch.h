//
//  ShaderBatch.h
//  kinect
//
//  Created by Daniel Almeida on 31/10/2021.
//

#ifndef ShaderBatchUI_h
#define ShaderBatchUI_h


#include "UIPanel.h"

class ShaderBatchUI : public UIPanel {
    
public:
    ShaderBatchUI() {}
    
    void setup(AppShaders* shaders, ShaderBatch* shaderBatch) {
        UIPanel::setup(1);
        panel.setName("Shader Batch");
        shaderBatch->each([this, shaders](std::string shaderName, ofShader* shader) {
            panel.add(shaders->getParameterForShader(shaderName));
        });
    }
    
    void draw() {
        panel.draw();
    }
    
};

#endif /* ShaderBatch_h */

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
    
    void setup(AppData *_appData, unsigned int _column = 0) {
        UIPanel::setup(_appData, _column);
        panel.setName("Shader Batch");
        appData->shaderBatch.each([this](std::string shaderName, ofShader* shader) {
            panel.add(this->appData->shaders.getParameterForShader(shaderName));
        });
    }
};

#endif /* ShaderBatch_h */

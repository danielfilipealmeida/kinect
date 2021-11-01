//
//  Shaders.h
//  kinect
//
//  Created by Daniel Almeida on 31/10/2021.
//

#ifndef ShadersUI_h
#define ShadersUI_h

#include "UIPanel.h"

class ShadersUI : public UIPanel {

public:
    void setup(AppShaders* shaders) {
        UIPanel::setup();
        panel.setName("All Shaders");
        shaders->each([this, shaders](std::string shaderName, ofShader* shader) {
            panel.add(shaders->getParameterForShader(shaderName));
        });
    }
    
    void draw() {
        panel.draw();
    }
};

#endif /* Shaders_h */

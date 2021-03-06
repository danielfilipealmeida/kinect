//
//  Shaders.h
//  kinect
//
//  Created by Daniel Almeida on 31/10/2021.
//

#ifndef ShadersUI_h
#define ShadersUI_h

#include "UIPanel.h"
#include "AppData.h"

class ShadersUI : public UIPanel {

public:
    void setup(AppData *_appData, unsigned int _column = 0) {
        UIPanel::setup(_appData, _column);
        panel.setName("All Shaders");
        appData->shaders.each([this](std::string shaderName, ofShader* shader) {
            panel.add(this->appData->shaders.getParameterForShader(shaderName));
        });
    }
};

#endif /* Shaders_h */

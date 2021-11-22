//
//  Inputs.h
//  kinect
//
//  Created by Daniel Almeida on 01/11/2021.
//

#ifndef InputsUI_h
#define InputsUI_h

#include "inputs/Video.hpp"
#include "ofxAddons/ofxFbo.h"
#include <typeinfo>


class InputsUI : public UIPanel {
    
public:
    void setup(AppData *_appData, unsigned int _column = 0) {
        UIPanel::setup(_appData, _column);
        panel.setName("Inputs");
        appData->inputs.each([this](InputProtocol *input){
            if (typeid(input) == typeid(Video)) {}
            
            ofFbo *fbo = &((Video *)input)->screenshot;
            ofxFbo* uiElement = new ofxFbo();
            uiElement->setup(fbo);
            panel.add((ofxBaseGui *)uiElement);
        });
    }
};

#endif /* Inputs_h */

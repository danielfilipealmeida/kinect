//
//  InputProtocol.hpp
//  kinect
//
//  Created by Daniel Almeida on 10/08/2021.
//

#ifndef InputProtocol_h
#define InputProtocol_h


#include "ofMain.h"

#define SCREENSHOT_WIDTH 320
#define SCREENSHOT_HEIGHT 240

class InputProtocol {
    
public:
    bool screenshotGenerated;
    
    virtual void update() = 0;
    virtual void draw(float x, float y, float w, float h) = 0;
    virtual ofPixels & getPixels() = 0;
    virtual ofTexture & getTexture() = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual bool isActive() = 0;
    virtual void generateScreenshot() = 0;
};


#endif /* InputProtocol_h */

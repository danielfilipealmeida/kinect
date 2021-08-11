//
//  InputProtocol.hpp
//  kinect
//
//  Created by Daniel Almeida on 10/08/2021.
//

#ifndef InputProtocol_h
#define InputProtocol_h


#include "ofMain.h"

class InputProtocol {
public:
    virtual void update() = 0;
    virtual void draw(float x, float y, float w, float h) = 0;
    virtual ofPixels & getPixels() = 0;
    virtual ofTexture & getTexture() = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
};


#endif /* InputProtocol_h */

//
//  Video.hpp
//  kinect
//
//  Created by Daniel Almeida on 10/08/2021.
//

#ifndef Video_h
#define Video_h


#include "InputProtocol.hpp"

class Video : InputProtocol {
    ofJson data;
    ofVideoPlayer video;
    ofFbo fbo;
    ofPixels pixels;
    
public:
    Video(ofJson data) {
        this->data = data;
    };
    
    virtual void update() {
        if (!video.isLoaded()) {
            video.load(data["path"]);
            video.setLoopState(OF_LOOP_NORMAL);
            
            fbo.allocate(video.getWidth(), video.getHeight());
        };
        video.update();
    }
    
    void draw(float x, float y, float w, float h){
        video.draw(x, y, w, h);
    };
    
    ofPixels & getPixels() {
        updateFbo();
        ofPixels &pixelsRef = pixels;
        fbo.readToPixels(pixelsRef);
        return pixelsRef;
    }
    
    ofTexture & getTexture() {
        updateFbo();
        return fbo.getTexture();
    }
    
    void play() {
        video.play();
    }
    
    void stop() {
        video.stop();
    }
    
    void updateFbo() {
        fbo.begin();
        video.draw(0,0);
        fbo.end();
    }
    
};



#endif /* Video_h */

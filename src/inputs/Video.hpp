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
    
public:
    Video(ofJson data) {
        this->data = data;
    };
    
    virtual void update() {
        if (!video.isLoaded()) {
            video.load(data["path"]);
            video.setLoopState(OF_LOOP_NORMAL);
        };
        video.update();
    }
    
    void draw(float x, float y, float w, float h){
        video.draw(x, y, w, h);
    };
    
    ofPixels & getPixels() {
        return video.getPixels();
    }
    
    ofTexture & getTexture() {
        return video.getTexture();
    }
    
    void play() {
        video.play();
    }
    
    void stop() {
        video.stop();
    }
    
};



#endif /* Video_h */

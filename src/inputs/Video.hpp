//
//  Video.hpp
//  kinect
//
//  Created by Daniel Almeida on 10/08/2021.
//

#ifndef Video_h
#define Video_h


#include "InputProtocol.hpp"

#define SCREENSHOT_VIDEO_POSITION 0.1

class Video : InputProtocol {
    
public:
    ofJson data;
    ofVideoPlayer video;
    ofFbo fbo;
    ofPixels pixels;
    ofFbo screenshot;
    
    
    Video(ofJson data) {
        this->data = data;
        
        ofLogNotice("Loading video " + std::string(data["path"]) + ".");
        video.load(data["path"]);
        video.setLoopState(OF_LOOP_NORMAL);
        
        fbo.allocate(video.getWidth(), video.getHeight());
        screenshot.allocate(SCREENSHOT_WIDTH, SCREENSHOT_HEIGHT);
        
        screenshotGenerated = false;
    };
    
    virtual void generateScreenshot() {
        if (screenshotGenerated) return;
        if (!video.isLoaded()) return;
       
        
        video.play();
        if (!video.isPlaying()) return;
        video.setPosition(SCREENSHOT_VIDEO_POSITION);
        video.update();
        screenshot.begin();
        ofColor(255,255,255);
        video.draw(0,0,SCREENSHOT_WIDTH,SCREENSHOT_HEIGHT);
        screenshot.end();
        video.stop();
        video.setPosition(0.0);
        ofLogNotice("Generated Screenshot for " + std::string(data["path"]) + ".");
        screenshotGenerated = true;
    };
    
    virtual void update() {
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
        if (!fbo.isAllocated()) {
            return;
        }
        
        fbo.begin();
        video.draw(0,0);
        fbo.end();
    }
    
    bool isActive() {
        return (video.isLoaded() && fbo.isAllocated());
    }
    
};



#endif /* Video_h */

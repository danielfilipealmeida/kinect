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
    
    
    void render(){
        if (!video.isLoaded()) {
            video.load(data["path"]);
        };
        
    };
    
};



#endif /* Video_h */

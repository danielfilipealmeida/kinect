//
//  shaderBatch.h
//  kinect
//
//  Created by Daniel Almeida on 30/05/2021.
//

#ifndef ShaderBatch_h
#define ShaderBatch_h

#include "AppShaders.hpp"


class ShaderBatch {
    std::vector<std::string> shaders;
    AppShaders appShaders;
    
public:
    ofFbo output;
    ofRectangle rect;
    ofTexture tmpTex;
    
    ShaderBatch() {}
    
    
    void setup(AppShaders _appShaders, std::vector<std::string> _shaders, ofRectangle _rect) {
        appShaders = _appShaders;
        shaders.insert(shaders.end(), _shaders.begin(), _shaders.end());
        rect = _rect;
        output.allocate(rect.getWidth(), rect.getHeight());
    }
    
    void apply(ofTexture tex) {
        bool firstFilter = true;
        for (std::string shader:shaders) {
            if (firstFilter) {
                output.begin();
                appShaders.apply(shader, tex, rect);
                output.end();
                firstFilter = false;
            }
            else {
                ofPixels pixels;
                output.getTexture().readToPixels(pixels);
                if (!tmpTex.isAllocated()) tmpTex.allocate(pixels); else tmpTex.readToPixels(pixels);
              
                output.begin();
                appShaders.apply(shader, tmpTex, rect);
                output.end();
                
            }
        }
        
    }
};

#endif /* ShaderBatch_h */

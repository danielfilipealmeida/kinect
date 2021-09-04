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
    AppShaders appShaders;
    
public:
    std::vector<std::string> shaders;
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
    
    ofTexture newResizedTexture(ofTexture tex, unsigned int width, unsigned int height) {
        ofFbo tempFbo;
        tempFbo.allocate(width, height);
        
        tempFbo.begin();
        tex.draw(0,0,width, height);
        tempFbo.end();
        
        return tempFbo.getTexture();
    }
    
    void applyShaderToTexture(std::string shaderName, ofTexture &tex) {
        output.begin();
        appShaders.apply(shaderName, tex, rect);
        output.end();
        
        // copy fbo pixels back to accumulator texture
        tex = output.getTexture();
    }
    
    void apply(ofTexture tex) {
        bool firstFilter = true;
        
        ofTexture accumulatorTexture = newResizedTexture(tex, output.getWidth(), output.getHeight());
       
        for (std::string shader:shaders) {
            applyShaderToTexture(shader, accumulatorTexture);
            /*
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
             */
        }
    }
    
    void update() {
       
    }
    
    /*!
     Applies the lambda to each shader in the batch
     */
    void each(std::function<void(std::string, ofShader*)> lambda) {
        for (std::string shaderName:shaders) {
            lambda(shaderName, appShaders.shaders[shaderName]);
        }
    }
};

#endif /* ShaderBatch_h */

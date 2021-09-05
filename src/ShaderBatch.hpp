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
        ofTexture tmpTexture;
        ofPixels tmpPixels;
        tex.readToPixels(tmpPixels);
        tmpTexture.allocate(tmpPixels);
        ofFbo tempFbo;
        tempFbo.allocate(width, height);
        
        tempFbo.begin();
        tmpTexture.draw(0,0,width, height);
        tempFbo.end();
        
        return tempFbo.getTexture();
    }
    
    void applyShaderToTexture(std::string shaderName, ofTexture *tex) {
        output.begin();
        appShaders.apply(shaderName, *tex, rect);
        output.end();
    
    }
    
    void apply(ofTexture tex) {
        //ofTexture accumulatorTexture = newResizedTexture(tex, output.getWidth(), output.getHeight());
        
        ofTexture *accumulatorTexture = &tex;
        ofFbo tmpFbo;
        tmpFbo.allocate(output.getWidth(), output.getHeight());
        
        
        unsigned int count = 0;
        for (std::string shader:shaders) {
            applyShaderToTexture(shader, accumulatorTexture);
        
            *accumulatorTexture = output.getTexture();
            
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

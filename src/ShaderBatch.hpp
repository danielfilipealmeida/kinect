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
        ofSetColor(255,255,255);
        tmpTexture.draw(0,0,width, height);
        tempFbo.end();
        
        return tempFbo.getTexture();
    }
    
    unsigned int countEnabledShaders() {
        unsigned int counter = 0;
        for (std::string shader:shaders) {
            if (appShaders.isShaderEnabled(shader)) counter++;
        }
        
        return counter;
    }
    
    /*!
     Applies one shader to a texture
     Will leave early if the shader is disabled
     @param shaderName
     @param tex
     */
    void applyShaderToTexture(std::string shaderName, ofTexture *tex) {
        if (!appShaders.isShaderEnabled(shaderName)) return;
    
        output.begin();
        appShaders.apply(shaderName, *tex, rect);
        output.end();
    }
    
    
    /*!
     Applies all shaders in this shader batch to a texture
     @param tex
     */
    void apply(ofTexture tex) {
         ofTexture *accumulatorTexture = &tex;
        //ofFbo tmpFbo;
        //tmpFbo.allocate(output.getWidth(), output.getHeight());
        
        unsigned int counter = countEnabledShaders();
        if (counter == 0) {
            output.begin();
            tex.draw(0, 0, output.getWidth(), output.getHeight());
            output.end();
        };
        if (counter == 1) {
            std::string shaderName;
            for(std::string shader:shaders) {
                if (appShaders.isShaderEnabled(shader)) {
                    shaderName = shader;
                    break;
                }
            }
            applyShaderToTexture(shaderName, &tex);
            return;
        }
        for (std::string shader:shaders) {
            applyShaderToTexture(shader, accumulatorTexture);
            *accumulatorTexture = output.getTexture();
        }
        
        //tex = *accumulatorTexture;
    }
    
    void update() {
       
    }

    /*!
     Draws the current shader batch output
     @param x
     @param y
     @param width
     @param height
     */
    void draw(unsigned int x, unsigned int y, unsigned int width, unsigned  int height){
        output.draw(x,y,width,height);
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

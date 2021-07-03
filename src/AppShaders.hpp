//
//  AppShaders.hpp
//  kinect
//
//  Created by Daniel Almeida on 27/05/2021.
//

#ifndef AppShaders_h
#define AppShaders_h

#include <iostream>
#include <map>
#include <string>


/**
 Facade for all shaders used in the app
 */
class AppShaders {
    std::map<std::string, ofShader*> shaders;
    ofJson config;
    
    
public:
    
    ofParameterGroup group;
    
    AppShaders() {}
    
    void loadConfig(ofJson _config) {
        config = _config;
        for(auto& [key, value] : config.items()) {
            loadShader(key);
            
            for(auto& [key, value]  : value.items()) {
                if (key == "parameters")  {
                    handleParameters(value);
                }
            }
            
            
        }
    }
    
    void handleParameters(ofJson parameters) {
        for(auto& [parameter, options]  : parameters.items()) {
            if (options["type"] == "rgb") {
                ofParameter<ofColor> param;
                param.setName(parameter);
                
                group.add(param);
            }
        }
    }
    
    /*!
     check if the shader is already added
     @param shader
     @return bool
     -
     */
    bool hasShader(std::string shader) {
        for(auto it : shaders) {
            if (it.first.compare(shader) == 0) {
                return true;
            }
        }
        
        return false;
    }
    
    void loadShader(std::string shaderName) {
        if (hasShader(shaderName)) return;
        
        ofShader *newShader = new ofShader();
        newShader->load("basic.vert", shaderName + ".frag");
        shaders[shaderName] = newShader;
    }
    
    void apply(std::string shaderName, ofTexture texture, ofRectangle rect) {
        ofShader *shader = shaders[shaderName];
        
        if (!shader) {
            throw std::runtime_error("No " + shaderName + " shader");
        }
        
        shader->begin();
        texture.draw(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
        shader->end();
    }
    
};

#endif /* AppShaders_h */

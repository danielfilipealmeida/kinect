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
    ofJson config;
    std::map<std::string, ofParameterGroup> parameterGroups;
    
public:
    
    std::map<std::string, ofShader*> shaders;
    
    AppShaders() {}
    
    /*!
     */
    void loadConfig(ofJson _config) {
        config = _config;
        for(auto& [shaderName, value] : config.items()) {
            loadShader(shaderName);
            
            for(auto& [key, value]  : value.items()) {
                if (key == "parameters")  {
                    handleParameters(shaderName, value);
                }
            }
        }
        
        shaders["limiter"]->begin();
        shaders["limiter"]->setUniform1f("lowerLimit", 100);
        shaders["limiter"]->end();
    }
    
    /*!
     */
    void handleParameters(std::string shaderName, ofJson parameters) {
        ofParameterGroup group = ofParameterGroup(shaderName);
        
        for(auto& [parameter, options]  : parameters.items()) {
            if (options["type"] == "rgb") {
                ofParameter<ofColor> param;
                param.setName(parameter);
                
                group.add(param);
            }
            
            if (options["type"] == "float") {
                ofParameter<float> param;
                param.setName(parameter);
                param.setMax(options["max"]);
                param.setMin(options["min"]);
                
                float value = options["min"];
                if (options.contains("value")) {
                     value = options["value"];
                }
                param = value;
                
                group.add(param);
            }
        }
        
        parameterGroups[shaderName] = group;
    }
    
    ofParameterGroup getParameterForShader(std::string shaderName) {
        return parameterGroups[shaderName];
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
    
    /*!
     */
    void loadShader(std::string shaderName) {
        if (hasShader(shaderName)) return;
        
        ofShader *newShader = new ofShader();
        newShader->load("basic.vert", shaderName + ".frag");
        shaders[shaderName] = newShader;
    }
    
    /*!
     */
    void apply(std::string shaderName, ofTexture texture, ofRectangle rect) {
        ofShader *shader = shaders[shaderName];
        
        if (!shader) {
            throw std::runtime_error("No " + shaderName + " shader");
        }
        
        shader->begin();
        ofParameterGroup parameterGroup = parameterGroups[shaderName];
        for(auto parameter:parameterGroup) {
            std::string name = parameter->getName();
            std::string type = parameter->valueType();
            
            if (type == "f") {
                ofParameter<float> parameter = (ofParameter<float> &) parameterGroup[name];
                shader->setUniform1f(name, parameter);
            }
            
            if (type == "8ofColor_IhE") {
                ofParameter<ofColor> parameter = (ofParameter<ofColor> &) parameterGroup[name];
                shader->setUniform3f(name, parameter.get().r / 255.0,  parameter.get().g / 255.0,  parameter.get().b / 255.0);
            }
        }
        texture.draw(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
        shader->end();
    }
    
    /*!
     Applies the lambda to each shader 
     */
    void each(std::function<void(std::string, ofShader*)> lambda) {
        for(auto& [shaderName, shader] : shaders) {
            lambda(shaderName, shader);
        }
    }
    
    
};

#endif /* AppShaders_h */

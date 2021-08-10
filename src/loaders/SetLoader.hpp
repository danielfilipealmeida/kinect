//
//  SetLoader.hpp
//  kinect
//
//  Created by Daniel Almeida on 26/07/2021.
//

#ifndef SetLoader_h
#define SetLoader_h


#include "ofMain.h"


class SetLoader {
public:
    
    std::function<void (ofJson data)> filtersLambda;
    std::function<void (ofJson data)> inputsLambda;
    
    void loadFile(std::string path) {
        ofJson setData = ofLoadJson(path);
        parseJson(setData);
    };
    
    void parseJson(ofJson data) {
        for(auto& [key, value]  : data.items()) {
            loadFilters(key, value);
            loadInputs(key, value);
        }
    }
    
    void loadFilters(std::string key, ofJson value) {
        if (key != "filters")  {
            return;
        }
        if (!filtersLambda) {
            return;
        }
        
        filtersLambda(value);
        
        //shaderBatch.setup(appShaders, value, ofRectangle(0, 0, 320, 200));
    }
    
    void loadInputs(std::string key, ofJson value) {
        if (key != "inputs")  {
            return;
        }
        if (!inputsLambda) {
            return;
        }
        
        inputsLambda(value);
    }
};

#endif /* SetLoader_h */

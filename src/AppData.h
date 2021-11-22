//
//  AppData.h
//  kinect
//
//  Created by Daniel Almeida on 01/11/2021.
//

#ifndef AppData_h
#define AppData_h


#include "InputProtocol.hpp"
#include "SetLoader.hpp"
#include "Video.hpp"
#include "Inputs.h"

class AppData {
public:
    AppShaders shaders;
    ShaderBatch shaderBatch;
    Inputs inputs;

    
    // todo, move this to a layer
    InputProtocol *activeInput;

    
    SetLoader setLoader;
   

    /// Loads a set from a given json stored in the path
    /// @param setPath the path of the json file s
    void loadSet(std::string setPath) {
        setLoader.inputsLambda = [&](ofJson data) {
            inputs.setup(data);
        };
        setLoader.filtersLambda = [&](ofJson data){
            shaderBatch.setup(shaders, data, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
        };
        setLoader.loadFile(setPath);
        
        
        // delete later. this is here just to have something running
        activeInput = inputs.inputs[0];
    }
    
};


#endif /* AppData_h */

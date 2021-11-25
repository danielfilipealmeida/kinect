//
//  Layers.h
//  emptyExample
//
//  Created by Daniel Almeida on 24/11/2021.
//

#ifndef Layers_h
#define Layers_h

#include "ShaderBatch.hpp"
#include "AppData.h"


class Layer {
public:
    bool enabled;
    float alpha;
    ofBlendMode blendMode;
    ShaderBatch shaderBatch;
    unsigned int activeVisual = 0;
    
};

/*!
 Handles all layers
 */
class Layers {
    std::vector<Layer *> layers;
public:
    
    std::map<std::string, ofBlendMode> layerBlendingModeMappings = {
        {"none", OF_BLENDMODE_DISABLED},
        {"alpha", OF_BLENDMODE_ALPHA},
        {"add",OF_BLENDMODE_ADD },
        {"subtract",OF_BLENDMODE_SUBTRACT},
        {"multiply", OF_BLENDMODE_MULTIPLY},
        {"screen",OF_BLENDMODE_SCREEN}
    };
    
    /*!
     Sets up the layers from json data
     @param layerData
     */
    void setup(ofJson layersData) {
        for(auto& [index, layer]  : layersData.items()) {
            Layer *newLayer = new Layer();
            
            newLayer->activeVisual = layer["visual"];
            newLayer->alpha = layer["alpha"];
            newLayer->blendMode = layerBlendingModeMappings[layer["mode"]];
            
            layers.push_back(newLayer);
            
        }
    }
    
    void each(std::function<void(Layer *)> lambda) {
        for (Layer* layer:layers) {
            lambda(layer);
        }
    }
    
   

};


#endif /* Layers_h */

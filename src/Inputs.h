//
//  Inputs.h
//  kinect
//
//  Created by Daniel Almeida on 01/11/2021.
//

#ifndef Inputs_h
#define Inputs_h

class Inputs {
    
public:

    std::vector<InputProtocol *> inputs;
    bool screenshotsGenerated;
    
    Inputs() {
        screenshotsGenerated = false;
    }
    
    void setup(ofJson visuals) {
        for(auto& [index, input]  : visuals.items()) {
            /*
            if  (input["type"] == "video") {
                Video *video = new Video(input);
                inputs.push_back((InputProtocol *) video);
                continue;
            }
            */
            //throw new std::runtime_error("Invalid input type");
            
            openVideo(input);
        }
    }
    
    void openVideo(ofJson input) {
        if (input["type"] != "video") return;
        
        Video *video = new Video(input);
        inputs.push_back((InputProtocol *) video);
    }
    
    /*!
     Applies the lambda to each shader in the batch
     */
    void each(std::function<void(InputProtocol*)> lambda) {
        for (InputProtocol* input:inputs) {
            lambda(input);
        }
    }
    
    /**
     Generates screenshots for all the inputs
     */
    void generateScreenshots() {
        
        unsigned int numberOfScreenshots = 0;
        each([&numberOfScreenshots](InputProtocol *image){
            image->generateScreenshot();
            if (image->screenshotGenerated) numberOfScreenshots++;
        });
        
        if (numberOfScreenshots == inputs.size()) screenshotsGenerated = true;
        ofLogNotice("Screenshots Generation: " + ofToString(numberOfScreenshots) + " of " + ofToString(inputs.size()));
        
    }
};

#endif /* Inputs_h */

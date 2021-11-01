#include "ofApp.h"
#include "Video.hpp"


void ofApp::initKinect()
{
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    angle = 0;
    kinect.setCameraTiltAngle(angle);
}

void ofApp::initUI(){
    gui.init(&appData);
}


/// Loads a set from a given json stored in the path
/// @param setPath the path of the json file s
void ofApp::loadSet(std::string setPath) {
    setLoader.inputsLambda = [&](ofJson data) {
        for(auto& [index, input]  : data.items()) {
            if  (input["type"] == "video") {
                Video *video = new Video(input);
                inputs.push_back((InputProtocol *) video);
                continue;
            }
            
            throw new std::runtime_error("Invalid input type");
        }
    };
    setLoader.filtersLambda = [&](ofJson data){
        appData.shaderBatch.setup(appData.shaders, data, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    };
    setLoader.loadFile(setPath);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    try {
        // load shaders
        ofJson shaderData = ofLoadJson("shaders.json");
        if (shaderData.empty()) throw new std::runtime_error("Error loading Shaders information.");
        appData.shaders.loadConfig(shaderData);
        
      
        loadSet("set1.json");
        
        activeInput = inputs[1];
        activeInput->update();
        activeInput->play();
        // apply data
        
        
        
        //initKinect();
        
        fbo.allocate(640, 480);
    }
    catch (std::runtime_error error) {
        errors.push_front(error.what());
    }
    
    initUI();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    activeInput->update();
    
    appData.shaderBatch.update();
    
    
    
    /*
    kinect.update();
    if(kinect.isFrameNew()) {
        depthImage = kinect.getDepthPixels();
    }
     */
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (activeInput->isActive()) {
        try {
            auto texFromPixels = [](ofPixels pixels) {
                ofTexture tex;
                tex.allocate(pixels);
                
                return tex;
            };
            
            ofSetColor(255, 255, 255);
            
            //ofTexture tex = texFromPixels(testImage.getPixels());
            ofTexture tex = activeInput->getTexture();
            appData.shaderBatch.apply(tex);
            appData.shaderBatch.output.draw(0, 0, ofGetWidth(), ofGetHeight());
        }
        catch(std::runtime_error error) {
            cout << error.what() << endl;
            errors.push_front(error.what());
        }
    }
    
    
    gui.draw();
    
    // print errors
    if (errors.empty()) return;
    
    unsigned int count = 0;
    for (std::string error:errors) {
        ofDrawBitmapString(error, 0, count * 10);
        count++;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



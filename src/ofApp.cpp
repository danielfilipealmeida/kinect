#include "ofApp.h"



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



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    frameNumber = 0;
    
    try {
        // load shaders
        ofJson shaderData = ofLoadJson("shaders.json");
        if (shaderData.empty()) throw new std::runtime_error("Error loading Shaders information.");
        appData.shaders.loadConfig(shaderData);
        appData.loadSet("set1.json");
        

    
        //initKinect();
        
        fbo.allocate(640, 480);
    }
    catch (std::runtime_error error) {
        errors.push_front(error.what());
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!appData.inputs.screenshotsGenerated && frameNumber>0) {
        appData.inputs.generateScreenshots();
        if (!appData.inputs.screenshotsGenerated) {
            return;
        }
        
        // only inits the UI when the screenshots are generated
        initUI();

        appData.activeInput->play();
        
    }
    
    
    ofBackground(0, 0, 0);
    appData.activeInput->update();
    appData.shaderBatch.update();
    
    
    
    /*
    kinect.update();
    if(kinect.isFrameNew()) {
        depthImage = kinect.getDepthPixels();
    }
     */
    frameNumber++;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (appData.activeInput->isActive()) {
        try {
            auto texFromPixels = [](ofPixels pixels) {
                ofTexture tex;
                tex.allocate(pixels);
                
                return tex;
            };
            
            ofSetColor(255, 255, 255);
            
            //ofTexture tex = texFromPixels(testImage.getPixels());
            ofTexture tex = appData.activeInput->getTexture();
            appData.shaderBatch.apply(tex);
            appData.shaderBatch.draw(0, 0, ofGetWidth(), ofGetHeight());
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



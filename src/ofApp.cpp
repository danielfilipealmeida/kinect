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
    gui.setup(appShaders.getParameterForShader("limiter"));
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    appShaders.loadConfig(ofLoadJson("shaders.json"));
    shaderBatch.setup(appShaders, {"limiter"}, ofRectangle(0, 0, 320, 200));
    
    //initKinect();
    testImage.load("Daniel.jpg");
    
    fbo.allocate(320, 200);
    
    initUI();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    
    shaderBatch.update();
    
    /*
    kinect.update();
    if(kinect.isFrameNew()) {
        depthImage = kinect.getDepthPixels();
    }
     */
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    try {
        auto texFromPixels = [](ofPixels pixels) {
            ofTexture tex;
            tex.allocate(pixels);
            
            return tex;
        };
        
        ofSetColor(255, 255, 255);
        
        ofTexture tex = texFromPixels(testImage.getPixels());

        shaderBatch.apply(tex);
        shaderBatch.output.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    catch(std::runtime_error error) {
        cout << error.what() << endl;
    }
    
    gui.draw();
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

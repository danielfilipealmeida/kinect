#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "AppShaders.hpp"
#include "ShaderBatch.hpp"
#include "AppGUI.h"
#include "AppData.h"

class ofApp : public ofBaseApp{
    std::list<std::string> errors;
    long unsigned int frameNumber;
    
	public:
    void extracted();
    
    void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void initKinect();
    void initUI();
    void loadSet(std::string setPath);
    
    void generateScreenshots();
    
    void applyToActiveInputs(std::function<void(InputProtocol *)> lambda);
    
    ofxKinect kinect;
    int angle;
    
    ofPixels depthImage;
    
    ofFbo fbo;
    
    
    
    AppGUI gui;
    AppData appData;
};

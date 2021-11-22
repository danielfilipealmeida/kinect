//
//  ofxFBO.h
//  kinect
//
//  Created by Daniel Almeida on 01/11/2021.
//

#ifndef ofxFbo_h
#define ofxFbo_h

class ofxFbo : public ofxBaseGui {
public:
    friend class ofPanel;
    ofParameter<ofFbo*> value;
    std::string title;
    ofVboMesh textMesh;
    
    ofxFbo(ofParameter<ofFbo*> _fbo) {
        value = _fbo;
    }
    ofxFbo(){}
    ~ofxFbo(){}
    
    void setup(ofParameter<ofFbo*> _value, float width = defaultWidth, float height = defaultHeight) {
        value = _value;
        ofFbo *fbo = (ofFbo*) value.get();
        
        b.x = 0;
        b.y = 0;
        b.width = width;
        b.height = width * fbo->getHeight() / fbo->getWidth();
        setNeedsRedraw();
    }
    
    void setPosition(const glm::vec3 & p) {}
    void setPosition(float x, float y) {}
    void setSize(float w, float h) {}
    void setShape(ofRectangle r) {}
    void setShape(float x, float y, float w, float h) {}
    
    // Abstract methods we must implement, but have no need for!
    virtual bool mouseMoved(ofMouseEventArgs & args){return false;}
    virtual bool mousePressed(ofMouseEventArgs & args){return false;}
    virtual bool mouseDragged(ofMouseEventArgs & args){return false;}
    virtual bool mouseReleased(ofMouseEventArgs & args){return false;}
    virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}
    
    ofAbstractParameter & getParameter() {return value;}
    
    void setTitle(std::string _title) {
        title = _title;
    }
    
    void drawTitle() {
        if (title.empty()) {
            return;
        }
        
        glm::vec2 labelPosition;
        labelPosition.x = b.x + textPadding;
        labelPosition.y =  b.y + 14;
        
        ofDrawBitmapStringHighlight(title, labelPosition, ofColor::orangeRed, textColor);
        
        return;
        
        ofSetColor(0,0,0, 128);
        ofFill();
        ofDrawRectangle(b.x, b.y, b.width, 16);
        
        
        
        
        ofSetColor(textColor);
        bindFontTexture();
        textMesh = getTextMesh(title, b.x + textPadding, b.y + 12);
        textMesh.draw();
        unbindFontTexture();
        ofSetColor(255, 255, 255, 0);
    }
    
    
protected:
    virtual void render() {
        ofSetColor(255, 255, 255, 255);
        ofFbo *fbo = (ofFbo*) value.get();
        
        fbo->draw(b.getX(), b.getY(), b.getWidth(), b.getHeight());
        
        drawTitle();
    }
    
    bool setValue(float mx, float my, bool bCheckBounds){return false;}
    void generateDraw() {};
};


#endif /* ofxFBO_h */

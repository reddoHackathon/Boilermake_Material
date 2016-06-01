#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    
    //open client with IP and PORT
    string ip = "192.168.99.71";
    int port = 11999;
    opcClient.setup(ip, port);
    
    //init heart template
    heart.setup();
    
    //start vidgrabber
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(320, 240);

   
}
//--------------------------------------------------------------
void ofApp::update()
{
    //grab video image
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        pixels = vidGrabber.getPixels();
        
        //set image to heart
        image.setFromPixels(pixels);
        image.update();
        heart.setImage(image);
    }
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
    }
    else
    {
        //send all 40ms
        if (ofGetElapsedTimeMillis() - lastSent >40) {
            // send the pixels to server
            opcClient.writeChannels(heart.colorData());
            
            lastSent = ofGetElapsedTimeMillis();
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    // draw the heart
    heart.draw();
    
    // draw additional informations
    ofDrawBitmapString("pixel position : (" + ofToString(mouseX/10) + " , " + ofToString(mouseY/10) + ")", 200, 45);
    ofDrawBitmapString("sector :          " + ofToString(heart.getSector(mouseX/10, mouseY/10)), 200, 60);
    ofDrawBitmapString("index :           " + ofToString(heart.getIndex(mouseX/10, mouseY/10)), 200, 75);
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(20);

	// setup the server to listen on 11999
	TCP.setup(11999);
    
    receiveSize = 1024000;
    tcpBuffer.allocate(receiveSize);
	lastSent = 0;
    opcClient.setup("127.0.0.1", 7890);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    for (int i = 0; i < TCP.getLastID(); i++) {
        if( TCP.isClientConnected(i) ) {
            int receiveSize = opcClient.getPacketLength();
            ofBuffer buffer;
            buffer.allocate(receiveSize);
            int totalBytes = 0;
            int counter = 0;
            while(totalBytes < receiveSize) {
                int result = TCP.receiveRawBytes(i,&buffer.getData()[totalBytes], receiveSize-totalBytes);
                if(result > 0) {
                    totalBytes += result;
                    if(totalBytes == receiveSize) {
                        opcClient.sendRawBytes(buffer.getData(),opcClient.getPacketLength());
                    } 
                }else{
                    counter++;
                }if (counter>20000){
                    break;
                }
            }
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(220);
	ofDrawBitmapString("TCP SERVER Example \n\nconnect on port: "+ofToString(TCP.getPort()), 10, 20);

	ofSetColor(0);
	ofDrawRectangle(10, 60, ofGetWidth()-24, ofGetHeight() - 65 - 15);

	ofSetColor(220);

	// for each connected client lets get the data being sent and lets print it to the screen
	for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){

		if( !TCP.isClientConnected(i) )continue;

		// give each client its own color
		ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);

		// calculate where to draw the text
		int xPos = 15;
		int yPos = 80 + (12 * i * 4);

		// get the ip and port of the client
		string port = ofToString( TCP.getClientPort(i) );
		string ip   = TCP.getClientIP(i);
		string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;


		// if we don't have a string allocated yet
		// lets create one
		if(i >= storeText.size() ){
			storeText.push_back( string() );
		}

		// draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);
		ofDrawBitmapString(storeText[i], 25, yPos + 20);

	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
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

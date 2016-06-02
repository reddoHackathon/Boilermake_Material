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

    initIdle();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    bool hasConnections = false;
    for (int i = 0; i < TCP.getLastID(); i++) {
        if( TCP.isClientConnected(i) ) {
            hasConnections = true;
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
    
    if(!hasConnections){
        runIdleAnimation();
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(220);
	ofDrawBitmapString("FadeCandy Server \n\nconnect on port: "+ofToString(TCP.getPort()), 10, 20);

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


		// draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);

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

void ofApp::initIdle(){
    heart.setup();
    pixels.allocate(15, 20, 3);
    pixels.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 0;
    sectors.back().color = ofColor::fromHsb(221,140,250);
    sectors.back().c_x = 7;
    sectors.back().c_y = 6;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 2;
    sectors.back().color = ofColor::fromHsb(8,191,250);
    sectors.back().c_x = 5;
    sectors.back().c_y = 6;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 3;
    sectors.back().color = ofColor(90,190,10);
    sectors.back().c_x = 9;
    sectors.back().c_y = 6;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 4;
    sectors.back().color = ofColor::fromHsb(23,191,250);
    sectors.back().c_x = 7;
    sectors.back().c_y = 15;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 5;
    sectors.back().color = ofColor::fromHsb(230,199,229);
    sectors.back().c_x = 3;
    sectors.back().c_y = 4;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 6;
    sectors.back().color = ofColor::fromHsb(140,196,219);
    sectors.back().c_x = 12;
    sectors.back().c_y = 6;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    sectors.push_back(Sector());
    sectors.back().id = 7;
    sectors.back().color = ofColor::fromHsb(204,158,158);
    sectors.back().c_x = 7;
    sectors.back().c_y = 2;
    sectors.back().radius = 0;
    sectors.back().px.allocate(15, 20, 3);
    sectors.back().px.setColor(ofColor(0));
    
    for (int i=0; i<sectors.size(); ++i) {
        m_sector.insert({sectors[i].id,&sectors[i]});
    }
    
    aniStart = 0;
    aniLength = 90000;

}

void ofApp::runIdleAnimation()
{
    int runTime = ofGetElapsedTimeMillis() - aniStart;
    
    
    if (runTime < STEP1*aniLength) {
        float time = ofMap(runTime, 0, STEP1*aniLength, 0, 1);
        setColors( time, m_sector[5]);
        m_sector[2]->px = m_sector[5]->px;
        m_sector[0]->px = m_sector[5]->px;
        m_sector[7]->px = m_sector[5]->px;
        
    }else if (runTime < STEP2*aniLength) {
        float time = ofMap(runTime,STEP1*aniLength, STEP2*aniLength, 0, 1);
        setColors(1, m_sector[5]);
        setColors(time, m_sector[6]);
        setColors(time, m_sector[7], m_sector[5]->color, m_sector[7]->color, m_sector[6]->c_x, m_sector[6]->c_y);
        ofColor mix0 = m_sector[5]->color;
        mix0.lerp(m_sector[6]->color, 0.5);
        setColors(time, m_sector[0], m_sector[5]->color, mix0, m_sector[6]->c_x, m_sector[6]->c_y);
        setColors(time, m_sector[3], ofColor::black, m_sector[6]->color, m_sector[6]->c_x, m_sector[6]->c_y);
        
    }else if (runTime < STEP3*aniLength) {
        float time = ofMap(runTime,STEP2*aniLength, STEP3*aniLength, 0, 1);
        setColors(1, m_sector[5]);
        setColors(1, m_sector[6]);
        setColors( time, m_sector[4]);
        setColors(time, m_sector[2], m_sector[5]->color, m_sector[2]->color, m_sector[4]->c_x, m_sector[4]->c_y);
        ofColor mix0 = m_sector[5]->color;
        mix0.lerp(m_sector[6]->color, 0.5);
        setColors(time, m_sector[0], mix0, m_sector[0]->color, m_sector[4]->c_x, m_sector[4]->c_y);
        setColors(time, m_sector[3], m_sector[6]->color, m_sector[3]->color, m_sector[4]->c_x, m_sector[4]->c_y);
        
    }else if (runTime < STEP4*aniLength) {
        setColors(1, m_sector[0]);
        setColors(1, m_sector[2]);
        setColors(1, m_sector[3]);
        setColors(1, m_sector[4]);
        setColors(1, m_sector[5]);
        setColors(1, m_sector[6]);
        setColors(1, m_sector[7]);
    }else if (runTime < aniLength) {
        float time = ofMap(runTime,STEP4*aniLength, aniLength, 0, 1);
        setColors(time, m_sector[0], m_sector[0]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[2], m_sector[2]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[3], m_sector[3]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[4], m_sector[4]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[5], m_sector[5]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[6], m_sector[6]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
        setColors(time, m_sector[7], m_sector[7]->color, ofColor::black, m_sector[0]->c_x, m_sector[0]->c_y);
    }else{
        for(auto s:sectors){
            s.px.setColor(ofColor::black);
        }
        aniStart = ofGetElapsedTimeMillis();
    }
    
    setChannels();
    opcClient.writeChannels(heart.colorData());
}

void ofApp::setColors(float time, Sector* sector){
    setColors(time, sector, ofColor::black, sector->color, sector->c_x, sector->c_y);
}

void ofApp::setColors(float time, Sector* sector, ofColor startColor, ofColor endColor, int s_x, int s_y){
    float maxRadius = 15;
    float radius = ofMap(time, 0, 1, 0, maxRadius);
    
    for (int x=0; x<sector->px.getWidth();++x) {
        for (int y=0; y<sector->px.getHeight();++y) {
            float dist = ofVec2f(s_x,s_y).distance(ofVec2f(x, y));
            float baseV = ofMap(dist, 0, maxRadius, 0, -1,true);
            baseV = mapCurve(baseV, 0, -1, 0, -1, 0.5);
            float lerp = baseV + time*2;
            if(lerp < 0) lerp = 0;
            else if (lerp > 1) lerp = 1;
            ofColor c = startColor;
            c.lerp(endColor, lerp);
            sector->px.setColor(x, y, c);
        }
    }
}

void ofApp::setChannels(){
    pixels.resize(15, 20);
    for (int x=0; x<15;++x) {
        for (int y=0; y<20;++y) {
            int s = heart.getSector(x, y);
            if (s != 255) {
                pixels.setColor(x, y, m_sector[s]->px.getColor(x, y));
            }
        }
    }
    heart.setPixels(pixels);
}

float ofApp::mapCurve(float in, float inMin, float inMax, float outMin, float outMax, float shaper){
    // (1) convert to pct (0-1)
    float pct = ofMap (in, inMin, inMax, 0, 1, true);
    // raise this number to a power
    pct = powf(pct, shaper);
    float out = ofMap(pct, 0,1, outMin, outMax, true);
    return out;
}

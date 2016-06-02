#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxOPC.h"

//idle animation steps
#define STEP1 0.20
#define STEP2 0.40
#define STEP3 0.70
#define STEP4 0.80

class ofApp : public ofBaseApp{

    //for idle animation
    struct Sector{
        ofColor color;
        float radius;
        int c_x,c_y;
        int id;
        ofPixels px;
    };
    
	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //animation
        void initIdle();
        void runIdleAnimation();
        void setColors(float time, Sector* sector);
        void setColors(float time, Sector* sector, ofColor startColor, ofColor endColor, int s_x, int s_y);
        void setChannels();
        float mapCurve(float in, float inMin, float inMax, float outMin, float outMax, float shaper);

private:
    //server
    ofxTCPServer TCP;
    ofxOPC opcClient;
    LavooHeart heart;
    uint64_t lastSent;
    ofBuffer tcpBuffer;
    int receiveSize;
    
    //idle animation
    uint64_t aniStart;
    int aniLength;
    map<int,Sector*> m_sector;
    vector<Sector> sectors;
    ofPixels pixels;
};


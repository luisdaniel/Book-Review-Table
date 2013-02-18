#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxOsc.h"
#include "BookReviewBox.h"
#include <iostream>
#include <vector>
#include "ofTrueTypeFont.h"
#include "linea.h"

using namespace std;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
    
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //----------------------------Graphics--------------
    void introScreen();
    ofTrueTypeFont myFont;    
    float alfa;
    bool intro;

    
    
    
    
    //------------------------------Kinect----------
    ofxKinect kinect;
    ofxCvColorImage colorImg;
    ofxCvContourFinder contourFinder;
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    bool bThreshWithOpenCV;
	float nearThreshold;
	float farThreshold;
    int angle;
    bool thresholdSet;
    
    
    //--------------------------------OSC---------------
    int gray;
    ofxOscReceiver  receiver;
    ofxOscSender sender;
    
    //-------------------------------Barcode-----------
    string barcode;
    string oldBarcode;
    vector<string> barcodeSet;
    
    //-------------------------------BookReviewBoxes------
    vector< BookReviewBox* > bookReviewSet;
    vector< linea* > lineaSet;
    
    //-----------------------varbs-----------
    float posx;
    float posy;
    float oldPosx;
    float oldPosy;
    
    
};

//to do: mirror the image (does it change when projected?

#include "testApp.h"
#include "math.h"

//--------------------------------------------------------------
void testApp::setup(){
    kinect.setRegistration(true);
	kinect.init();
	kinect.open();
    
    colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 236;
	farThreshold = 233;
    angle = 0;
	kinect.setCameraTiltAngle(angle);
    
    thresholdSet=false;
    
    
    
    
    //----------OSC SETUP----------
    gray = 255;
    receiver.setup(1235);
    sender.setup("127.0.0.1", 1234);
    barcode = "";
    oldBarcode = "";
    
    
    //-----------------------------position variables----------
    posx = 0;
    posy = 0;
    oldPosx = 0;
    oldPosy = 0;
    
    
    //------------graphics------------
    myFont.loadFont("Verdana.ttf", 48);
    alfa = 0;
    intro = true;
    

}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0,0,0);
	kinect.update();
    
  
    if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		
		// update the cv images
		grayImage.flagImageChanged();
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 1, false);
	}
    
    
    
    
    //--------------OSC-------------
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage mIn;
        receiver.getNextMessage(&mIn);
        barcode = mIn.getArgAsString(0);
        //cout<<barcode<<endl;
        ofxOscMessage mOut;
        mOut.addStringArg("barcodeReceived");
        string mensaje = mOut.getArgAsString(0);
        sender.sendMessage(mOut);
    }
    
    
    
    
    //----------update bookReviewBox------------
    if (barcode != oldBarcode && contourFinder.nBlobs !=0) {
        oldBarcode = barcode;
        barcodeSet.push_back(barcode);
        //new BookReviewBox
        BookReviewBox* OBJ = new BookReviewBox( barcode );
        bookReviewSet.push_back( OBJ );
    }
    
    
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    contourFinder.draw(0,0);
    
    if (barcodeSet.size() == 0) {
        introScreen();
    }

    
    
    
    for(int i = 0; i < contourFinder.nBlobs; i++) {
        ofxCvBlob r=contourFinder.blobs.at(i);
        int blobWidth = r.boundingRect.width/2;
        int blobHeight = r.boundingRect.height/2;
        ofSetHexColor(0xCCDACD);
        posx = ofMap(r.centroid.x, 538, 90, 200, 1200);
        posy = ofMap(r.centroid.y, 330, 128, 200, 700) - blobHeight;
        //ofRect(posx, posy, blobWidth, blobHeight);
        if ( abs(oldPosx-posx) < 10 || abs(oldPosx - posy) < 10) {
            posx = oldPosx;
            posy = oldPosy;
        } else {
            oldPosx = posx;
            oldPosy = posy;
        }
        if (barcodeSet.size() !=0 && bookReviewSet.size() != 0) {
            bookReviewSet[i]->update(posx+3.5*blobWidth, posy);
            bookReviewSet[i]->display();
            
            //BookReviewBox *book = new BookReviewBox(posx, posy, barcodeSet[i]);
            //book->display();
        }
    }
    if (contourFinder.nBlobs == 0) {
        for(int i = 0; i < bookReviewSet.size(); i++)
        {
            delete bookReviewSet[i];
        }
        bookReviewSet.clear();
        barcodeSet.clear();
    }
        
    
/*
    //------------------------draw instructions------------
	ofSetColor(255, 255, 255);
	stringstream reportStream;
	reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
	<< ofToString(kinect.getMksAccel().y, 2) << " / "
	<< ofToString(kinect.getMksAccel().z, 2) << endl
	<< "set near threshold " << nearThreshold << " (press: + -)" << endl
	<< "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
	<< ", fps: " << ofGetFrameRate() << endl
	<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl
	<< "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
    << "x value is " << posx << " y value is " << posy <<endl
    << "Barcode says " <<  barcode <<endl;
	ofDrawBitmapString(reportStream.str(),20,600);
    */
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
            
		case '>':
		case '.':
            if (!thresholdSet) {
                farThreshold ++;
                if (farThreshold > 255) farThreshold = 255;
            }
			break;
			
		case '<':
		case ',':
            if (!thresholdSet) {
                farThreshold --;
                if (farThreshold < 0) farThreshold = 0;
            }
			break;
			
		case '+':
		case '=':
            if (!thresholdSet){
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
            }
			break;
			
		case '-':
            if (!thresholdSet){
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
            }
			break;
            
			
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
        
        case 13:
            thresholdSet=true;
            break;
            
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    for(int i = 0; i < bookReviewSet.size(); i++) {
        if (bookReviewSet.size() !=0) {
            bookReviewSet[i]->scroll(x, y);
        }
    }

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}


void testApp::introScreen() {
    ofBackground(0x000000);
    ofEnableAlphaBlending();
    alfa +=.1;
    if (alfa >360) alfa = 0;
    ofSetColor(0, 255, 0, 255+255*sin(alfa*3.14159/180));
    for (int i = 0; i < 3; i ++) {
        ofRect(1160, 30*i, 10, 20);
    }
    
    for (int i = 1; i < 5; i++) {
        ofRect(1150+ i*30, 70, 20, 10);
    }
    myFont.drawString("Scan book here", 260, 80);
    myFont.drawString("to begin...", 260, 158);
}

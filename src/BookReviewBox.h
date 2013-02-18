//
//  BookReviewBox.h
//  BookReview_Final
//
//  Created by Luis Daniel Palacios on 3/3/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#ifndef BookReview_Final_BookReviewBox_h
#define BookReview_Final_BookReviewBox_h

#include "ofMain.h"
#include "Integrator.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"


class BookReviewBox {
    
public: 
    //constructor
    BookReviewBox(int _x, int _y, string _serial);
    BookReviewBox(string _serial);
    //BookReviewBox(string _serial, ofxCvBlob _blob);
    BookReviewBox();
    ~BookReviewBox();
    
    //other methods
    void display();
    void display(int _x, int _y);
    void update(int _x, int _y);
    void spring();
    void ReplaceAll(string& str, const string& toReplace, const string& replaceWith);
    string wrapString(string text, int width);
    void scroll(int x, int y);
    
    
    //variables
    int x, y, height, width;
    string serial;
    bool sprung;
    Integrator* interpolator;
    int initValue;
    ofxCvBlob blob;
    
    
    
    //--------------text variables--------------
    ofFile file;
    int numLines;
    
    ofBuffer buff;
    ofxXmlSettings book;
    
    string wrapper;
    string editorial;
    string author;
    string stars;
    string product;
    string reviews;
    
    
    
    string beginProduct;
    string endProduct;
    ofTrueTypeFont myFont;   
    ofTrueTypeFont myFontBigger;   

    
    ofRectangle editorialRect;
    ofRectangle authorRect;
    ofRectangle productRect;
    ofRectangle starsRect;
    ofRectangle reviewsRect;
    
    int boxBorder;
    int wrapWidth;
    
    string tempLine;
    int lineNumber;
    int previousLineNum;
    
    float fingerXPos;
    float previousXPos;
    
    
    vector<string> allLines;
    vector<string> tempLines;
    char * cstr, *p;
    
    
};





#endif

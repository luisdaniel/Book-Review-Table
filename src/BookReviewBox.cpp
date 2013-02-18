//
//  BookReviewBox.cpp
//  BookReview_Final
//
//  Created by Luis Daniel Palacios on 3/3/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#include <iostream>
#include "BookReviewBox.h"
#include "ofMain.h"


using namespace std;


BookReviewBox::BookReviewBox(int _x, int _y, string _serial) {
    x = _x;
    y = _y;
    serial = _serial;
    width = 400;
    height = 400;
    sprung = false;
    initValue = 0;
    interpolator = new Integrator(height, .9, .1);
    
    //-----------text------------------
    ofTrueTypeFont::setGlobalDpi(72);
    
    ofFile file;
    file.open(ofToDataPath("0195311450.xml").c_str(), ofFile::ReadOnly, false);
    string buff = file.readToBuffer();  
    ReplaceAll(buff,"\n\n","\n"); 
    ReplaceAll(buff,"\n \n","\n");    
    ReplaceAll(buff,"\n","&#10;"); 
    book.loadFromBuffer(buff);
    
    //read in wrapper instead of buff to make sure lines are already wrapped
    
    wrapper = book.getValue("book:wrapper","");
    wrapWidth=width - 90;
    
    myFont.loadFont("Verdana.ttf", 8, true, true);
    myFont.setLineHeight(10.0f);
     myFontBigger.loadFont("Verdana.ttf",18,true,true);
    wrapper=wrapString(wrapper,wrapWidth);
    
    //converting strings to char array and then separating by new line
    
    cstr = new char[wrapper.size()+1];
    strcpy (cstr, wrapper.c_str());
    p=strtok (cstr,"\n");
    while (p!=NULL)
        
    {
        
        
        
        tempLines.push_back(p);
        
        //cout<<p<<endl;
        
        if (tempLines[tempLines.size()-1] == "Editorial Reviews" || tempLines[tempLines.size()-1]=="About the Author"
            || tempLines[tempLines.size()-1]=="Product Details" || tempLines[tempLines.size()-1]=="Biography"
            || tempLines[tempLines.size()-1]=="Customer Reviews"){
            
            
            
            allLines.push_back("\n");
            
            allLines.push_back(p);
            
            allLines.push_back("\n");
            
            
            
        }else{
            
            allLines.push_back(p);
            
        }
        
        
        
        p=strtok(NULL,"\n");
        
    }    //for (int i=0;i<allLines.size();i++){
        //cout<<i<<endl;
        //cout<<allLines[i]<<endl;
        //cout<<" "<<endl;
    //}
    
    
    
    ofBackground(255,255,255);
    ofEnableSmoothing();
    
    boxBorder=40;
    lineNumber=0;
    previousLineNum=0;
    
    fingerXPos=0.0;
    previousXPos=0.0;
}

BookReviewBox::BookReviewBox(string _serial) {
    serial = _serial;
    width = 200;
    height = 250;
    x = 3000;
    y = 3000;
    sprung = false;
    initValue = 0;
    interpolator = new Integrator(height, .9, .1);
    
    
    //-----------text------------------
    ofTrueTypeFont::setGlobalDpi(72);
    
    ofFile file;
    file.open(ofToDataPath(serial + ".xml").c_str(), ofFile::ReadOnly, false);
    string buff = file.readToBuffer();  
    ReplaceAll(buff,"\n\n","\n"); 
    ReplaceAll(buff,"\n \n","\n");    
    ReplaceAll(buff,"\n","&#10;"); 
    book.loadFromBuffer(buff);
    
    //read in wrapper instead of buff to make sure lines are already wrapped
    
    wrapper = book.getValue("book:wrapper","");
    wrapWidth=width - 70;
    
    myFont.loadFont("Verdana.ttf", 8, true, true);
    myFont.setLineHeight(10.0f);
    myFontBigger.loadFont("Verdana.ttf",18,true,true);
    wrapper=wrapString(wrapper,wrapWidth);
    
    //converting strings to char array and then separating by new line
    
    cstr = new char[wrapper.size()+1];
    strcpy (cstr, wrapper.c_str());
    p=strtok (cstr,"\n");
    while (p!=NULL)
    {
        
        
        
        tempLines.push_back(p);
        
        //cout<<p<<endl;
        
        if (tempLines[tempLines.size()-1] == "Editorial Reviews" || tempLines[tempLines.size()-1]=="About the Author"
            || tempLines[tempLines.size()-1]=="Product Details" || tempLines[tempLines.size()-1]=="Biography"
            || tempLines[tempLines.size()-1]=="Customer Reviews"){
            
            
            
            allLines.push_back("\n");
            
            allLines.push_back(p);
            
            allLines.push_back("\n");
            
            
            
        }else{
            
            allLines.push_back(p);
            
        }
        
        
        
        p=strtok(NULL,"\n");
        
    } 
    //for (int i=0;i<allLines.size();i++){
        //cout<<i<<endl;
        //cout<<allLines[i]<<endl;
        //cout<<" "<<endl;
    //}
    
    
    
    ofBackground(255,255,255);
    ofEnableSmoothing();
    
    boxBorder=40;
    lineNumber=0;
    previousLineNum=0;
    
    fingerXPos=0.0;
    previousXPos=0.0;
    
    
}

BookReviewBox::BookReviewBox() {
    width = 400;
    height = 500;
    sprung = false;
    //do other stuff.
}

BookReviewBox::~BookReviewBox() {
    
}

void BookReviewBox::display() {

    //ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetHexColor(0xCCDACD);
    //ofDrawBitmapString(serial, x, y);
    ofRect(x, y, width, height); 
    

    
    //-----------------text-------------------------
    ofSetColor(0);
    
    //myFont.drawString(wrapper,boxBorder/2,boxBorder/2);
    
    
    
    for (int i=lineNumber;i<allLines.size();i++){
        if (allLines[i] == "Editorial Reviews" || allLines[i]=="About the Author"
            || allLines[i]=="Product Details" || allLines[i]=="Biography"
            || allLines[i]=="Customer Reviews"){
            
            myFontBigger.drawString(allLines[i], x +10, y + 10 + (i-lineNumber)*myFont.getLineHeight());
            
            
            
        }else{
            
            myFont.drawString(allLines[i], x +10, y + 10 + (i-lineNumber)*myFont.getLineHeight());
            
        }
        
    }
}

void BookReviewBox::display(int _x, int _y) {
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetHexColor(0xFFFF00);
    ofRect(_x, _y, width, height);  
    
    
    
    
    //-----------------text-------------------------
    ofSetColor(0);
    //myFont.drawString(wrapper,boxBorder/2,boxBorder/2);
    
    for (int i=lineNumber;i<allLines.size();i++){
        myFont.drawString(allLines[i], _x - width/2 +10, _y - height/2 + 10 + (i-lineNumber)*myFont.getLineHeight());
        //cout<<allLines[i]<<endl;
    }
}


void BookReviewBox::update(int _x, int _y) {
    x = _x;
    y = _y;
}

void BookReviewBox::spring() {
    for (int i = 0; i < height ; i++ ) {
        ofRect(x, y, 5, i); 
    }
    for (int i = 5; i < width - 5; i ++) { 
        ofRect(x, y, i, height);
    }
}



void BookReviewBox::ReplaceAll(string& str, const string& toReplace, const string& replaceWith){
    string::size_type pos = 0;
    while ((pos = str.find(toReplace), pos) != string::npos)
    {
        str.replace(pos, toReplace.size( ), replaceWith);
        pos += replaceWith.size( );
    }
}
//--------------------------------------------------------------

string BookReviewBox::wrapString(string text, int _width) {  
    
    string typeWrapped = "";  
    string tempString = "";  
    vector <string> words = ofSplitString(text, " ");  
    
    for(int i=0; i<words.size(); i++) {  
        
        string wrd = words[i];  
        //cout << wrd << endl;  
        
        tempString += wrd + " ";  
        int stringwidth = myFont.stringWidth(tempString);  
        if(stringwidth >= _width) {  
            tempString = "";  
            typeWrapped += "\n";  
        }  
        
        typeWrapped += wrd + " ";  
    }  
    
    return typeWrapped;  
    
}  


void BookReviewBox::scroll(int x, int y){
    int calculate = height/myFont.getLineHeight();
    //ofGetWidth();
    previousXPos=fingerXPos;
    fingerXPos=y;
    if (fingerXPos-previousXPos <0){
        lineNumber--;
        if (lineNumber<=0){
            lineNumber=0;
        }
    }else if(fingerXPos-previousXPos >0){
        lineNumber++;
        if (lineNumber>=allLines.size()-calculate){
            lineNumber=allLines.size()-calculate;
        }
    }
}




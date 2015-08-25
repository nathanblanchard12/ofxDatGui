//
//  ofxDatGuiButton.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/18/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiButton : public ofxDatGuiItem {

    public:
    
        ofxDatGuiButton(int index, string label) : ofxDatGuiItem(index, label) { }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_CLICKED, mId);
            changeEventCallback(evt);
        }
    
        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
        }
    
        void drawBkgd()
        {
        // anything that extends ofxDatGuiButton has the same rollover effect //
            if (mMouseDown){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_DOWN, 255);
            }   else if (mMouseOver){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_OVER, 255);
            }   else{
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::ROW_BKGD);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+guiWidth && m.y>=y && m.y<= y+mHeight);
        }
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(int index, string label, bool state) : ofxDatGuiButton(index, label)
        {
            mState = state;
            if (!radioOn.isAllocated()) radioOn.load("radio-on.png");
            if (!radioOff.isAllocated()) radioOff.load("radio-off.png");
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            mState = !mState;
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_TOGGLED, mId, mState);
            changeEventCallback(evt);
        }

        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::TOGGLE_STRIPE);
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::LABEL);
                if (mState == true){
                    radioOn.draw(x+radioIconX, y+radioIconY, radioIconSize, radioIconSize);
                }   else{
                    radioOff.draw(x+radioIconX, y+radioIconY, radioIconSize, radioIconSize);
                }
            ofPopStyle();
        }
    
    private:
        bool mState;
        ofImage radioOn;
        ofImage radioOff;

};

class ofxDatGuiToggler : public ofxDatGuiButton {


    public:
    
        ofxDatGuiToggler() : ofxDatGuiButton(9999, "COLLAPSE CONTROLS")
        {
            mIsExpanded = true;
            mHeight = rowHeight*.8;
            setLabel("COLLAPSE CONTROLS");
        }
    
        void draw()
        {
            mLabelX = guiWidth/2 - getStringBoundingBox(mLabel, 0, 0).width/2;
            ofxDatGuiButton::draw();
        }
    
        int getOriginY()
        {
            return originY;
        }
    
        void setOriginY(int y)
        {
            this->y = originY = y;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::GUI_TOGGLED, mId, mIsExpanded);
            changeEventCallback(evt);
            if (mIsExpanded){
                mIsExpanded = false;
                setLabel("EXPAND CONTROLS");
            }   else{
                mIsExpanded = true;
                setLabel("COLLAPSE CONTROLS");
            }
        }
    
        void setLabel(string label)
        {
            mLabel = label;
        }
    
    private:
    
    
    
    
    
};



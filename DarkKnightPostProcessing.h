/*
 Copyright (C) 2018 Luis Fernando García [http://luiscript.com]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef DarkKnightPostProcessing_h
#define DarkKnightPostProcessing_h

#include "module.hpp"
#include "ofxPostProcessing.h"

class DarkKnightPostProcessing : public Module {
    
private:
    
    float alpha;
    ofxPostProcessing post;
    ofFbo * fbo;
    ofFbo mainFbo;
    bool drawFbo = false;
    // ofEasyCam cam;
    
public:
    void setup()
    {
        mainFbo.allocate(getModuleWidth(), getModuleHeight());
        
        mainFbo.begin();
        ofClear(0,0,0,0);
        mainFbo.end();
        
        post.init(getModuleWidth(), getModuleHeight());
        post.createPass<BleachBypassPass>()->setEnabled(false);
        post.createPass<BloomPass>()->setEnabled(false);
        post.createPass<ContrastPass>()->setEnabled(false);
        post.createPass<ConvolutionPass>()->setEnabled(false);
        post.createPass<DofAltPass>()->setEnabled(false);
        post.createPass<DofPass>()->setEnabled(false);
        post.createPass<EdgePass>()->setEnabled(false);
        post.createPass<FakeSSSPass>()->setEnabled(false);
        post.createPass<FxaaPass>()->setEnabled(false);
        post.createPass<GodRaysPass>()->setEnabled(false);
        post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
        post.createPass<HsbShiftPass>()->setEnabled(false);
        post.createPass<KaleidoscopePass>()->setEnabled(false);
        post.createPass<LUTPass>()->setEnabled(false);
        post.createPass<LimbDarkeningPass>()->setEnabled(false);
        post.createPass<NoiseWarpPass>()->setEnabled(false);
        post.createPass<PixelatePass>()->setEnabled(false);
        post.createPass<RGBShiftPass>()->setEnabled(false);
        post.createPass<RimHighlightingPass>()->setEnabled(false);
        post.createPass<SSAOPass>()->setEnabled(false);
        post.createPass<ToonPass>()->setEnabled(false);
        post.createPass<VerticalTiltShifPass>()->setEnabled(false);
        post.createPass<ZoomBlurPass>()->setEnabled(false);
        
    };
    void update()
    {
        
    };
    void draw()
    {
        if(drawFbo)
        {
            mainFbo.begin();
            post.begin();
            fbo->draw(0,0);
            post.end();
            mainFbo.end();
        }
        
    };
    void addModuleParameters()
    {
        gui->addMatrix("FX", 22, true)->onMatrixEvent(this, &DarkKnightPostProcessing::onFxSelected);
    };
    void drawMasterInput()
    {
        drawInputConnection();
    };
    void drawMasterOutput()
    {
        drawOutputConnection();
    }
    void setFbo(ofFbo * fboPtr)
    {
        fbo  = fboPtr;
        drawFbo = fboPtr != nullptr;
    }
    
    ofFbo * getFbo()
    {
        return &mainFbo;
    }
    
    void onFxSelected(ofxDatGuiMatrixEvent e)
    {
        int index = e.child;
        post[index]->setEnabled(e.enabled);
    }
};

#endif /* DarkKnightPostProcessing_h */

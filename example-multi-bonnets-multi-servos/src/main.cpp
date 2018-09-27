#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
#else
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
#endif
    
    settings.setSize(1150,800);
    settings.windowMode = OF_WINDOW;
    
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class crystalDLAApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void crystalDLAApp::setup()
{
}

void crystalDLAApp::mouseDown( MouseEvent event )
{
}

void crystalDLAApp::update()
{
}

void crystalDLAApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( crystalDLAApp, RendererGl )

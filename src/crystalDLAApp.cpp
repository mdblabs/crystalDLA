#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "cinder/TriMesh.h"

#include "cinder/ImageIo.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"




using namespace ci;
using namespace ci::app;
using namespace std;

CameraPersp mCam;

class testCinderApp : public AppBasic {
public:
    
    CameraPersp mCam;
    Vec3f mEye;
    Vec3f mCenter;
    Vec3f mUp;
    float mCameraDistance;
    
    params::InterfaceGlRef mParams;
    Quatf mSceneRotation;
    
    
    void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
};

void testCinderApp::prepareSettings(Settings *settings)
{
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.0f);
}


void testCinderApp::setup()
{
    mCameraDistance=500.0f;
    mEye = Vec3f(0.0f,0.0f,mCameraDistance);
    mCenter = Vec3f::zero();
    mUp = Vec3f::yAxis();
    mCam.setPerspective(60.0f, getWindowAspectRatio(), 5.0f, 3000.0f);
    
    mParams = params::InterfaceGl::create( "Flocking", Vec2i( 225, 200 ) );
    mParams->addParam( "Scene Rotation", &mSceneRotation,"opened=1");
    mParams->addSeparator();
    mParams->addParam("Eye Distance", &mCameraDistance,"min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w");
    
    
    
}

void testCinderApp::update()
{
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCam.lookAt(mEye,mCenter,mUp);
    gl::setMatrices(mCam);
    gl::rotate( mSceneRotation );
    
}

void testCinderApp::draw()
{
    TriMesh mesh;

    gl::clear( Color( 0, 0, 0 ) );
    mParams->draw();
    
    // Create the points of our cube
    Vec3f v0(-100,-100,-100);
    Vec3f v1( 100,-100,-100);
    Vec3f v2( 100, 100,-100);
    Vec3f v3(-100, 100,-100);
    Vec3f v4(-100,-100, 100);
    Vec3f v5( 100,-100, 100);
    Vec3f v6( 100, 100, 100);
    Vec3f v7(-100, 100, 100);
    
    // Create the colors for each vertex
    ColorA c0( 0, 0.5, 0.5, 0.1);
    ColorA c1( 0, 0.9, 0.9, 1);
    
    Vec3f faces[6][4] = { /* Vertices for the 6 faces of a cube. */
        {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
        {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3} };
    
    for (int i = 0; i < 3; i++)
    {
        
        mesh.appendVertex(faces[i][0]);
        mesh.appendColorRgba(c0);
        mesh.appendVertex(faces[i][1]);
        mesh.appendColorRgba(c0);
        mesh.appendVertex(faces[i][2]);
        mesh.appendColorRgba(c0);
        mesh.appendVertex(faces[i][3]);
        mesh.appendColorRgba(c0);
        
        int numberVertices = mesh.getNumVertices();
        
        mesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
        mesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );
        
    }
    
    for (int i = 3; i < 6; i++)
    {
        
        mesh.appendVertex(faces[i][0]);
        mesh.appendColorRgba(c1);
        mesh.appendVertex(faces[i][1]);
        mesh.appendColorRgba(c1);
        mesh.appendVertex(faces[i][2]);
        mesh.appendColorRgba(c1);
        mesh.appendVertex(faces[i][3]);
        mesh.appendColorRgba(c1);
        
        int numberVertices = mesh.getNumVertices();
        
        mesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
        mesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );
        
    }

    
    gl::enableAlphaBlending();
    gl::draw(mesh);
    gl::disableAlphaBlending();
    
}

CINDER_APP_BASIC( testCinderApp, RendererGl )

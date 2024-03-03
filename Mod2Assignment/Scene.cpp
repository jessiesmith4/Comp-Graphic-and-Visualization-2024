#include "Scene.h"
#include "Shapes.h"
#include "mesh.h"

using namespace std;

/*
* Instead of using the same mesh for each shape,
* each shape will have its own mesh for separate rotations
* It also makes it much easier to keep the project organized
*/

void Scene::UBuildScene(vector<GLMesh>& scene)
{

	srand(time(nullptr));

	/*** PHONE ***/
// Phone base
	GLMesh phoneBase;
	phoneBase.p = {
		1.0f,  1.0f,  1.0f, 1.0f,  // Colors
		1.0f,  1.0f,  1.0f,		   // Scales
		0.0f,  1.0f,  0.0f, 0.0f,  // x rotation
	   -45.0f, 0.0f,  1.0f, 0.0f,  // y rotations
		0.0f,  0.0f,  0.0f, 1.0f,  // z rotation
	   -1.0f,  0.0f,  -2.0f,       // Translations
		1.0f,  1.0f				   // Texture scales
	};
	phoneBase.width = 4.0f;	phoneBase.height = 0.5f;	phoneBase.numOfSides = 6.0f;
	phoneBase.texFilename = "gray_blue.jpg";
	Shapes::UBuildPhone(phoneBase);
	scene.push_back(phoneBase);

	// Camera base
	GLMesh camBase;
	camBase.p = {
		1.0f,  1.0f,  1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,
		0.0f,  1.0f,  0.0f, 0.0f,
	   -45.0f, 0.0f,  1.0f, 0.0f,
		0.0f,  0.0f,  0.0f, 1.0f,
	   -1.7f, 0.0f, -1.0f,
		1.0f,  1.0f
	};
	camBase.width = 4.0f;	camBase.height = 0.5f;	camBase.numOfSides = 6.0f;
	camBase.texFilename = "dark_blue.jpg";
	Shapes::UBuildCamBase(camBase);
	scene.push_back(camBase);

	// Camera 1
	GLMesh cam1;
	cam1.p = {
		1.0f,  1.0f,   1.0f, 1.0f,
		0.15f, 0.15f,  0.15f,
		0.0f, 1.0f,   0.0f, 0.0f,
		0.0f,  0.0f,   1.0f, 0.0f,
		0.0f,  0.0f,   0.0f, 1.0f,
	   -1.8f, 0.13f, -0.925f,
		1.0f,  1.0f
	};
	cam1.height = 0.03f, cam1.radius = 0.5f, cam1.numOfSides = 16.0f;
	cam1.texFilename = "cams.jpg";
	Shapes::UBuildCylinder(cam1);
	scene.push_back(cam1);

	// Camera 2
	GLMesh cam2;
	cam2.p = {
		1.0f,  1.0f,   1.0f, 1.0f,
		0.15f, 0.15f,  0.15f,
		0.0f, 1.0f,   0.0f, 0.0f,
		0.0f,  0.0f,   1.0f, 0.0f,
		0.0f,  0.0f,   0.0f, 1.0f,
	   -1.65f, 0.13f, -1.075f,
		1.0f,  1.0f
	};
	cam2.height = 0.03f, cam2.radius = 0.5f, cam2.numOfSides = 16.0f;
	cam2.texFilename = "cams.jpg";
	Shapes::UBuildCylinder(cam2);
	scene.push_back(cam2);

	// Camera 3
	GLMesh cam3;
	cam3.p = {
		1.0f,  1.0f,   1.0f, 1.0f,
		0.15f, 0.15f,  0.15f,
		0.0f, 1.0f,   0.0f, 0.0f,
		0.0f,  0.0f,   1.0f, 0.0f,
		0.0f,  0.0f,   0.0f, 1.0f,
       -1.85f, 0.13f, -1.13f,
		1.0f,  1.0f
	};
	cam3.height = 0.03f, cam3.radius = 0.5f, cam3.numOfSides = 16.0f;
	cam3.texFilename = "cams.jpg";
	Shapes::UBuildCylinder(cam3);
	scene.push_back(cam3);




		/*** PLANE ***/
	GLMesh plane;
	plane.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		4.0f, 2.0f, 4.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f
	};
	plane.texFilename = "dark_gray.jpg";
	Shapes::UBuildPlane(plane);
	scene.push_back(plane);



		/*** WATER BOTTLE ***/
	// Water bottle base
	GLMesh waterBottle;
	waterBottle.p = {
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f,
		0.0f, 0.0f, -0.25f,
		1.0f, 1.0f
	};
	waterBottle.height = 2.15f;	waterBottle.radius = 0.375f;	waterBottle.numOfSides = 32.0f;
	waterBottle.texFilename = "green.jpg";
	Shapes::UBuildCylinder(waterBottle);
	scene.push_back(waterBottle);

	// Water bottle cone-ish area under lid
	GLMesh waterBottle2;
	waterBottle2.p = {
		1.0f, 1.0f,   1.0f, 1.0f,
		1.0f, 1.0f,   1.0f,
		0.0f, 1.0f,   0.0f, 0.0f,
		0.0f, 0.0f,   1.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 1.0f,
		0.0f, 2.15f, -0.25f,
		1.0f, 1.0f
	};
	waterBottle2.height = 0.35f, waterBottle2.radius = 0.375f, waterBottle2.numOfSides = 32.0f;
	waterBottle2.texFilename = "green.jpg";
	Shapes::UBuildCone(waterBottle2);
	scene.push_back(waterBottle2);

	// Water bottle lid
	GLMesh bottleLid;
	bottleLid.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 2.25f, -0.25f,
		1.0f, 1.0f
	};
	bottleLid.height = 0.3f, bottleLid.radius = 0.25f, bottleLid.numOfSides = 32.0f;
	bottleLid.texFilename = "dark_green.jpg";
	Shapes::UBuildCylinder(bottleLid);
	scene.push_back(bottleLid);

	

		/*** MAGIC 8-BALL ***/
	GLMesh sphere;
	sphere.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.7f, -1.0f,
		1.0f, 1.0f
	};
	sphere.radius = 0.8f;
	sphere.numOfSlices = 180.0f;
	sphere.numOfStacks = 180.0f;
	sphere.texFilename = "dark_gray.jpg";
	Shapes::UBuildSphere(sphere);
	scene.push_back(sphere);

	

	/*** XBOX CONTROLLER ***/
	// Controller base
	GLMesh contBase;
	contBase.p = {
		1.0f,  1.0f,  1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,
		0.0f,  1.0f,  0.0f, 0.0f,
		45.0f, 0.0f,  1.0f, 0.0f,
		0.0f,  0.0f,  0.0f, 1.0f,
	   -1.5f,  0.0f,  0.35f,
		1.0f,  1.0f	
	};
	contBase.width = 4.5f; contBase.height = 2.0f; contBase.numOfSides = 6.0f;
	contBase.texFilename = "white.jpg";
	Shapes::UBuildContBase(contBase);
	scene.push_back(contBase);

	// Base for joy stick
	GLMesh joyBase1;
	joyBase1.p = {
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f,
	   -2.0f, 0.5f, -0.35f,
		1.0f, 1.0f
	};
	joyBase1.height = 0.01f; joyBase1.radius = 0.15f; joyBase1.numOfSides = 16.0f;
	joyBase1.texFilename = "dark_gray.jpg";
	Shapes::UBuildCylinder(joyBase1);
	scene.push_back(joyBase1);

	// Base for second joy stick
	GLMesh joyBase2;
	joyBase2.p = {
		1.0f,  1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,
		0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	   -1.43f, 0.5f, 0.8f,
		1.0f,  1.0f
	};
	joyBase2.height = 0.01f; joyBase2.radius = 0.15f; joyBase2.numOfSides = 16.0f;
	joyBase2.texFilename = "dark_gray.jpg";
	Shapes::UBuildCylinder(joyBase2);
	scene.push_back(joyBase2);

	// Joy stick
	GLMesh joyStick1;
	joyStick1.p = {
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f,
	   -2.0f, 0.5f, -0.35f,
		1.0f, 1.0f
	};
	joyStick1.height = 0.1f; joyStick1.radius = 0.05f; joyStick1.numOfSides = 16.0f;
	joyStick1.texFilename = "dark_gray.jpg";
	Shapes::UBuildCylinder(joyStick1);
	scene.push_back(joyStick1);

	// Second joy stick
	GLMesh joyStick2;
	joyStick2.p = {
		1.0f,  1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,
		0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	   -1.43f, 0.5f, 0.8f,
		1.0f,  1.0f
	};
	joyStick2.height = 0.1f; joyStick2.radius = 0.05f; joyStick2.numOfSides = 16.0f;
	joyStick2.texFilename = "dark_gray.jpg";
	Shapes::UBuildCylinder(joyStick2);
	scene.push_back(joyStick2);

	// Top of joy stick
	GLMesh joyTop1;
	joyTop1.p = {
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f,
	   -2.0f, 0.6f, -0.35f,
		1.0f, 1.0f
	};
	joyTop1.height = 0.05f; joyTop1.radius = 0.1f; joyTop1.numOfSides = 16.0f;
	joyTop1.texFilename = "black.jpg";
	Shapes::UBuildCylinder(joyTop1);
	scene.push_back(joyTop1);

	// Top of second joy stick
	GLMesh joyTop2;
	joyTop2.p = {
		1.0f,  1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,
		0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	   -1.43f, 0.6f, 0.8f,
		1.0f,  1.0f
	};
	joyTop2.height = 0.05f; joyTop2.radius = 0.1f; joyTop2.numOfSides = 16.0f;
	joyTop2.texFilename = "black.jpg";
	Shapes::UBuildCylinder(joyTop2);
	scene.push_back(joyTop2);

	// D-pad
	GLMesh dPad;
	dPad.p = {
		1.0f,  1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,
		0.0f,  1.0f, 0.0f, 0.0f,
		45.0f, 0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	   -2.5f,  0.5f, 0.45f,
		1.0f,  1.0f
	};
	dPad.height = 0.01f; dPad.radius = 0.15f; dPad.numOfSides = 8.0f;
	dPad.texFilename = "dark_gray.jpg";
	Shapes::UBuildCylinder(dPad);
	scene.push_back(dPad);

	// Y button
	GLMesh yBut;
	yBut.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	   -1.0f, 0.5f, 0.4f,
		1.0f, 1.0f
	};
	yBut.height = 0.01f; yBut.radius = 0.05f; yBut.numOfSides = 16.0f;
	yBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(yBut);
	scene.push_back(yBut);

	// A button
	GLMesh aBut;
	aBut.p = {
		1.0f,   1.0f, 1.0f, 1.0f,
		1.0f,   1.0f, 1.0f,
		0.0f,   1.0f, 0.0f, 0.0f,
		0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,   0.0f, 0.0f, 1.0f,
	   -1.175f, 0.5f, 0.575f,
		1.0f,   1.0f
	};
	aBut.height = 0.01f; aBut.radius = 0.05f; aBut.numOfSides = 16.0f;
	aBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(aBut);
	scene.push_back(aBut);

	// X button
	GLMesh xBut;
	xBut.p = {
		1.0f,  1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,
		0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
	   -1.18f, 0.5f, 0.4f,
		1.0f,  1.0f
	};
	xBut.height = 0.01f; xBut.radius = 0.05f; xBut.numOfSides = 16.0f;
	xBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(xBut);
	scene.push_back(xBut);

	// B button
	GLMesh bBut;
	bBut.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	   -1.0f, 0.5f, 0.575f,
		1.0f, 1.0f
	};
	bBut.height = 0.01f; bBut.radius = 0.05f; bBut.numOfSides = 16.0f;
	bBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(bBut);
	scene.push_back(bBut);

	// XBOX button
	GLMesh xboxBut;
	xboxBut.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	   -1.5f, 0.5f, 0.0f,
		1.0f, 1.0f
	};
	xboxBut.height = 0.01f; xboxBut.radius = 0.1f; xboxBut.numOfSides = 16.0f;
	xboxBut.texFilename = "black.jpg";
	Shapes::UBuildCylinder(xboxBut);
	scene.push_back(xboxBut);

	// View button
	GLMesh viewBut;
	viewBut.p = {
		1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f,
	   -1.8f, 0.5f, -0.035f,
		1.0f, 1.0f
	};
	viewBut.height = 0.01f; viewBut.radius = 0.025f; viewBut.numOfSides = 16.0f;
	viewBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(viewBut);
	scene.push_back(viewBut);

	// Menu button
	GLMesh menuBut;
	menuBut.p = {
		1.0f,   1.0f, 1.0f, 1.0f,
		1.0f,   1.0f, 1.0f,
		0.0f,   1.0f, 0.0f, 0.0f,
		0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,   0.0f, 0.0f, 1.0f,
	   -1.465f, 0.5f, 0.3f,
		1.0f,   1.0f
	};
	menuBut.height = 0.01f; menuBut.radius = 0.025f; menuBut.numOfSides = 16.0f;
	menuBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(menuBut);
	scene.push_back(menuBut);

	// Button that changes color of XBOX button
	GLMesh colorBut;
	colorBut.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	   -1.75f, 0.5f, 0.25f,
		1.0f, 1.0f
	};
	colorBut.height = 0.01f; colorBut.radius = 0.025f; colorBut.numOfSides = 16.0f;
	colorBut.texFilename = "white.jpg";
	Shapes::UBuildCylinder(colorBut);
	scene.push_back(colorBut);

	// Light that indicates power of controller
	GLMesh powerInd;
	powerInd.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	   -1.65f, 0.5f, 0.15f,
		1.0f, 1.0f
	};
	powerInd.height = 0.01f; powerInd.radius = 0.01f; powerInd.numOfSides = 16.0f;
	powerInd.texFilename = "black.jpg";
	Shapes::UBuildCylinder(powerInd);
	scene.push_back(powerInd);

	// Handle
	GLMesh handle1;
	handle1.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		115.0f, 0.0f, 0.0f, 1.0f,
		-1.75f, -0.25f, 0.85f,
		1.0f, 1.0f
	};
	handle1.height = 0.55f; handle1.radius = 0.25f; handle1.numOfSides = 16.0f;
	handle1.texFilename = "black.jpg";
	Shapes::UBuildCylinder(handle1);
	scene.push_back(handle1);

	// Handle end
	GLMesh handleEnd1;
	handleEnd1.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		115.0f, 0.0f, 0.0f, 1.0f,
		-2.25f, -0.25f, 1.079f,
		1.0f, 1.0f
	};
	handleEnd1.height = 0.2f; handleEnd1.radius = 0.25f; handleEnd1.numOfSides = 16.0f;
	handleEnd1.texFilename = "black.jpg";
	Shapes::UBuildCone(handleEnd1);
	scene.push_back(handleEnd1);

	// Second handle
	GLMesh handle2;
	handle2.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-25.0f, 0.0f, 0.0f, 1.0f,
		-1.55f, -0.25f, 1.80f,
		1.0f, 1.0f
	};
	handle2.height = 0.55f; handle2.radius = 0.25f; handle2.numOfSides = 16.0f;
	handle2.texFilename = "black.jpg";
	Shapes::UBuildCylinder(handle2);
	scene.push_back(handle2);

	// Second handle end
	GLMesh handleEnd2;
	handleEnd2.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		155.0f, 0.0f, 0.0f, 1.0f,
		-0.635f, -0.25f, 2.2155f,
		1.0f, 1.0f
	};
	handleEnd2.height = 0.2f; handleEnd2.radius = 0.25f; handleEnd2.numOfSides = 16.0f;
	handleEnd2.texFilename = "black.jpg";
	Shapes::UBuildCone(handleEnd2);
	scene.push_back(handleEnd2);
}

#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>

#include "Shapes.h"

using namespace std;

/*
* These functions are used to build the shapes,
* instead of having all of it on the main cpp file
*/


// Function to build the phone base
// FIXME: Need to just make UBuildCube function for both phone base and cam base
void Shapes::UBuildPhone(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		-0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		-0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,
		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	1.0f,
		-0.5f,	0.1f,  -0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,
		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

		-0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,
		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.1f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	0.1f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,




	};

	UTranslator(mesh);
}


// Function to build cam base
void Shapes::UBuildCamBase(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };
	mesh.v = {
		0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,	
		-0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		-0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		-0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.2f,	0.1f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.2f,	0.1f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		-0.2f,	0.1f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		0.2f,	0.1f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,
		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	1.0f,	1.0f,
		-0.2f,	0.12f,  -0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.2f,	0.1f,	0.2f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.2f,	0.1f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,	
		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

		-0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,
		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.2f,	0.12f,	0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.2f,	0.12f,	-0.2f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

	};

	UTranslator(mesh);

}

// Function to build cylinders (so far used to make the cameras on the phone)
void Shapes::UBuildCylinder(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float h = mesh.height;
	float s = mesh.numOfSides;


	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.125f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,			// x
										0.0f ,										// y
										0.5f + r * sin(i * sectorStep) ,			// z
										c[0], -1.0f, c[2], 1.0f,						// color data r g b a
										0.5f + (0.5f * cos((i)*sectorStep)) ,		// texture x; adding the origin for proper alignment
										(0.125f + (0.125f * sin((i)*sectorStep))) });		// texture y


		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,						// color data r g b a
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										(0.125f + (0.125f * sin((i + 1) * sectorStep))) });


	}

	for (auto i = 1; i < s + 1; i++)
	{

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;
		// triangle fan, top
		v.insert(v.end(), { 0.5f, h, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.875f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,										// build this fan the 'l' value away from the other fan
										0.5f + r * sin(i * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,					// color data r g b a
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										0.875f + (0.125f * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,					// color data r g b a
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										0.875f + (0.125f * sin((i + 1) * sectorStep)) });
	}

	// since all side triangles have the same points as the fans above, the same calculations are used
	// to wrap the texture around the cylinder, the calculated points are used to determine which section of
	// the texture to clamp to the corresponding point.
	constexpr float x = 1.0f;
	float j = 1.0f / (s / x);	// for calculating texture location; change 'x' to increase or decrease how many times the texture wraps around the cylinder
	float k = 0.0f;				// for texture clamping

	// sides
	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k,
										0.25f });
		k += j;
	}

	mesh.v = v;
	v.clear();
	UTranslator(mesh);

}


// Builds cone
void Shapes::UBuildCone(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float l = mesh.height;
	float s = mesh.numOfSides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;
	const float textStep = 1.0f / s;
	float textureXLoc = 0.0f;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++) {

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;

		v.insert(v.end(), { 0.5f, 0.0f, 0.5f, c[0], -1.0f, c[2], c[3], 0.5f, 0.25f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep), 0.0f, 0.5f + r * sin(i * sectorStep), c[0], -1.0f, c[2], c[3], 0.5f + (r * cos((i)*sectorStep)), 0.25f + (0.25f * sin((i)*sectorStep))});
		v.insert(v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)), 0.0f, 0.5f + (r * sin((i + 1) * sectorStep)), c[0], -1.0f, c[2], c[3], 0.5f + (r * cos((i + 1) * sectorStep)),0.25f + (0.25f * sin((i + 1) * sectorStep))});


		v.insert(v.end(), { 0.5f + (r * cos(i * sectorStep)), 0.0f, 0.5f + (r * sin(i * sectorStep)), c[0], 1.0f, c[2], c[3], textureXLoc, 0.5f});
		v.insert(v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)), 0.0f, 0.5f + (r * sin((i + 1) * sectorStep)), c[0], 1.0f, c[2], c[3], textureXLoc + textStep, 0.5f});
		v.insert(v.end(), { 0.5f , l , 0.5f , c[0], 1.0f, c[2], c[3], textureXLoc + (textStep / 2), 1.0f });

		textureXLoc = 0.0f;

	}

	mesh.v = v;
	v.clear();

	UTranslator(mesh);
}


// Function to build sphere
void Shapes::UBuildSphere(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float radius = mesh.radius;
	float numOfSlices = mesh.numOfSlices;
	float numOfStacks = mesh.numOfStacks;
	float PI = 3.14f;

	float x, y, z, xy;

	float sectorStep = 2 * PI / numOfSlices;
	float stackStep = PI / numOfStacks;
	float sectorAngle, stackAngle;

	vector<float> v;

	for (int i = 0; i <= numOfStacks; ++i)
	{
		stackAngle = PI / 2.0f - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= numOfSlices; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);

			v.insert(v.end(), { x, y, z, c[0], c[1], c[2], c[3], x + (radius * cosf((i)*sectorStep)), y + (y * sinf((i)) * sectorStep)});
			x = xy * cosf((i + 1) * sectorStep);
			y = xy * sinf((i + 1) * sectorStep);
			v.insert(v.end(), { x, y, z, c[0], c[1], c[2], c[3], x + (radius * cosf((i)*sectorStep)), y + (y * sinf((i)) * sectorStep)});
			
		}
	}
	

	mesh.v = v;
	v.clear();
	UTranslator(mesh);
}



void Shapes::UBuildContBase(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		 0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		-0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		-0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	1.0f,
		0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,
		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,

		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	0.5f,
		0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.5f,	1.0f,
		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	1.0f,
		-0.5f,	0.5f,  -0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.0f,	1.5f,	c[0],	c[1],	c[2],	c[3],	1.0f,	0.5f,
		-0.5f,	0.0f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	0.5f,
		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.75f,	1.0f,

		-0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,
		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

		-0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.0f,
		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,

		-0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.0f,	0.5f,
		0.5f,	0.5f,	1.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.0f,
		0.5f,	0.5f,	-0.5f,	c[0],	c[1],	c[2],	c[3],	0.25f,	0.5f,

	};

	UTranslator(mesh);
}



// Function to build plane
void Shapes::UBuildPlane(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		-1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.0f, 1.0f,
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,
		-1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.0f, 0.0f,

		-1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.0f, 1.0f,
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,
		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,

		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,
		 0.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 0.5f, 0.0f,
		 1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 1.0f, 0.0f,

		 0.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 0.5f, 1.0f,
		 1.0f, 0.0f, 1.0f, c[0], c[1], c[2], c[3], 1.0f, 0.0f,
		 1.0f, 0.0f, -1.0f, c[0], c[1], c[2], c[3], 1.0f, 1.0f,

	};

	UTranslator(mesh);

}


void Shapes::UTranslator(GLMesh& mesh)
{
	constexpr GLuint floatsPerVertex = 3;
	constexpr GLuint floatsPerColor = 4;
	constexpr GLuint floatsPerUV = 2;

	mesh.nIndices = mesh.v.size() / (floatsPerVertex + floatsPerUV + floatsPerColor);

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	
	glBufferData(
		GL_ARRAY_BUFFER,
		mesh.v.size() * sizeof(float),
		&mesh.v.front(),
		GL_STATIC_DRAW
	); 

	// Strides between vertex coordinates
	constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV + floatsPerColor);

	// Create Vertex Attribute POinters
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Scales the object
	mesh.scale = glm::scale(glm::vec3(mesh.p[4], mesh.p[5], mesh.p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);

	// Rotates the object
	mesh.xrotation = glm::rotate(rot, glm::radians(mesh.p[7]), glm::vec3(mesh.p[8], mesh.p[9], mesh.p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(mesh.p[11]), glm::vec3(mesh.p[12], mesh.p[13], mesh.p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(mesh.p[15]), glm::vec3(mesh.p[16], mesh.p[17], mesh.p[18]));

	mesh.translation = glm::translate(glm::vec3(mesh.p[19], mesh.p[20], mesh.p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	mesh.gUVScale = glm::vec2(2.0f, 2.0f);

}
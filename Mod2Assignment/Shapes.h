#pragma once

/* HEADER FILE FOR SHAPE BUILDING FUNCTIONS */

#include "mesh.h"

using namespace std;

class Shapes
{
public:
	static void UBuildPhone(GLMesh& mesh);
	static void UBuildCamBase(GLMesh& mesh);
	static void UBuildCylinder(GLMesh& mesh);
	static void UBuildCone(GLMesh& mesh);
	static void UBuildSphere(GLMesh& mesh);
	static void UBuildContBase(GLMesh& mesh);
	static void UBuildPlane(GLMesh& mesh);
	static void UTranslator(GLMesh& mesh);
};
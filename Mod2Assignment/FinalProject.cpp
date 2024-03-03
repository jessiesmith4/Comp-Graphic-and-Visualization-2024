#include <iostream>
#include <vector>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shapes.h"
#include "mesh.h"
#include "Scene.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 

// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

/*
* Jessie Smith
* CS 330
* SNHU
* 26 February 2024
* 
* FINAL PROJECT
*/


using namespace std;

// Window title
const char* const WINDOW_TITLE = "Final Project - Jessie Smith";

// Width and height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Mesh to hold light data
struct GLightMesh
{
	GLuint vao;
	GLuint vbo;
	GLuint nVertices;
};

GLightMesh flashLight;
GLightMesh roomLight;

Shapes builder;

// Main GLFW window
GLFWwindow* gWindow = nullptr;
// Shader program
GLuint gProgramId;
// Light shader program
GLuint gLightProgramId;
// Scene vector
vector<GLMesh> scene;
// For perspective change to ortho
bool gPerspective = false;
// For orbiting flash light
bool gFlashLightOrbit = false;


// Camera
Camera gCamera(glm::vec3(-5.5f, 4.5f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, -30.0f);
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// Timing
float gDeltaTime = 0.0f;
float gLastFrame = 0.0f;

// Flash from phone light
glm::vec3 gFlashLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 gFlashLightPos(-5.7f, 4.5f, -0.3f); // Flash light starts directly behind the camera
glm::vec3 gFlashLightScale(0.1f);

// Room light
glm::vec3 gRoomLightColor(1.0f, 1.0f, 0.0f); // Has a slight yellowish color
glm::vec3 gRoomLightPos(0.0f, 7.0f, -9.0); // Room light is higher up and to the left of the scene
glm::vec3 gRoomLightScale(0.3f);

bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void URender(vector<GLMesh> scene);
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);
void UDestroyTexture(GLuint textureId);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
bool UCreateTexture(const char* filename, GLuint& textureId);
void UCreateLightMesh(GLightMesh& lightMesh);

// Vertex shader source code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 normal;
	layout(location = 2) in vec2 textureCoordinate;

	out vec3 vertexNormal;
	out vec3 vertexFragmentPos;
	out vec2 vertexTextureCoordinate;
	
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(position, 1.0f);
		vertexFragmentPos = vec3(model * vec4(position, 1.0f));
		vertexNormal = mat3(transpose(inverse(model))) * normal;
		vertexTextureCoordinate = textureCoordinate;
	}
);

// Shape Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,

	in vec3 vertexFragmentPos;
	in vec3 vertexNormal;
	in vec2 vertexTextureCoordinate;

	out vec4 fragmentColor;

	uniform vec3 objectColor;
	uniform vec3 lightColor;
	uniform vec3 roomLightColor;
	uniform vec3 lightPos;
	uniform vec3 roomLightPos;
	uniform vec3 viewPosition;

	uniform sampler2D uTexture;
	uniform vec2 uvScale;

	void main()
	{
		float flashStrength = 0.7f;
		float roomStrength = 0.1f; // Room light is dimmer, but still shows the yellowish tint
		vec3 flash = flashStrength * lightColor;
		vec3 room = roomStrength * roomLightColor;
			
		vec3 norm = normalize(vertexNormal);
		vec3 lightDirection = normalize(lightPos - vertexFragmentPos);
		vec3 roomLightDirection = normalize(roomLightPos - vertexFragmentPos);

		float impact = max(dot(norm, lightDirection), 0.0);
		float roomImpact = max(dot(norm, roomLightDirection), 0.0);
	
		vec3 diffuse = impact * lightColor;
		vec3 roomDiffuse = roomImpact * roomLightColor;

		float specularIntensity = 0.4f;
		float highlightSize = 16.0f;
		vec3 viewDir = normalize(viewPosition - vertexFragmentPos);
		vec3 reflectDir = reflect(-lightDirection, norm);
		
		float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
		vec3 specular = specularIntensity * specularComponent * lightColor;
		vec3 roomSpecular = specularIntensity * specularComponent * roomLightColor;

		vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

		vec3 phong = (flash + room + diffuse + roomDiffuse + specular) * textureColor.xyz;

		fragmentColor = vec4(phong, 1.0);

	}
);

// Light vertex shader source code
const GLchar* lampVertexShaderSource = GLSL(440,
	layout(location = 0) in vec3 position;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(position, 1.0f);
	}
);

// Light fragment shader source code
const GLchar* lampFragmentShaderSource = GLSL(440,
	out vec4 fragmentColor;
	
	void main()
	{
		fragmentColor = vec4(1.0f);
	}
);


void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
	for (int j = 0; j < height / 2; ++j)
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;

		for (int i = width * channels; i > 0; --i)
		{
			unsigned char tmp = image[index1];
			image[index1] = image[index2];
			image[index2] = tmp;
			++index1;
			++index2;
		}
	}
}



// Main
int main(int argc, char* argv[])
{
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	Scene::UBuildScene(scene);

	for (auto& m : scene)
	{
		if (!UCreateTexture(m.texFilename, m.textureId))
		{
			cout << "Failed to load texture " << m.texFilename << endl;
			return EXIT_FAILURE;
		}

		if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source, gProgramId))
			return EXIT_FAILURE;
	}

	if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLightProgramId))
		return EXIT_FAILURE;

	UCreateLightMesh(flashLight);
	UCreateLightMesh(roomLight);
	
	glUseProgram(gProgramId);
	glUniform1i(glGetUniformLocation(gProgramId, "uTexture"), 0);

	// Render loop
	while (!glfwWindowShouldClose(gWindow))
	{
		// Background will be black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Per-frame timing
		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;

		// Input
		UProcessInput(gWindow);

		// Render rame
		URender(scene);

		glfwPollEvents();

	}

	// Release mesh data
	for (auto& m : scene)
	{
		UDestroyMesh(m);
	}

	// Clear scene
	scene.clear();

	// Release shader program
	UDestroyShaderProgram(gProgramId);
	UDestroyShaderProgram(gLightProgramId);

	exit(EXIT_SUCCESS);

}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	// Initialize and configure GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Window creation
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}


bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
	// Compilation and linkage error reporting
	int success = 0;
	char infoLog[512];

	// Create a Shader program object.
	programId = glCreateProgram();

	// Create the vertex and fragment shader objects
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrive the shader source
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	// Compile the vertex shader, and print compilation errors
	glCompileShader(vertexShaderId);
	// Check for shader compile errors
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glCompileShader(fragmentShaderId);
	// Check for shader compile errors
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	// Attached compiled shaders to the shader program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);
	// Check for linking errors
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glUseProgram(programId);

	return true;
}


// Processes input from mouse and keys
void UProcessInput(GLFWwindow* window)
{
	// ESC to end program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// W = forward, S = backward, A = left, D = right
	// E = up, Q = down
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(DOWN, gDeltaTime);

	// P = perspective, O = ortho
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		gPerspective = false;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		gPerspective = true;

	// L = orbit, K = still light
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		gFlashLightOrbit = true;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		gFlashLightOrbit = false;

}


void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


// Mouse movement
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (gFirstMouse)
	{
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}

	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos;

	gLastX = xpos;
	gLastY = ypos;

	gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// Mouse wheel scroll
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Changes camera speed
	gCamera.ProcessMouseScroll(yoffset);
}


// Mouse button events
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "LP" << endl;
		else
			cout << "LR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "MP" << endl;
		else
			cout << "MR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "RP" << endl;
		else
			cout << "RR" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// Render a freame
void URender(vector<GLMesh> scene)
{
	// Flash can orbit
	constexpr float angularVelocity = glm::radians(45.0f);
	if (gFlashLightOrbit)
	{
		glm::vec4 newPosition = glm::rotate(angularVelocity * gDeltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(gFlashLightPos, 1.0f);
		gFlashLightPos.x = newPosition.x;
		gFlashLightPos.y = newPosition.y;
		gFlashLightPos.z = newPosition.z;
	}

	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Background will be black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Transform camera
	glm::mat4 view = gCamera.GetViewMatrix();

	// Choose between perspective and ortho
	glm::mat4 projection;
	if (!gPerspective)
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	else
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		glBindVertexArray(mesh.vao);

		// Set shader program
		glUseProgram(gProgramId);

		GLint modelLocation = glGetUniformLocation(gProgramId, "model");
		GLint viewLocation = glGetUniformLocation(gProgramId, "view");
		GLint projLocation = glGetUniformLocation(gProgramId, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		GLint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");

		// Flash
		GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
		GLint lightPositionLoc = glGetUniformLocation(gProgramId, "lightPos");

		// Room
		GLint keyLightColorLoc = glGetUniformLocation(gProgramId, "roomLightColor");
		GLint keyLightPositionLoc = glGetUniformLocation(gProgramId, "roomLightPos");

		// Camera
		GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");

		glUniform3f(objectColorLoc, mesh.p[0], mesh.p[1], mesh.p[2]);

		// Flash
		glUniform3f(lightColorLoc, gFlashLightColor.r, gFlashLightColor.g, gFlashLightColor.b);
		glUniform3f(lightPositionLoc, gFlashLightPos.x, gFlashLightPos.y, gFlashLightPos.z);

		// Room
		glUniform3f(keyLightColorLoc, gRoomLightColor.r, gRoomLightColor.g, gRoomLightColor.b);
		glUniform3f(keyLightPositionLoc, gRoomLightPos.x, gRoomLightPos.y, gRoomLightPos.z);


		const glm::vec3 cameraPosition = gCamera.Position;
		glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);


		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.textureId);

		// Draws the shape
		glDrawArrays(GL_TRIANGLES, 0, mesh.nIndices);


	}

	// Draw the flash
	glUseProgram(gLightProgramId);
	glBindVertexArray(flashLight.vao);

	glm::mat4 model = glm::translate(gFlashLightPos) * glm::scale(gFlashLightScale);

	GLint modelLoc = glGetUniformLocation(gLightProgramId, "model");
	GLint viewLoc = glGetUniformLocation(gLightProgramId, "view");
	GLint projLoc = glGetUniformLocation(gLightProgramId, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, flashLight.nVertices);

	// Draw the room light
	glUseProgram(gLightProgramId);
	glBindVertexArray(roomLight.vao);

	model = glm::translate(gRoomLightPos) * glm::scale(gRoomLightScale);

	modelLoc = glGetUniformLocation(gLightProgramId, "model");
	viewLoc = glGetUniformLocation(gLightProgramId, "view");
	projLoc = glGetUniformLocation(gLightProgramId, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, roomLight.nVertices);

	// Deactivate vao's
	glBindVertexArray(0);
	glUseProgram(0);

	// Swap buffers
	glfwSwapBuffers(gWindow);
}


void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
}


void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}


bool UCreateTexture(const char* filename, GLuint& textureId)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
	if (image)
	{
		// Loads image
		flipImageVertically(image, width, height, channels);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		else if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			cout << "Not implemented to handle image with " << channels << " channels" << endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	// Error loading the image
	return false;
}
void UDestroyTexture(GLuint textureId)
{
	glGenTextures(1, &textureId);
}


// Creates lights
void UCreateLightMesh(GLightMesh& lightMesh)
{
	
	GLfloat verts[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	lightMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

	glGenVertexArrays(1, &lightMesh.vao);
	glBindVertexArray(lightMesh.vao);

	glGenBuffers(1, &lightMesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightMesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
	glEnableVertexAttribArray(2);
}
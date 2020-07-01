#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader_s.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <vector>
#include <iostream>
#include "doSomePic.h"
using namespace std;


const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 512;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Position mousePos(lastX,lastY);

unsigned char sameVertices[512 * 512 * 3] = { 0 };

int sameRange = 15;

vector<vector<PixelNode*>*>picPixels;
vector<PixelNode*>edgePixels;
vector<PixelNode*>similarPixels;
vector<vector<PixelNode*>*>edgeGroups;
vector<vector<PixelNode*>*>similarGroups;

//vector<vector<PixelNode*>*>goodGroups;

void cursor_Pos_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	checkGLFWwindow(window);

	//// tell GLFW to capture our mouse(true for show the arrow in window)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_TRUE);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_Pos_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);

	// glad: load all OpenGL function pointers
	checkGLADload();

	// build and compile our shader zprogram
	Shader ourShader("texture_vs.glsl", "texture_fs.glsl");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//load and create a texture 
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	const char* path = "./container3.jpg";
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		//(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		// render container
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();

	for (int i = picPixels.size()-1 ; i >-1 ; i--) {
		for (int j = (*picPixels[i]).size()-1; j > -1 ; j--) {
			delete((*picPixels[i])[j]);
		}
		delete(picPixels[i]);
	}
	return 0;
}

void cursor_Pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	//save all picturePixels
	if (picPixels.size() == 0) {
		savePicPix(SCR_WIDTH, SCR_HEIGHT, picPixels);
	}
	//find all pixels' neighbourPix
	if ((*picPixels[0])[0]->ifFound == false) {
		FindAllNeighbor(SCR_WIDTH, SCR_HEIGHT, picPixels);
	}
	similarSituation(xpos, ypos, sameRange,  picPixels, edgePixels, similarPixels);
	//NumSimi(similarPixels);
	//reNumSimi(similarPixels, similarGroups);
	NumEdge(edgePixels);
	reNumEdge(edgePixels,edgeGroups);
	//goodEdge(edgeGroups, goodGroups,10);
	bestEdge(xpos, ypos,edgeGroups, picPixels);

	//color edges
	if (picPixels.size() != 0) {
		//AllEdges show Green
		for (int i = 0; i < picPixels.size(); i++) {
			for (int j = 0; j < (*picPixels[i]).size(); j++) {
				int p = 3 * ((*picPixels[i])[j]->selfPosition->y * 512 + (*picPixels[i])[j]->selfPosition->x);
				sameVertices[p + 0] = (*picPixels[i])[j]->showColour->r;
				sameVertices[p + 1] = (*picPixels[i])[j]->showColour->g;
				sameVertices[p + 2] = (*picPixels[i])[j]->showColour->b;
			}
		}
		unsigned int texture2;
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, sameVertices);//(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
	}

	showMousePn(xpos, ypos, picPixels);
	reSet(picPixels);
   // similarPixels.clear();
	//similarGroups.clear();
	edgePixels.clear();
	edgeGroups.clear();
	//goodGroups.clear();
}
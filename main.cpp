#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#define GLSL(src) #src

#include "src/Application.h"
#include "Logger.h"

static void error_callback(int error, const char *description) {
	fputs(description, stderr);
}


static Core::Application* pKenInputTarget = nullptr;

static void render(GLFWwindow *window) {
}

int main(void) {
	GLFWwindow *window;

	glfwSetErrorCallback(error_callback);



	if (!glfwInit())
		exit(EXIT_FAILURE);



  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1200, 720, "GIRenderer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK){
		Logger::Error((const char*)glewGetErrorString(err));
		return 1;
	}

/*

	try {

*/
		Core::Application app(window);
		app.Initialize();

		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		while (!glfwWindowShouldClose(window)) {
			glViewport(400, 0, w-400, h);
			glClear(GL_COLOR_BUFFER_BIT);
			render(window);
			app.Update();
			app.Render();
			glfwPollEvents();
			//glfwWaitEvents();
		}

/*
	} catch (const std::runtime_error &e) {
		std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
#if defined(_WIN32)
		MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
		std::cerr << error_msg << std::endl;
#endif
	}
	*/
	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

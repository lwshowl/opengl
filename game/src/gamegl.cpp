#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gamegl.h"
#include "shader.h"
#include "viewport.h"
#include "texture.h"
#include "cube.h"

#include <iostream>

int main()
{
	GLFWwindow *window = initWindow(window_width, window_height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	viewport viewport(window, 2000, 1100);
	glEnable(GL_DEPTH_TEST);

	Shader shader("assets/shader/core.vs", "assets/shader/core.fs");
	shader.compile();

	texture texture1("assets/texture/door.png", "texture1");
	texture texture2("assets/texture/img.png", "texture1");

	cube cube0({0, 0, 0}, {1.2f, 1.2f, 1.2f}, texture1);
	cube cube1({0, 2, 0}, {1.2f, 1.2f, 1.2f}, texture2);

	double dt = 0;
	double last_frame = 0;

	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	shader.activate();
	while (!glfwWindowShouldClose(window))
	{
		double current = glfwGetTime();
		dt = current - last_frame;
		last_frame = current;

		processingInput(window, dt);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view = camera.view();
		projection = glm::perspective((float)glm::radians(camera.zoom),
									  (float)viewport.width / (float)viewport.height,
									  0.1f, 100.0f);

		shader.uniformMat4("view", view);
		shader.uniformMat4("projection", projection);

		cube0.render(shader);
		cube1.render(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

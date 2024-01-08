#include <iostream>

#include <glad/glad.h> 
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "YRWindow.h"
#include "YRShader.h"
#include "YRTexture.h"

#include "YRPosData.h"
#include "YRCameraData.h"

float colorAdjust = 0.5;
float leftRightAdjust = 0.0;
float upDownAdjust = 0.0;

glm::vec3 cameraPos = YRCameraData::cameraPos;
glm::vec3 cameraFront = YRCameraData::cameraFront;
glm::vec3 cameraUp = YRCameraData::cameraUp;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	YRWindow myWindow("LearnOpenGL");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::string shaderFilesFolder = "D:\\learningFolder\\code\\shader";
	std::string vertexShaderFilePath = shaderFilesFolder + "\\vshader.txt";
	std::string fragmentShaderFilePath = shaderFilesFolder + "\\fshader.txt";
	YRShader myshader(vertexShaderFilePath, fragmentShaderFilePath);

	std::string textureFilesFolder = "D:\\learningFolder\\code\\texture";
	std::string textureFilePath1 = textureFilesFolder + "\\container.jpg";
	std::string textureFilePath2 = textureFilesFolder + "\\awesomeface.png";
	YRTexture myTexture1(textureFilePath1.c_str());
	YRTexture myTexture2(textureFilePath2.c_str(), true, true);

	//unsigned int VBO1, VAO1, VBO2, VAO2;
	//glGenVertexArrays(1, &VAO1);
	//glGenBuffers(1, &VBO1);
	//glBindVertexArray(VAO1);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glGenVertexArrays(1, &VAO2);
	//glGenBuffers(1, &VBO2);
	//glBindVertexArray(VAO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices36), vertices36, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position vertex attribution
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color vertex attribution
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// texture vertex attribution
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	myshader.use();
	myshader.setInt("texture1", 0);
	myshader.setInt("texture2", 1);

	//glm::mat4 view(1.0f);
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//view = glm::rotate(view, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	/*glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)(800.0 / 600), 0.1f, 100.0f);*/

	glEnable(GL_DEPTH_TEST);

	while (!myWindow.ifCloseWindow())
	{
		myWindow.processInput(myWindow.window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear z-buffer

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture1.texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture2.texture);
		//glUseProgram(shaderProgram1);
		//glBindVertexArray(VAO1);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//float timeValue = glfwGetTime();
		//std::cout << timeValue << "\n";
		//float offsetValue = cos(timeValue);
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//myshader.setFloat("offset", offsetValue);

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		myshader.use();
		glBindVertexArray(VAO);

		for (size_t i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1);
			if ( i % 3 == 0)
			{
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			else
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			myshader.setMat4("model", model);
			//myshader.setMat4("view", view);
			//myshader.setMat4("projection", projection);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		float time = glfwGetTime();
		float offsetValue = sin(time);
		myshader.setFloat("colorOffset", offsetValue);
		myshader.setFloat("colorAdjust", colorAdjust);

		//glm::mat4 model(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		//myshader.setMat4("model", model);
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view(1.0f);
		//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)(800.0 / 600), 0.1f, 100.0f);
		myshader.setMat4("view", view);
		myshader.setMat4("projection", projection);

		//glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		// 
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		//unsigned int transformLoc = glGetUniformLocation(myshader.id, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		//myshader.setFloat("leftRightAdjust", leftRightAdjust);
		//myshader.setFloat("upDownAdjust", upDownAdjust);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//offsetValue = std::fabs(sin(time))+0.1;
		//glm::mat4 transform1 = glm::mat4(1.0f); 
		//transform1 = glm::translate(transform1, glm::vec3(-0.5f, 0.5f, 0.0f));
		//transform1 = glm::scale(transform1, glm::vec3(offsetValue, offsetValue, 0.0));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//transformLoc = glGetUniformLocation(myshader.id, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

		glfwSwapBuffers(myWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
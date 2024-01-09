#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "YRCamera.h"
extern float colorAdjust;

extern float leftRightAdjust;
extern float upDownAdjust;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern float deltaTime;

class YRWindow
{
public:
    GLFWwindow* window;

    YRWindow(const char* windowName, const unsigned int width = 800, const unsigned int hight = 600);

    void processInput(GLFWwindow* window);

    bool ifCloseWindow();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

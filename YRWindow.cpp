#include "YRWindow.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern bool firstMouse;
extern float lastX;
extern float lastY;

extern YRCamera myCamera;

YRWindow::YRWindow(const char* windowName, const unsigned int width, const unsigned int hight)
{
    window = glfwCreateWindow(width, hight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void YRWindow::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // float cameraSpeed = 0.005f; // adjust accordingly
    //float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //cameraPos += cameraSpeed * cameraFront;
        myCamera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        myCamera.ProcessKeyboard(BACKWARD, deltaTime);
        //cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        myCamera.ProcessKeyboard(LEFT, deltaTime);
        //cameraPos -= glm::normalize(
        //    glm::cross(static_cast<glm::vec3>(cameraFront), static_cast<glm::vec3>(cameraUp))) *
        //    cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        myCamera.ProcessKeyboard(RIGHT, deltaTime);
        //cameraPos += glm::normalize(
        //    glm::cross(static_cast<glm::vec3>(cameraFront), static_cast<glm::vec3>(cameraUp))) *
        //    cameraSpeed;
}

bool YRWindow::ifCloseWindow()
{
    return glfwWindowShouldClose(this->window);
}

void YRWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void YRWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    myCamera.ProcessMouseMovement(xoffset, yoffset);
    //float sensitivity = 0.05;
    //xoffset *= sensitivity;
    //yoffset *= sensitivity;

    //yaw += xoffset;
    //pitch += yoffset;

    //if (pitch > 89.0f)
    //    pitch = 89.0f;
    //if (pitch < -89.0f)
    //    pitch = -89.0f;

    //glm::vec3 front;
    //front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //front.y = sin(glm::radians(pitch));
    //front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //cameraFront = glm::normalize(front);
}

void YRWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    myCamera.ProcessMouseScroll(static_cast<float>(yoffset));
    //if (fov >= 1.0f && fov <= 45.0f)
    //    fov -= yoffset;
    //if (fov <= 1.0f)
    //    fov = 1.0f;
    //if (fov >= 45.0f)
    //    fov = 45.0f;
}
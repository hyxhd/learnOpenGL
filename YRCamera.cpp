#include "YRCamera.h"

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 YRCamera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	//不是m_up，应该是worldup，
	//worldup是用来计算右向量时用到的那个世界上向量，up是相机的上向量，如果用up，当视角对准天空之后
	//相机的方位感就失效了。.
	//return glm::lookAt(m_Position, m_Position + m_Front, m_WorldUp);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera
// defined ENUM (to abstract it from windowing systems)
void YRCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	if (direction == FORWARD)
		m_Position += m_Front * velocity;
	if (direction == BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == LEFT)
		m_Position -= m_Right * velocity;
	if (direction == RIGHT)
		m_Position += m_Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void YRCamera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (constrainPitch)
	//{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	//}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void YRCamera::ProcessMouseScroll(float yoffset)
{
	m_Fov -= (float)yoffset;
	if (m_Fov < 1.0f)
		m_Fov = 1.0f;
	if (m_Fov > 45.0f)
		m_Fov = 45.0f;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void YRCamera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_Right = glm::normalize(
		glm::cross(m_Front, m_WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you
										// look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
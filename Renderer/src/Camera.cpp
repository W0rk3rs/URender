#include "Camera.h"


GLFWwindow* Camera::m_Window;

glm::vec3 Camera::Position;
glm::vec3 Camera::Front;
glm::vec3 Camera::Up;
glm::vec3 Camera::Right;
glm::vec3 Camera::WorldUp;

float Camera::Yaw;
float Camera::Pitch;

float Camera::MovementSpeed;
float Camera::MouseSensitivity;
float Camera::Zoom;

float Camera::lastTime;
float Camera::deltaTime;

bool Camera::firstMouse;

float Camera::lastX;
float Camera::lastY;

bool Camera::InputMode;

float YAW = -90.0f;
float PITCH = 0.0f;
float SPEED = 2.5f;
float SENSITIVITY = 0.1f;
float ZOOM = 45.0F;


Camera& Camera::InitCamera(GLFWwindow* window, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	float yaw = YAW, float pitch = PITCH)
{
	Camera camera;
	m_Window = window;
	Front =glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = SPEED;
	MouseSensitivity =SENSITIVITY;
	Zoom =ZOOM;
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	lastTime = 0.0f;
	firstMouse = true;
	InputMode = false;
	updateCameraVectors();

	return camera;
}

Camera& Camera::InitCamera(GLFWwindow* window, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	Camera camera;
	m_Window = window;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;
	Yaw = yaw;
	Pitch = pitch;
	lastTime = 0.0f;
	firstMouse = true;
	InputMode = false;
	updateCameraVectors();

	return camera;
}

/*Camera Camera::GetCamera()
{
	return camera;
}*/


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Mouvement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

float Camera::GetZoom() { return Zoom; }

glm::vec3 Camera::GetPos()
{
	return Position;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	
	Right = glm::normalize(glm::cross(Front, WorldUp)); 
	Up = glm::normalize(glm::cross(Right, Front));
}

float Camera::GetDeltaTime()
{
	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	return deltaTime;
}

void Camera::PollKeys()
{
	float time = GetDeltaTime();
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		ProcessKeyboard(FORWARD, time);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		ProcessKeyboard(BACKWARD, time);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		ProcessKeyboard(RIGHT, time);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		ProcessKeyboard(LEFT, time);
	if (glfwGetKey(m_Window, GLFW_KEY_C) == GLFW_PRESS)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		InputMode = true;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_N) == GLFW_PRESS)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		InputMode = false;
		firstMouse = true;
	}
}

void Camera::mouseEvent(double xpos, double ypos)
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

	ProcessMouseMovement(xoffset, yoffset);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseEvent(xpos, ypos);

}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ProcessMouseScroll(yoffset);
}

void Camera::PollInput()
{
	if (InputMode)
	{
		glfwSetCursorPosCallback(m_Window, Camera::mouse_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
	}
	else
	{
		glfwSetCursorPosCallback(m_Window, 0);
		glfwSetScrollCallback(m_Window, 0);
	}
	PollKeys();

	
}
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "GLFW/glfw3.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Mouvement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:

	static GLFWwindow* m_Window;

	static glm::vec3 Position;
	static glm::vec3 Front;
	static glm::vec3 Up;
	static glm::vec3 Right;
	static glm::vec3 WorldUp;

	static float Yaw;
	static float Pitch;

	static float MovementSpeed;
	static float MouseSensitivity;
	static float Zoom;

	static float lastTime;
	static float deltaTime;

	static bool firstMouse;

	static float lastX;
	static float lastY;

	static bool InputMode;

public:
	static Camera& InitCamera(GLFWwindow* window, glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	static Camera& InitCamera(GLFWwindow* window, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	static glm::mat4 GetViewMatrix();
	static void ProcessKeyboard(Camera_Mouvement direction, float deltaTime);
	static void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constraintPitch);
	static void ProcessMouseScroll(float yoffset);

	static float GetZoom();
	static glm::vec3 GetPos();

	static float GetDeltaTime();

	static void PollKeys();

	static void mouseEvent(double xpos, double ypos);

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static void PollInput();


private:
	Camera() {}

	static Camera camera;
	static void updateCameraVectors();

public:
	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;
};

#endif
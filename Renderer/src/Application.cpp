#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/Test3D.h"
#include "tests/TestLighting.h"
#include "tests/TestSphere.h"


void ErrorCallback(int id, const char* err_str)
{
	std::cout << "GLFW Error "<< id << ": " << err_str << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	else if ((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}


int main()
{
	float windowWidth = 800.0f;
	float windowHeight = 600.0f;

	glfwSetErrorCallback(ErrorCallback);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//Make OPEN_GL CORE and hints, however need opengl 3.3 and higher
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);*/
	
	GLFWwindow* window;
	
	/* Create a windowed mode window and its OpenGL context */ 
	window = glfwCreateWindow((int)windowWidth, (int)windowHeight, "OPENGL testing", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glfwSwapInterval(1);

	/* Initialize glew after currenting window's context*/
	if (glewInit() != GLEW_OK) 
		return -1;

	GLCall(glViewport(0, 0, (int)windowWidth, (int)windowHeight));


	{

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		const char* glsl_version = "#version 130";
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);


		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = new test::TestSphere(window);

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
		testMenu->RegisterTest3D<test::Test3D>("3D Test", window);
		testMenu->RegisterTest3D<test::TestLighting>("Lighting Test", window);
		testMenu->RegisterTest3D<test::TestSphere>("Circle Test", window);



		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if ((currentTest != testMenu && ImGui::Button("<-")) ||
					(currentTest != testMenu &&(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Poll for and process events */
			glfwPollEvents();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
		}
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
#include "Test.h"
#include "imgui\imgui.h"

namespace test {
	TestMenu::TestMenu(Test *& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if(ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Press C to control direction with mouse"
					"\nPress N to realease directional control"
					"\nPress M to access menu"
					"\nPress 2 to enter polygon mode"
					"\nPress 1 to return to normal mode"
					"\nPress esc to leave"
					"\nPress W,A,S,D to move the camera"
					"\nScroll up and down to zoom in and out");
	}
}
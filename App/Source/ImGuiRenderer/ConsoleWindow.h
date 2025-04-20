#pragma once
#include "UIElement.h"
#include <imgui.h>

class ConsoleWindow : public UIElement
{
public:
	void OnImGuiRender() override
	{
		ImGui::Begin("Console");
		ImGui::Text("Log output goes here.");
		ImGui::End();
	}
};

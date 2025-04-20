#pragma once
#include "UIElement.h"
#include <imgui.h>

class SettingsPanel : public UIElement
{
public:
	bool m_Open = false;

	void OnImGuiRender() override
	{
		if (!m_Open) return;

		ImGui::Begin("Settings", &m_Open, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Settings here");
		static char search[64] = "";
		ImGui::InputText("Search", search, sizeof(search));
		ImGui::End();
	}
};

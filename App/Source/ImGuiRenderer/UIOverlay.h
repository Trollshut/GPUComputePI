#pragma once
#include "UIElement.h"
#include <imgui.h>
#include <imgui_internal.h>

class UIOverlay : public UIElement
{
public:
	bool* pSettingsOpen = nullptr;

	void OnImGuiRender() override
	{
		ImGuiViewport* vp = ImGui::GetMainViewport();
		ImVec2 pos = ImVec2(vp->WorkPos.x + vp->WorkSize.x - 40, vp->WorkPos.y + 10);

		ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(30, 30));
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::Begin("Cog", nullptr,
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

		if (ImGui::Button("⚙")) // You can replace with icon font or custom texture
		{
			if (pSettingsOpen)
				*pSettingsOpen = !(*pSettingsOpen);
		}

		ImGui::End();
	}
};

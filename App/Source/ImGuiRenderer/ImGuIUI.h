#pragma once

#include "UIElement.h"
#include "ConsoleWindow.h"
#include "SettingsPanel.h"
#include "UIOverlay.h"

class ImGuiUI
{
public:
	ImGuiUI()
	{
		m_Overlay.pSettingsOpen = &m_SettingsPanel.m_Open;
	}

	void Render()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		m_ConsoleWindow.OnImGuiRender();
		m_SettingsPanel.OnImGuiRender();
		m_Overlay.OnImGuiRender();
	}

private:
	ConsoleWindow m_ConsoleWindow;
	SettingsPanel m_SettingsPanel;
	UIOverlay m_Overlay;
};

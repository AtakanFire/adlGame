#include "GameFunctions.h"


void GameFunctions::ImGuiStyler()
{
	ImGuiStyle& style = ImGui::GetStyle();

	// Settings
	style.WindowBorderSize = style.ChildBorderSize = style.FrameBorderSize = style.PopupBorderSize = 0.0f;
	style.GrabRounding = style.FrameRounding = style.PopupRounding = 10;
	style.GrabMinSize = 15;
	style.WindowTitleAlign = ImVec2(0.5f, 1.0f);
	style.ItemInnerSpacing = ImVec2(10, 4);

	// Color
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.16f, 0.16f, 0.50f);

	colors[ImGuiCol_Header] = ImVec4(0.12f, 0.51f, 0.69f, 0.67f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.35f, 0.74f, 0.59f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.11f, 0.69f, 0.54f, 0.75f);

	colors[ImGuiCol_PlotHistogram] = ImVec4(0.16f, 0.18f, 0.04f, 0.89f);

	
	colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.40f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 0.40f);






	/*colors[ImGuiCol_HeaderHovered] = ImVec4(0.29f, 0.25f, 0.09f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.65f, 0.48f, 0.18f, 0.80f);*/






}

bool GameFunctions::CheckImGuiClicked()
{
	return ImGui::IsAnyWindowHovered() || ImGui::IsAnyItemHovered() || ImGui::IsMouseHoveringAnyWindow();
}

std::vector<std::string> GameFunctions::SplitString(std::string mainString, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> newString;
	while ((pos = mainString.find(delimiter)) != std::string::npos) {
		token = mainString.substr(0, pos);
		std::cout << token << std::endl;
		newString.push_back(token);
		mainString.erase(0, pos + delimiter.length());
	}
	if (mainString != "")
		newString.push_back(mainString);
	return newString;
}


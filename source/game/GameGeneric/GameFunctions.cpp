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
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.10f, 0.08f, 0.16f);

	colors[ImGuiCol_Header] = ImVec4(0.66f, 0.36f, 0.01f, 0.16f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.43f, 0.26f, 0.16f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.79f, 0.65f, 0.22f, 1.00f);

	colors[ImGuiCol_FrameBg] = ImVec4(0.96f, 1.00f, 0.31f, 0.1f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.75f, 0.56f, 0.04f, 0.16f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.65f, 0.32f, 0.00f, 0.21f);


	colors[ImGuiCol_Button] = ImVec4(0.85f, 0.36f, 0.00f, 0.28f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.66f, 0.26f, 0.01f, 0.64f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.96f, 0.83f, 0.25f, 0.72f);

	colors[ImGuiCol_PlotHistogram] = ImVec4(0.95f, 0.57f, 0.06f, 0.6f);

	colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.40f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 0.40f);

	// Font
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/fonts/arial.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesDefault());
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
		//std::cout << token << std::endl;
		newString.push_back(token);
		mainString.erase(0, pos + delimiter.length());
	}
	if (mainString != "")
		newString.push_back(mainString);
	return newString;
}


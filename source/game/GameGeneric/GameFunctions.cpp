#include "GameFunctions.h"

void GameFunctions::ImGuiStyler()
{
	ImGuiStyle& style = ImGui::GetStyle();

	// Settings
	style.WindowBorderSize = style.ChildBorderSize = style.FrameBorderSize = style.PopupBorderSize = 0.0f;
	style.GrabRounding = style.FrameRounding = style.PopupRounding = 10;
	style.GrabMinSize = 15;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ItemInnerSpacing = ImVec2(10, 4);

	// Color


}

bool GameFunctions::CheckImGuiClicked()
{
	return ImGui::IsAnyWindowHovered() || ImGui::IsAnyItemHovered() || ImGui::IsMouseHoveringAnyWindow();
}



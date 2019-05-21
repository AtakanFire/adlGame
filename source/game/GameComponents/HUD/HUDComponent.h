#ifndef HUDComponent_h__
#define HUDComponent_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "engine/adl_editor/adlEditor_manager.h"
#include "engine/adlWindow.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameComponents/Player/PlayerAttributes.h"

class HUDComponent : public adlEntity_component { 

public:

	HUDComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	struct GameLog
	{
		ImGuiTextBuffer     Buf;
		ImVector<int>       LineOffsets;        // Index to lines offset
		bool                ScrollToBottom;
		bool                opened = false;
		ImGuiTextBuffer     last;

		void    Toggle() { opened != opened; }

		void    Clear() { Buf.clear(); LineOffsets.clear(); }

		void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
		{
			last.clear();
			last.appendf("");

			int old_size = Buf.size();
			va_list args;
			va_start(args, fmt);
			Buf.appendfv(fmt, args);
			last.appendfv(fmt,args);
			va_end(args);

			Buf.appendf("\n");
			for (int new_size = Buf.size(); old_size < new_size; old_size++)
				if (Buf[old_size] == '\n')
					LineOffsets.push_back(old_size);
			ScrollToBottom = true;
		}

		void    Draw()
		{
			if (!opened) return;
				
			const char* title = "Game Actions";
			ImGuiIO& io = ImGui::GetIO();
			ImGui::SetNextWindowSize(ImVec2(250, 200));
			ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 260, (io.DisplaySize.y - 200)/2));
			ImGui::SetNextWindowBgAlpha(0.1f);

			if (ImGui::Begin(title, &opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | 
				ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar))
			{
				ImGui::BeginChild("Scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
				ImGui::TextUnformatted(Buf.begin());
				if (ScrollToBottom)
					ImGui::SetScrollHere(1.0f);
				ScrollToBottom = false;
				ImGui::EndChild();
				if (ImGui::IsItemHovered()) {
					if (ImGui::GetIO().MouseClicked[1])
					{
						Clear();
					}
					else if (ImGui::GetIO().MouseClicked[2])
					{
						opened = false;
					}
				}
				ImGui::End();
			}

		}

		void    MainMenu()
		{
			//ImGui::Text("|");
			ImGui::Text("%s", last.begin());
			if (ImGui::IsItemHovered()) {
				if (ImGui::GetIO().MouseClicked[1])
				{
					opened = true;
				}
			}
		}
	};

	GameLog gameLog;

private:

	ImGuiStyle defaultStyle;	
	adlEditor_manager* editorMan;
	SharedPointer<PlayerAttributes> player;

	void mainMenu();
	void mainLayout();

	void humanAttributes();
	void resourceAttributes();
	void constructionAttributes();

	void progressBarGenerator(std::vector<std::string> text, float value[], float limit = 100.0f, bool indent = true, bool showAll = true, bool valueColor = false);

	void buildConstructionTool(std::string name);

	void modal();

};

#endif //HUDComponent_h__

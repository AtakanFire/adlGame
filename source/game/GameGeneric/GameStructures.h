#ifndef GameStructures_h__
#define GameStructures_h__

#include "game/GameGeneric/GameGenericTypedef.h"

struct ConsumableResources { // Food, Wood, Stone, Metal, Cotton
	float food = 0;
	float wood = 0;
	float stone = 0;
	float metal = 0;
	float cotton = 0;
	float gold = 0;
	float knowledge = 0;
	float happy = 0;

	void load(const rapidjson::Value& jsonObject) {
		food = jsonObject["food"].GetFloat();
		wood = jsonObject["wood"].GetFloat();
		stone = jsonObject["stone"].GetFloat();
		metal = jsonObject["metal"].GetFloat();
		cotton = jsonObject["cotton"].GetFloat();
		gold = jsonObject["gold"].GetFloat();
		knowledge = jsonObject["knowledge"].GetFloat();
		happy = jsonObject["happy"].GetFloat();
	}

	void editor() {

		ImGui::Indent();
		ImGui::Text("Food(0f, 100f)");
		ImGui::SliderFloat("##food", &food, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Wood(0f, 100f)");
		ImGui::SliderFloat("##wood", &wood, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Stone(0f, 100f)");
		ImGui::SliderFloat("##stone", &stone, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Metal(0f, 100f)");
		ImGui::SliderFloat("##metal", &metal, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Cotton(0f, 100f)");
		ImGui::SliderFloat("##cotton", &cotton, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Gold(0f, 100f)");
		ImGui::SliderFloat("##gold", &gold, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Knowledge(0f, 100f)");
		ImGui::SliderFloat("##knowledge", &knowledge, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Indent();
		ImGui::Text("Happy(0f, 100f)");
		ImGui::SliderFloat("##happy", &happy, 0.0f, 100.0f);
		ImGui::Unindent();
	}
};


struct DerivedResources { // Cloth, Lumber, Gold
	float cloth = 0;
	float lumber = 0;
	float gold = 0;
};


struct HumanlyResources { // Happy, Knowledge
	float Happy = 0;
	float Knowledge = 0;
};


#endif //GameStructures_h__

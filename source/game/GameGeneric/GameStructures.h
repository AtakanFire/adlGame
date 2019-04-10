#ifndef GameStructures_h__
#define GameStructures_h__

#include "game/GameGeneric/GameGenericTypedef.h"


enum ConsumableResources { // Food, Wood, Stone, Metal, Cotton
	ConsumableResourcesFood, 
	ConsumableResourcesWood, 
	ConsumableResourcesStone, 
	ConsumableResourcesMetal, 
	ConsumableResourcesCotton,
	ConsumableResourcesCOUNT
};

enum DerivedResources { // Cloth, Lumber, Gold
	DerivedResourcesCloth,
	DerivedResourcesLumber,
	DerivedResourcesGold,
	DerivedResourcesCOUNT
};

enum HumanlyResources { // Happy, Knowledge
	HumanlyResourcesHappy,
	HumanlyResourcesKnowledge,
	HumanlyResourcesCOUNT
};

struct AllResources {
	std::vector<std::string> consumableTypes = { "Food", "Wood", "Stone", "Metal", "Cotton" };
	std::vector<std::string> derivedTypes = { "Cloth", "Lumber", "Gold" };
	std::vector<std::string> humanlyTypes = { "Happy", "Knowledge" };

	float consumable[ConsumableResources::ConsumableResourcesCOUNT] = { 0 }; // Food, Wood, Stone, Metal, Cotton
	float derived[DerivedResources::DerivedResourcesCOUNT] = { 0 }; // Cloth, Lumber, Gold
	float humanly[HumanlyResources::HumanlyResourcesCOUNT] = { 0 }; // Happy, Knowledge

	void editor() {
		ImGui::Text("Consumable Resources");
		ImGui::Indent();

		for (int i = 0; i < consumableTypes.capacity(); i++)
		{
			ImGui::Indent();

			ImGui::Text("%s(0f, 100f)", consumableTypes[i].c_str());
			ImGui::SliderFloat(std::string("##" + consumableTypes[i]).c_str(), &consumable[i], 0.0f, 100.0f);

			ImGui::Unindent();
		}
		ImGui::Unindent();

		ImGui::Text("Derived Resources");
		ImGui::Indent();

		for (int i = 0; i < derivedTypes.capacity(); i++)
		{
			ImGui::Indent();

			ImGui::Text("%s(0f, 100f)", derivedTypes[i].c_str());
			ImGui::SliderFloat(std::string("##" + derivedTypes[i]).c_str(), &derived[i], 0.0f, 100.0f);

			ImGui::Unindent();
		}
		ImGui::Unindent();

		ImGui::Text("Humanly Resources");
		ImGui::Indent();

		for (int i = 0; i < humanlyTypes.capacity(); i++)
		{
			ImGui::Indent();

			ImGui::Text("%s(0f, 100f)", humanlyTypes[i].c_str());
			ImGui::SliderFloat(std::string("##" + humanlyTypes[i]).c_str(), &humanly[i], 0.0f, 100.0f);

			ImGui::Unindent();
		}
		ImGui::Unindent();
	}
};

#endif //GameStructures_h__

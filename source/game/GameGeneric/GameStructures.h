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

	std::vector<std::string> allTypes() {
		std::vector<std::string> all = { };
		all.insert(std::end(all), std::begin(consumableTypes), std::end(consumableTypes));
		all.insert(std::end(all), std::begin(derivedTypes), std::end(derivedTypes));
		all.insert(std::end(all), std::begin(humanlyTypes), std::end(humanlyTypes));
		return all;
	}

	std::vector<float> allValues() {
		std::vector<float> all = { };
		all.insert(std::end(all), std::begin(consumable), std::end(consumable));
		all.insert(std::end(all), std::begin(derived), std::end(derived));
		all.insert(std::end(all), std::begin(humanly), std::end(humanly));
		return all;
	}

	float &find(std::string type) {

		std::vector<std::string>::iterator c = std::find(consumableTypes.begin(), consumableTypes.end(), type);
		std::vector<std::string>::iterator d = std::find(derivedTypes.begin(), derivedTypes.end(), type);
		std::vector<std::string>::iterator h = std::find(humanlyTypes.begin(), humanlyTypes.end(), type);

		if (c != consumableTypes.cend()) {
			return consumable[std::distance(consumableTypes.begin(), c)];
		} else if (d != derivedTypes.cend()) {
			return derived[std::distance(derivedTypes.begin(), d)];
		} else if (h != humanlyTypes.cend()) {
			return humanly[std::distance(humanlyTypes.begin(), h)];
		} else {
			std::cout << "Undefined Type" << std::endl;
		}			
	}

	void editor() {
		ImGui::Text("Consumable Resources");
		ImGui::Indent();

		for (size_t i = 0; i < consumableTypes.size(); i++)
		{
			ImGui::Indent();

			ImGui::Text("%s(0f, 100f)", consumableTypes[i].c_str());
			ImGui::SliderFloat(std::string("##" + consumableTypes[i]).c_str(), &consumable[i], 0.0f, 100.0f);

			ImGui::Unindent();
		}
		ImGui::Unindent();

		ImGui::Text("Derived Resources");
		ImGui::Indent();

		for (size_t i = 0; i < derivedTypes.size(); i++)
		{
			ImGui::Indent();

			ImGui::Text("%s(0f, 100f)", derivedTypes[i].c_str());
			ImGui::SliderFloat(std::string("##" + derivedTypes[i]).c_str(), &derived[i], 0.0f, 100.0f);

			ImGui::Unindent();
		}
		ImGui::Unindent();

		ImGui::Text("Humanly Resources");
		ImGui::Indent();

		for (size_t i = 0; i < humanlyTypes.size(); i++)
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

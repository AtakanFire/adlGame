#ifndef GameFunctions_h__
#define GameFunctions_h__

#include "game/GameGeneric/GameGenericTypedef.h"

class GameFunctions { 

public:

	static void ImGuiStyler();

	static bool CheckImGuiClicked();

	static std::vector<std::string> SplitString(std::string mainString, std::string delimiter);

private:

};

#endif //GameFunctions_h__

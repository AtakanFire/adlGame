#ifndef adl_input_h__
#define adl_input_h__

#include <string.h>
#include <stdio.h>
#include "adl_math/adlMath.h"
#include "sdl_definitions.h"

class adlInput
{
public:

	static adlInput& get()
	{
		static adlInput instance;
		return instance;
	}

	void update();
	bool get_key(adl_keys key);
	bool get_key_down(adl_keys key);
	bool get_key_up(adl_keys key);

	bool get_mouse_down(uint32 button);
	bool get_mouse_up(uint32 button);

	adlVec2_i32 get_mouse_pos();

	int get_mouse_x_rel();
	int get_mouse_y_rel();

	struct Mouse_state
	{
		int x;
		int y;
		int xDif;
		int yDif;
		int lmb;
		int rmb;
		int lmbr;
		int rmbr;
	};

private:
	unsigned char keyboard_[323] = { 0 };
	unsigned char prev_keyboard_[323] = { 0 };

	Mouse_state mouse_state_ = {};
	Mouse_state prev_mouse_state_ = {};

	adlInput();
};

#endif // adl_input_h__

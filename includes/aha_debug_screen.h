#ifndef AHA_DEBUG_SCREEN_H
#define AHA_DEBUG_SCREEN_H

#include "jgl.h"

#include "aha_editor_mode.h"

class c_debug_screen : public c_widget
{
private:
	c_board* board;
	c_editor_mode* board_widget;
public:
	c_debug_screen(c_editor_mode* p_board_widget, c_widget* p_parent);
	void render();
	void set_geometry_imp(Vector3 p_anchor, Vector3 p_area);
};

#endif
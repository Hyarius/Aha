#ifndef AHA_QUIT_MENU_H
#define AHA_QUIT_MENU_H

#include "jgl.h"

class c_quit_menu : public c_widget
{
protected:
	class c_game_engine* _engine;

	c_frame* _back_frame;
	c_button* _save_button;
	c_button* _save_quit_button;
	c_button* _quit_button;

public:
	c_quit_menu(c_game_engine* p_engine, c_widget* p_parent);
	void render();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
};

#endif
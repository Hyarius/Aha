#ifndef AHA_DEBUG_SCREEN_H
#define AHA_DEBUG_SCREEN_H

#include "jgl.h"

#include "aha_editor_mode.h"

class c_debug_screen : public c_widget
{
private:
	class c_game_engine* _engine;

public:
	c_debug_screen(c_game_engine *p_engine, c_widget* p_parent = nullptr);
	void draw_line(int& nb_line, string text);
	void render();
	string parse_direction(Vector3 direction);
	void set_geometry_imp(Vector2 p_achor, Vector2 p_area) {}
};

#endif
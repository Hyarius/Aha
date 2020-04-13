#ifndef AHA_GAME_ENGINE_H
#define AHA_GAME_ENGINE_H

#include "jgl.h"
#include "aha_board.h"
#include "aha_player.h"
#include "aha_debug_screen.h"

class c_game_engine : public c_widget
{
protected:
	c_camera* _camera;
	c_board* _board;
	c_player* _player;

	size_t _active_mode;
	c_game_mode *_modes[1];

	c_debug_screen* _debug_screen;

	int _player_vision;
	Vector2 _player_pos;

public:
	c_game_engine(string path, c_widget *p_parent = nullptr);
	c_game_mode* modes(size_t index) { return (_modes[index]); }
	c_camera* camera() { return (_camera); }
	c_board* board() { return (_board); }
	c_player* player() { return (_player); }
	Vector2 player_pos() { return (_player_pos); }
	void actualize_player_pos();

	bool handle_keyboard();
	bool handle_mouse();
	void update();
	void render();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
};

void save_map(c_game_engine* render);

#endif
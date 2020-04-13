#ifndef AHA_EDITOR_MODE_H
#define AHA_EDITOR_MODE_H

#include "jgl.h"
#include "aha_game_mode.h"
#include "aha_player_info_widget.h"
#include "aha_short_cut_bar.h"

class c_editor_mode : public c_game_mode
{
protected:
	Vector3 _source;
	Vector3 _target;

	c_mesh* _pointeur;
	c_player_info* _player_info;

	c_shortcut_bar* _shortcut_bar;

public:
	c_editor_mode(c_game_engine* p_engine, c_camera* camera, c_board* board, c_player* player);

	void render();
	void update();
	bool handle_mouse();
	bool handle_keyboard();

	c_player_info* player_info() { return (_player_info); }

	c_shortcut_bar* shortcut_bar() { return (_shortcut_bar); }

	void activate() { _active = true; _player_info->activate(); _shortcut_bar->activate(); }
	void desactivate() { _active = false; _player_info->desactivate(); _shortcut_bar->desactivate(); }

	void set_voxel(Vector3 pos, int type);
	void add_voxel(Vector3 pos, int type);
	void change_voxel(Vector3 pos, int type);
};

#endif
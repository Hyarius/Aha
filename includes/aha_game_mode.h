#ifndef AHA_GAME_MODE_H
#define AHA_GAME_MODE_H

#include "jgl.h"
#include "aha_board.h"
#include "aha_player.h"

class c_game_mode
{
protected:
	c_camera* _camera;
	c_board* _board;
	c_player* _player;

public:
	c_game_mode(c_camera* p_camera, c_board* p_board, c_player* p_player)
	{
		_camera = p_camera;
		_board = p_board;
		_player = p_player;
	}
	c_camera* camera() { return (_camera); }
	c_board* board() { return (_board); }
	c_player* player() { return (_player); }
	bool voxel_raycast(Vector3 pos, Vector3 direction, Vector3* voxel_source, Vector3* voxel_target)
	{
		Vector3 actual = pos;
		Vector3 delta = direction / -100.0f;

		int i = 0;
		while (_board->voxels(actual + delta * i) < 0 && i < 1000)
			i++;

		if (i != 1000)
		{
			*voxel_source = actual + delta * i;
			*voxel_target = actual + delta * (i - 1);
			return (true);
		}
		else
		{
			*voxel_source = -1;
			*voxel_target = -1;
			return (false);
		}
	}


	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handle_mouse() = 0;
	virtual bool handle_keyboard() = 0;
	virtual void set_voxel(Vector3 pos, int type) = 0;
	virtual void add_voxel(Vector3 pos, int type) = 0;
	virtual void change_voxel(Vector3 pos, int type) = 0;
};

#endif
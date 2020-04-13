#ifndef AHA_BOARD_H
#define AHA_BOARD_H

extern Vector3 chunk_size;
extern c_tileset* block_tile;
extern float block_alphas[];
extern size_t block_sprite_face[][3];

#include "aha_chunk.h"

class c_board
{
protected:
	Vector3 _spawn;
	map<Vector2, c_chunk*> _chunks;
	vector<Voxel_data> _edited_voxel;
public:
	c_board(fstream &file);
	Vector3 spawn() { return(_spawn); }
	map<Vector2, c_chunk*>& chunks() { return _chunks; }
	vector<Voxel_data>& edited_voxel() { return _edited_voxel; }
	Voxel_data edited_voxel(size_t index) { return (_edited_voxel[index]); }
	c_chunk* chunk(Vector2 chunk_pos);
	c_chunk* chunks(Vector2 chunk_pos);
	Vector2 get_chunk_pos(Vector3 abs_pos);
	Vector3 get_rel_pos(Vector3 abs_pos);
	int voxels(Vector3 pos);
	void set_voxel(Vector3 pos, int type);
	void change_voxel(Vector3 pos, int type);
	void add_voxel(Vector3 pos, int type);
	void render(c_camera* camera, Vector2 player_pos, int player_vision);
};

#endif
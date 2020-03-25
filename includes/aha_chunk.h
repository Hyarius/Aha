#ifndef AHA_CHUNK_H
#define AHA_CHUNK_H

#include "jgl.h"

extern Vector3 chunk_size;
extern Vector3 voxel_neighbour[6];
extern Vector3 voxel_vertices[8];
extern Vector2 voxel_uvs[4];
extern Vector3 voxel_normales[6];
extern int  voxel_face_vertices_index[6][2][3];
extern int  voxel_face_uvs_index[6][2][3];
extern int  voxel_face_normales_index[6][3];

struct Voxel_data
{
	Vector3 pos;
	int type;
	Voxel_data(Vector3 p_pos, int p_type)
	{
		pos = p_pos;
		type = p_type;
	}
};

class c_chunk
{
protected:
	bool _baked;
	Vector2 _pos;
	int*** _voxels;
	vector<Voxel_data> _edited;

	c_mesh* _mesh;
	c_mesh* _transparent_mesh;

public:
	c_chunk(Vector2 p_pos);
	void actualize();
	void load();
	void release();
	Vector3 absolute_pos(Vector3 rel_pos);
	vector<Voxel_data>& edited() { return (_edited); }
	int*** voxels() { return _voxels; }
	int voxels(Vector3 rel_pos);
	void add_voxel_comp(c_mesh* target, int type, Vector3 abs_pos);
	void compose_voxel(Vector3 abs_pos, int type);
	void set_voxel(Vector3 rel_pos, int type);
	void change_voxel(Vector3 rel_pos, int type);
	void add_voxel(Vector3 rel_pos, int type);
	void render(c_camera* camera);
	void render_alpha(c_camera* camera);
};

#endif
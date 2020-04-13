#include "aha.h"

extern c_board* g_board;

c_chunk::c_chunk(Vector2 p_pos)
{
	_baked = false;
	_pos = p_pos;
	_edited.clear();
	_mesh = new c_mesh(0, 0, 1);
	_mesh->set_texture(block_tile);
	_transparent_mesh = new c_mesh(0, 0, 1);
	_transparent_mesh->set_texture(block_tile);
	_transparent_mesh->set_transparency(0.5f);
	load();
}

void c_chunk::load()
{
	_voxels = new int** [static_cast<size_t>(chunk_size.x)];
	for (size_t i = 0; i < static_cast<size_t>(chunk_size.x); ++i)
	{
		_voxels[i] = new int* [static_cast<size_t>(chunk_size.y)];
		for (size_t j = 0; j < static_cast<size_t>(chunk_size.y); ++j)
		{
			_voxels[i][j] = new int[static_cast<size_t>(chunk_size.z)];
			for (size_t h = 0; h < static_cast<size_t>(chunk_size.z); ++h)
				_voxels[i][j][h] = (j == 0 ? 0 : -1);
		}
	}
	for (size_t i = 0; i < _edited.size(); i++)
	{
		Vector3 pos = _edited[i].pos;
		int type = _edited[i].type;
		set_voxel(pos, type);
	}
}

void c_chunk::release()
{
	_mesh->clear();
	_transparent_mesh->clear();
	_baked = false;
	if (_voxels == nullptr)
		return;
	for (size_t i = 0; i < static_cast<size_t>(chunk_size.x); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(chunk_size.y); ++j)
		{
			delete _voxels[i][j];
		}
		delete _voxels[i];
	}
	delete _voxels;
	_voxels = nullptr;
}

void c_chunk::actualize()
{
	_mesh->clear();
	_transparent_mesh->clear();
	if (_voxels == nullptr)
		load();
	for (size_t i = 0; i < static_cast<size_t>(chunk_size.x); ++i)
		for (size_t j = 0; j < static_cast<size_t>(chunk_size.y); ++j)
			for (size_t h = 0; h < static_cast<size_t>(chunk_size.z); ++h)
			{
				if (_voxels[i][j][h] != -1)
					compose_voxel(Vector3(static_cast<int>(i), static_cast<int>(j), static_cast<int>(h)), _voxels[i][j][h]);
			}
	_mesh->bake();
	_transparent_mesh->bake();
	_baked = true;
}

Vector3 c_chunk::absolute_pos(Vector3 rel_pos)
{
	return (rel_pos + Vector3(_pos.x * chunk_size.x, 0.0f, _pos.y * chunk_size.z));
}

int c_chunk::voxels(Vector3 rel_pos)
{
	if (rel_pos.x < 0 || rel_pos.y < 0 || rel_pos.z < 0 ||
		rel_pos.x >= chunk_size.x || rel_pos.y >= chunk_size.y || rel_pos.z >= chunk_size.z)
	{
		if (g_board != nullptr)
			return g_board->voxels(absolute_pos(rel_pos));
		return (-2);
	}
	if (_voxels == nullptr)
		load();
	int x = static_cast<int>(rel_pos.x);
	int y = static_cast<int>(rel_pos.y);
	int z = static_cast<int>(rel_pos.z);
	return (_voxels[x][y][z]);
}

void c_chunk::add_voxel_comp(c_mesh* target, int type, Vector3 abs_pos)
{
	Vector2 sprite_unit = block_tile->unit();
	static Vector3 delta = Vector3(0.5f, 0.0f, 0.5f);
	for (size_t i = 0; i < 8; i++)
		target->add_point(voxel_vertices[i] + abs_pos + Vector3(_pos.x * chunk_size.x, 0.0f, _pos.y * chunk_size.z));
	for (size_t i = 0; i < 3; i++)
	{
		Vector2 sprite_pos = block_tile->sprite(block_sprite_face[type][i]);
		for (size_t j = 0; j < 4; j++)
			target->add_uv(voxel_uvs[j] * sprite_unit + sprite_pos);
	}
	for (size_t i = 0; i < 6; i++)
		target->add_normale(voxel_normales[i]);
}

void c_chunk::compose_voxel(Vector3 abs_pos, int type)
{
	if (type == -1)
		return;

	static int tmp_vertices_index[3] = { -1, -1, -1 };
	static int tmp_uvs_index[3] = { -1, -1, -1 };
	static int tmp_normales_index[3] = { -1, -1, -1 };
	c_mesh* target;

	if (block_alphas[type] == 1.0f)
		target = _mesh;
	else
		target = _transparent_mesh;

	size_t start_vertices = target->vertices().size();
	size_t start_uvs = target->uvs().size();
	size_t start_normales = target->normales().size();

	add_voxel_comp(target, type, abs_pos);
	for (size_t face = 0; face < 6; face++)
	{
		int neightbour = voxels(abs_pos + voxel_neighbour[face]);
		if (neightbour == -1 || (block_alphas[neightbour] != 1.0f && block_alphas[type] == 1.0f))
		{
			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					tmp_vertices_index[j] = voxel_face_vertices_index[face][i][j] + start_vertices;
					tmp_uvs_index[j] = voxel_face_uvs_index[face][i][j] + start_uvs;
					tmp_normales_index[j] = voxel_face_normales_index[face][j] + start_normales;
				}
				target->add_face(Face(tmp_vertices_index, tmp_uvs_index, tmp_normales_index, Color(150, 150, 150)));
			}
		}
	}
}

void c_chunk::set_voxel(Vector3 rel_pos, int type)
{
	if (rel_pos.x < 0 || rel_pos.y < 0 || rel_pos.z < 0 ||
		rel_pos.x >= chunk_size.x || rel_pos.y >= chunk_size.y || rel_pos.z >= chunk_size.z)
		return;
	int x = static_cast<int>(rel_pos.x);
	int y = static_cast<int>(rel_pos.y);
	int z = static_cast<int>(rel_pos.z);
	_voxels[x][y][z] = type;
}

void c_chunk::change_voxel(Vector3 rel_pos, int type)
{
	if (rel_pos.x < 0 || rel_pos.y < 0 || rel_pos.z < 0 ||
		rel_pos.x >= chunk_size.x || rel_pos.y >= chunk_size.y || rel_pos.z >= chunk_size.z)
		return;
	int x = static_cast<int>(rel_pos.x);
	int y = static_cast<int>(rel_pos.y);
	int z = static_cast<int>(rel_pos.z);
	_voxels[x][y][z] = type;
	Voxel_data data = Voxel_data(Vector3(x, y, z), type);
	_edited.push_back(data);
	if (g_board != nullptr)
		g_board->edited_voxel().push_back(Voxel_data(absolute_pos(Vector3(x, y, z)), type));
}

void c_chunk::add_voxel(Vector3 rel_pos, int type)
{
	if (rel_pos.x < 0 || rel_pos.y < 0 || rel_pos.z < 0 ||
		rel_pos.x >= chunk_size.x || rel_pos.y >= chunk_size.y || rel_pos.z >= chunk_size.z)
		return;
	int x = static_cast<int>(rel_pos.x);
	int y = static_cast<int>(rel_pos.y);
	int z = static_cast<int>(rel_pos.z);
	_voxels[x][y][z] = type;
	Voxel_data data = Voxel_data(Vector3(x, y, z), type);
	_edited.push_back(data);
	actualize();
	if (g_board == nullptr)
		return;
	g_board->edited_voxel().push_back(Voxel_data(absolute_pos(Vector3(x, y, z)), type));
	for (size_t i = 0; i < 6; i++)
	{
		Vector3 abs_pos = absolute_pos(rel_pos + voxel_neighbour[i]);
		Vector2 chunk_pos = g_board->get_chunk_pos(absolute_pos(rel_pos + voxel_neighbour[i]));
		c_chunk* tmp = g_board->chunks(chunk_pos);
		if (tmp != nullptr && g_board->voxels(abs_pos) >= 0)
			tmp->actualize();
	}
}

void c_chunk::render(c_camera* camera)
{
	if (_baked == false)
		actualize();
	_mesh->render(camera);
}

void c_chunk::render_alpha(c_camera* camera)
{
	if (_baked == false)
		actualize();
	_transparent_mesh->render(camera);
}
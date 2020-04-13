#include "aha.h"

c_board::c_board(fstream& file)
{
	string line;
	vector<string> tab;

	_spawn = Vector3(chunk_size.x / 2.0f, 4.0f, chunk_size.z / 2.0f);

	if (file.is_open() == false)
		return;

	tab = get_strsplit(file, " ", 3);
	_spawn = Vector3(atof(tab[0].c_str()), atof(tab[1].c_str()), atof(tab[2].c_str()));

	while (file.eof() == false)
	{
		line = get_str(file);
		if (line == "")
			break;
		tab = strsplit(line, " ");
		if (tab.size() != 4)
			error_exit(1, "Error while spliting a string - no correct len");
		Vector3 pos = Vector3(atoi(tab[0].c_str()), atoi(tab[1].c_str()), atoi(tab[2].c_str()));
		int type = atoi(tab[3].c_str());
		change_voxel(pos, type);
		_edited_voxel.push_back(Voxel_data(pos, type));
	}
}

void c_board::render(c_camera* camera, Vector2 player_pos, int player_vision)
{
	Vector2 chunk_pos;
	for (int i = static_cast<int>(player_pos.x) - player_vision; i <= static_cast<int>(player_pos.x) + player_vision; i++)
		for (int j = static_cast<int>(player_pos.y) - player_vision; j <= static_cast<int>(player_pos.y) + player_vision; j++)
		{
			chunk_pos = Vector2(i, j);
			if (chunk_pos.distance(player_pos) <= player_vision + 0.5f)
			{
				chunk(chunk_pos)->render(camera);
			}
		}
	for (int i = static_cast<int>(player_pos.x) - player_vision; i <= static_cast<int>(player_pos.x) + player_vision; i++)
		for (int j = static_cast<int>(player_pos.y) - player_vision; j <= static_cast<int>(player_pos.y) + player_vision; j++)
		{
			chunk_pos = Vector2(i, j);
			if (chunk_pos.distance(player_pos) <= player_vision + 0.5f)
			{
				chunk(chunk_pos)->render_alpha(camera);
			}
		}
}

Vector2 c_board::get_chunk_pos(Vector3 abs_pos)
{
	Vector2 result;

	result = Vector2(floor(abs_pos.x / chunk_size.x), floor(abs_pos.z / chunk_size.z));
	return (result);
}
Vector3 c_board::get_rel_pos(Vector3 abs_pos)
{
	Vector2 chunk_pos = get_chunk_pos(abs_pos);
	Vector3 result;

	result = abs_pos - Vector3(chunk_pos.x * chunk_size.x, 0.0f, chunk_pos.y * chunk_size.z);
	return (result.floor());
}
int c_board::voxels(Vector3 pos)
{
	if (pos.y < 0.0f)
		return (-2);
	Vector2 chunk_pos = get_chunk_pos(pos);
	Vector3 rel_pos = get_rel_pos(pos);
	return (chunk(chunk_pos)->voxels(rel_pos));
}

void c_board::set_voxel(Vector3 pos, int type)
{
	Vector2 chunk_pos = get_chunk_pos(pos);
	Vector3 rel_pos = get_rel_pos(pos);
	chunk(chunk_pos)->set_voxel(rel_pos, type);
}

void c_board::add_voxel(Vector3 pos, int type)
{
	Vector2 chunk_pos = get_chunk_pos(pos);
	Vector3 rel_pos = get_rel_pos(pos);
	chunk(chunk_pos)->add_voxel(rel_pos, type);
}

void c_board::change_voxel(Vector3 pos, int type)
{
	Vector2 chunk_pos = get_chunk_pos(pos);
	Vector3 rel_pos = get_rel_pos(pos);
	chunk(chunk_pos)->change_voxel(rel_pos, type);
}

c_chunk* c_board::chunk(Vector2 chunk_pos)
{
	if (_chunks.count(chunk_pos) == false)
		_chunks[chunk_pos] = new c_chunk(chunk_pos);
	return _chunks[chunk_pos];
}

c_chunk* c_board::chunks(Vector2 chunk_pos)
{
	if (_chunks.count(chunk_pos) == false)
		return (nullptr);
	return _chunks[chunk_pos];
}

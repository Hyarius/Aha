#include "aha.h"

c_board* g_board = nullptr;

c_game_engine::c_game_engine(string path, c_widget* p_parent) : c_widget(p_parent)
{
	fstream file = open_file(path);
	_camera = new c_camera(4, 70.0f);
	if (file.is_open() == true)
	{
		vector<string> tab = get_strsplit(file, " ", 4);
		float value[3];
		for (size_t i = 0; i < 3; i++)
			value[i] = static_cast<float>(atof((tab[1 + i]).c_str()));
		_player = new c_player(_camera, tab[0], Vector3(value[0], value[1], value[2]));
	}
	else
		_player = new c_player(_camera, "New player", Vector3(chunk_size.x / 2.0f, 4.0f, chunk_size.z / 2.0f));
	for (size_t i = 0; i < 9; i++)
		_player->set_item(-1, i, new Block_item(i, i, i));
	_board = new c_board(file);
	g_board = _board;
	_player_vision = 5;

	_active_mode = 0;
	_modes[0] = new c_editor_mode(this, _camera, _board, _player);
	g_mouse->place(g_application->size() / 2);
	_debug_screen = new c_debug_screen(this);
}

void c_game_engine::actualize_player_pos()
{
	Vector2 old_pos = _player_pos;
	_player_pos = Vector2(floor(_camera->pos().x / chunk_size.x), floor(_camera->pos().z / chunk_size.z));
	if (old_pos != _player_pos)
	{
		for (int i = static_cast<int>(old_pos.x) - _player_vision; i <= static_cast<int>(old_pos.x) + _player_vision; i++)
			for (int j = static_cast<int>(old_pos.y) - _player_vision; j <= static_cast<int>(old_pos.y) + _player_vision; j++)
			{
				Vector2 chunk_pos = Vector2(i, j);
				if (chunk_pos.distance(_player_pos) > _player_vision + 0.51f)
				{
					if (_board->chunks().count(chunk_pos) == false)
						break;
					_board->chunks(chunk_pos)->release();
				}
			}
	}
}

void c_game_engine::update()
{
	_modes[_active_mode]->update();
	actualize_player_pos();
}

bool c_game_engine::handle_keyboard()
{
	static bool tmp = false;
	if (tmp == false && g_keyboard->get_key(SDL_SCANCODE_F3) == key_state::down)
	{
		if (_modes[_active_mode]->active() == false)
		{
			_modes[_active_mode]->activate();
			_debug_screen->desactivate();
		}
		else
		{
			_modes[_active_mode]->desactivate();
			_debug_screen->activate();
		}
		tmp = true;
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_F3) == key_state::up)
		tmp = false;
	bool ret_value = _modes[_active_mode]->handle_keyboard();
	return (ret_value);
}

bool c_game_engine::handle_mouse()
{
	return (_modes[_active_mode]->handle_mouse());
}

void c_game_engine::render()
{
	_board->render(_camera, _player_pos, _player_vision);
	_modes[_active_mode]->render();
}

void c_game_engine::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

}

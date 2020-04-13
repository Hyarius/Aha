#include "aha.h"

Uint32 timer_delta = 200;

c_editor_mode::c_editor_mode(c_game_engine *p_engine, c_camera* camera, c_board* board, c_player* player) : c_game_mode(p_engine, camera, board, player)
{
	_mouse_active = false;
	_timer_delta = 180;
	_source = -1;
	_target = -1;
	_pointeur = primitive_cube(0, 0, 1, Color(255, 255, 255, 150));
	_player_info = new c_player_info(player, _engine);
	_player_info->set_geometry(Vector2(10, 10), Vector2(350, 100));
	_player_info->health_bar()->desactivate();
	_player_info->mana_bar()->desactivate();
	_player_info->activate();
	
	_shortcut_bar = new c_shortcut_bar(player, _engine);
	_shortcut_bar->activate();
}

void c_editor_mode::add_voxel(Vector3 pos, int type)
{
	if (_timer <= _actual_timer)
	{
		_board->add_voxel(pos, type);
		_timer = _actual_timer + _timer_delta;
	}
}

void c_editor_mode::set_voxel(Vector3 pos, int type)
{
	_board->set_voxel(pos, type);
}

void c_editor_mode::change_voxel(Vector3 pos, int type)
{
	_board->change_voxel(pos, type);
}

bool should_draw = false;

void c_editor_mode::render()
{
	if (should_draw == true && _active == true)
		_pointeur->render(_camera);
}

void c_editor_mode::update()
{
	_actual_timer = SDL_GetTicks();
	should_draw = voxel_raycast(_camera->pos(), _camera->forward(), &_source, &_target);
	if (should_draw == true)
		_pointeur->place(_target.floor() + 0.5f);
}

bool tmp_state = false;

bool c_editor_mode::handle_mouse()
{
	if (_mouse_active == true)
		return false;

	if (g_mouse->rel_pos != 0)
	{
		_camera->rotate(_player->rot_speed() * g_mouse->rel_pos.x, _player->rot_speed() * g_mouse->rel_pos.y);
	}
	g_mouse->place(g_application->size() / 2);
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
	{
		if (_timer <= _actual_timer)
		{
			Item* tmp = _shortcut_bar->get_item();
			if (tmp != nullptr && tmp->type == item_type::block)
				static_cast<Block_item*>(tmp)->use(Data(2, _engine, &_target));
			_timer = _actual_timer + _timer_delta;
		}
	}
	if (g_mouse->get_button(mouse_button::right) == mouse_state::down)
		add_voxel(_source, -1);
	if (g_mouse->wheel != 0)
		_shortcut_bar->edit_selected(static_cast<int>(g_mouse->wheel));
	return (false);
}

bool c_editor_mode::handle_keyboard()
{
	if (g_keyboard->get_key(SDL_SCANCODE_F1) == key_state::down)
	{
		g_application->quit();
	}
	if (g_keyboard->get_key(SDL_SCANCODE_ESCAPE) == key_state::down)
	{
		if (_mouse_active == false)
		{
			_mouse_active = true;
			_quit_menu->activate();
		}
		else
		{
			_mouse_active = false;
			_quit_menu->desactivate();
			g_mouse->place(g_application->size() / 2);
			g_mouse->update(20);
		}
		g_keyboard->reset_key(SDL_SCANCODE_ESCAPE);
	}
	if (_mouse_active == true)
		return (false);
	if (g_keyboard->get_key(SDL_SCANCODE_W) == key_state::down)
		_player->move((_camera->forward() * Vector3(1, 0, 1)).normalize() * -_player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_S) == key_state::down)
		_player->move((_camera->forward() * Vector3(1, 0, 1)).normalize() * _player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_A) == key_state::down)
		_player->move(_camera->right() * -_player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_D) == key_state::down)
		_player->move(_camera->right() * _player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_LSHIFT) == key_state::down)
		_player->move(Vector3(0.0f, -_player->move_speed(), 0.0f));
	if (g_keyboard->get_key(SDL_SCANCODE_SPACE) == key_state::down)
		_player->move(Vector3(0.0f, _player->move_speed(), 0.0f));
	return (false);
}
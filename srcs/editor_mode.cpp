#include "aha.h"

Uint32 timer_delta = 200;
c_board* g_board = nullptr;

c_editor_mode::c_editor_mode(c_camera* camera, c_board* board, c_player* player) : c_game_mode(camera, board, player)
{
	_pointeur = primitive_cube(0, 0, 1, Color(255, 255, 255, 150));
	_player_info = new c_player_info(player);
	_player_info->set_geometry(Vector2(10, 10), Vector2(350, 100));
	_player_info->health_bar()->desactivate();
	_player_info->mana_bar()->desactivate();
	_player_info->activate();
	
	_shortcut_bar = new c_shortcut_bar(player);
	_shortcut_bar->activate();
}

void c_editor_mode::add_voxel(Vector3 pos, int type)
{

}

void c_editor_mode::set_voxel(Vector3 pos, int type)
{

}

void c_editor_mode::change_voxel(Vector3 pos, int type)
{

}

bool should_draw = false;

void c_editor_mode::render()
{
	if (should_draw == true)
		_pointeur->render(_camera);
}

void c_editor_mode::update()
{
	Vector3 source;
	Vector3 target;
	should_draw = voxel_raycast(_camera->pos(), _camera->forward(), &source, &target);
	if (should_draw == true)
		_pointeur->place(target.floor() + 0.5f);
}

bool c_editor_mode::handle_mouse()
{
	if (g_mouse->rel_pos != 0)
		_camera->rotate(_player->rot_speed() * g_mouse->rel_pos.x, _player->rot_speed() * g_mouse->rel_pos.y);
	g_mouse->place(g_application->size() / 2);
	if (g_mouse->wheel != 0)
		_shortcut_bar->edit_selected(g_mouse->wheel);
	return (false);
}

bool c_editor_mode::handle_keyboard()
{
	if (g_keyboard->get_key(SDL_SCANCODE_ESCAPE) == key_state::down)
	{
		g_application->quit();
	}
	if (g_keyboard->get_key(SDL_SCANCODE_W) == key_state::down)
		_camera->move((_camera->forward() * Vector3(1, 0, 1)).normalize() * -_player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_S) == key_state::down)
		_camera->move((_camera->forward() * Vector3(1, 0, 1)).normalize() * _player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_A) == key_state::down)
		_camera->move(_camera->right() * -_player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_D) == key_state::down)
		_camera->move(_camera->right() * _player->move_speed());
	if (g_keyboard->get_key(SDL_SCANCODE_LSHIFT) == key_state::down)
		_camera->move(Vector3(0.0f, -_player->move_speed(), 0.0f));
	if (g_keyboard->get_key(SDL_SCANCODE_SPACE) == key_state::down)
		_camera->move(Vector3(0.0f, _player->move_speed(), 0.0f));
	return (false);
}
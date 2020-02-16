#include "aha.h"

class c_chunk
{
private:
	Vector3 pos;
	map<Vector3, int> voxels;

	c_mesh *mesh;
	c_mesh *mesh_transparent;
public:
	c_chunk(Vector3 pos);

	void add_voxel(Vector3 pos, int type)
	{
		voxels[pos] = type;
	}
};

class c_board
{
private:
	Vector2 chunk_size;
	map<Vector2, c_chunk *> chunks;
public:
	c_board()
	{
		chunk_size = Vector2(13, 13);
	}

	Vector2 get_chunk_pos(Vector3 voxel_pos)
	{
		Vector2 chunk_pos;

		chunk_pos = Vector2();
		return (chunk_pos);
	}
	Vector3 get_voxel_rel_pos(Vector3 voxel_pos)
	{
		Vector2 chunk_pos;
		Vector3 rel_pos;

		chunk_pos = get_chunk_pos(voxel_pos);
		rel_pos = Vector3((int)(voxel_pos.x) % (int)(chunk_size.x), (int)(voxel_pos.y), (int)(voxel_pos.z) % (int)(chunk_size.y));
		return (rel_pos);
	}
	void add_voxel(Vector3 pos, int type)
	{
		Vector2 chunk_pos = get_chunk_pos(pos);
		Vector3 rel_pos = get_voxel_rel_pos(pos);

		chunks[chunk_pos]->add_voxel(rel_pos, type);
	}
};

class c_board_widget : public c_widget
{
private:
	float _zoom;
	Vector3 _target;
	c_camera *_camera;
	c_engine *_engine;
	c_mesh *_board;
	c_mesh *_transparent_board;
public:
	c_board_widget(c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		_zoom = 0.0f;
		_camera = new c_camera(Vector3(2, 2, 2), 70.0f, 0.1f, 1000.0f);
		_target = Vector3(0.0f, 0.0f, 0.0f);
		_camera->look_at(_target);
		_engine = new c_engine();
		_board = _engine->add_mesh(new c_mesh(0));
		_transparent_board = _engine->add_mesh(new c_mesh(0));
		_transparent_board->set_transparency(0.5f);
	}
	c_camera* camera(){return (_camera);}
	c_engine* engine(){return (_engine);}
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{

	}
	c_mesh *board(){return (_board);}
	c_mesh *transparent_board(){return (_transparent_board);}
	void add_voxel(c_mesh *p_mesh)
	{
		if (p_mesh->transparency() == 1)
			_board->add_component(p_mesh);
		else
			_transparent_board->add_component(p_mesh);
	}
	c_mesh *add_mesh(c_mesh *p_mesh)
	{
		_engine->add_mesh(p_mesh);
		return (p_mesh);
	}
	void render()
	{
		static Vector2		coord = Vector2(20, 20);
		_viewport->use();
		glClear(GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() == 1.0f)
				_engine->mesh(i)->render(_camera);

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() != 1 && _engine->mesh(i)->transparency() != 0)
				_engine->mesh(i)->render(_camera);

		draw_text("Camera pos = " + _camera->pos().str(), coord, 16, 0, text_color::white);
		draw_text("Target pos = " + _target.str(), coord + Vector2(0, 18), 16, 0, text_color::white);
		draw_text("Zoom = " + ftoa(_zoom, 4), coord + Vector2(0, 36), 16, 0, text_color::white);
	}
	bool handle_mouse()
	{
		if (g_mouse->wheel != 0)
		{
			if (g_mouse->wheel < 0 || _zoom < 10)
			{
				_zoom += (g_mouse->wheel > 0 ? 1 : -1);
				_camera->move(_camera->forward().normalize() * (g_mouse->wheel < 0 ? 0.5f : -0.5f));
			}
		}
		return (false);
	}
	bool handle_keyboard()
	{
		Vector3 delta;

		if (g_keyboard->get_key(SDL_SCANCODE_Q) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(0, 1, 0) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_E) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(0, -1, 0) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_SPACE) == key_state::down)
		{
			delta = Vector3(0.0f, 0.25f, 0.0f) * g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_LCTRL) == key_state::down)
		{
			delta = Vector3(0.0f, -0.25f, 0.0f) * g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_W) == key_state::down)
		{
			delta = _camera->forward() * Vector3(0.25f, 0.0f, 0.25f) * -g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_S) == key_state::down)
		{
			delta = _camera->forward() * Vector3(0.25f, 0.0f, 0.25f) * g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_A) == key_state::down)
		{
			delta = _camera->right() * Vector3(0.25f, 0.0f, 0.25f) * -g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_D) == key_state::down)
		{
			delta = _camera->right() * Vector3(0.25f, 0.0f, 0.25f) * g_application->fps_ratio();
			_target += delta;
			_camera->move(delta);
			_camera->look_at(_target);
		}
		return (false);
	}
};

int		main(void)
{
	c_application app = c_application("Aha (c)", Vector2(840, 680));
	app.set_font_path("ressources/font/karma suture.ttf");
	app.set_max_fps(660);

	c_board_widget render = c_board_widget();
	render.set_geometry(0, app.size());
	render.activate();

	c_tileset *tile = new c_tileset("ressources/texture/tileset.png", Vector2(9, 4));

	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			render.add_voxel(primitive_voxel(Vector3(i, 0.0f, j), tile, (i == 0 || i == 9 || j == 0 || j == 9 ? 1 : 0)));

	render.board()->bake();
	render.board()->set_texture(tile);
	render.transparent_board()->bake();
	render.transparent_board()->set_texture(tile);

	return (app.run());
}

#include "aha.h"

class c_board_widget : public c_widget
{
private:
	Vector3 _target;
	c_camera *_camera;
	c_engine *_engine;
	c_mesh *_board;
	c_mesh *_transparent_board;
public:
	c_board_widget(c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		_camera = new c_camera(Vector3(13, 5, 13));
		_target = Vector3(4.5f, 0.5f, 4.5f);
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

		draw_text("Camera pos = " + _camera->pos().str(), coord, 20, 0, text_color::white);

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() == 1.0f)
				_engine->mesh(i)->render(_camera);

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() != 1 && _engine->mesh(i)->transparency() != 0)
				_engine->mesh(i)->render(_camera);
	}
	bool handle_keyboard()
	{
		if (g_keyboard->get_key(SDL_SCANCODE_A) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(0, 1, 0) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_D) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(0, -1, 0) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_W) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(0, 0, 1) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		if (g_keyboard->get_key(SDL_SCANCODE_S) == key_state::down)
		{
			_camera->rotate_around_point(_target, Vector3(1, 0, 0) * g_application->fps_ratio());
			_camera->look_at(_target);
		}
		return (false);
	}
};

int		main(void)
{
	c_application app = c_application("Aha (c)", Vector2(840, 680));
	app.set_font_path("ressources/fonts/karma suture.ttf");
	app.set_max_fps(660);

	c_board_widget render = c_board_widget();
	render.set_geometry(0, app.size());
	render.activate();

	c_tileset *tile = new c_tileset("ressources/texture/tileset.png", Vector2(9, 4));

	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			render.add_voxel(primitive_voxel(Vector3(i, 0.0f, j), tile, 0));

	render.add_voxel(primitive_voxel(Vector3(0, 1, 0), tile, 1));
	render.add_voxel(primitive_voxel(Vector3(9, 1, 9), tile, 2));
	render.add_voxel(primitive_voxel(Vector3(9, 1, 0), tile, 3, 0.5f));
	render.add_voxel(primitive_voxel(Vector3(0, 1, 9), tile, 4, 0.5f));

	render.add_voxel(primitive_voxel(Vector3(0, 2, 0), tile, 5, 0.5f));
	render.add_voxel(primitive_voxel(Vector3(9, 2, 9), tile, 6));
	render.add_voxel(primitive_voxel(Vector3(9, 2, 0), tile, 7));
	render.add_voxel(primitive_voxel(Vector3(0, 2, 9), tile, 8));

	render.board()->bake();
	render.board()->set_texture(tile);
	render.transparent_board()->bake();
	render.transparent_board()->set_texture(tile);

	return (app.run());
}

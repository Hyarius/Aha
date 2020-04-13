#include "aha.h"

void save_game(Data param)
{
	c_game_engine *engine = param.acces<c_game_engine*>(0);
	save_map(engine);
}

void quit_game(Data param)
{
	g_application->quit();
}

void save_quit_game(Data param)
{
	save_game(param);
	quit_game(nullptr);
}

c_quit_menu::c_quit_menu(c_game_engine* p_engine, c_widget *p_parent) : c_widget(p_parent)
{
	_engine = p_engine;

	_back_frame = new c_frame(this);
	_back_frame->activate();

	_save_button = new c_button(save_game, _engine, _back_frame);
	_save_button->set_text("Sauvegarder la partie");
	_save_button->activate();
	_save_quit_button = new c_button(save_quit_game, _engine, _back_frame);
	_save_quit_button->set_text("Sauvegarder et quitter la partie");
	_save_quit_button->activate();
	_quit_button = new c_button(quit_game, nullptr, _back_frame);
	_quit_button->set_text("Quitter la partie");
	_quit_button->activate();
}

void c_quit_menu::render()
{
	fill_rectangle(anchor(), area(), Color(0, 0, 0, 150));
}

void c_quit_menu::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 tmp_size = p_area / 2;
	_back_frame->set_geometry(p_anchor + tmp_size / 2, tmp_size);

	tmp_size = Vector2(tmp_size.x - 10 - _back_frame->border() * 2, 60.0f);
	Vector2 tmp_pos = Vector2(5.0f, _back_frame->area().y - (tmp_size.y + 5));
	_quit_button->set_geometry(tmp_pos, tmp_size);
	tmp_pos.y -= tmp_size.y + 5;
	_save_quit_button->set_geometry(tmp_pos, tmp_size);
	tmp_pos.y -= tmp_size.y + 5;
	_save_button->set_geometry(tmp_pos, tmp_size);
}

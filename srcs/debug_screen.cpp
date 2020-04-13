#include "aha.h"

c_debug_screen::c_debug_screen(c_game_engine* p_engine, c_widget *p_parent) : c_widget(p_parent)
{
	_engine = p_engine;
}

void c_debug_screen::draw_line(int& nb_line, string text)
{
	draw_text(text, Vector2(0, 0 + nb_line * 20) + 10, 16, 0, text_color::white);
	nb_line++;
}

string c_debug_screen::parse_direction(Vector3 direction)
{
	float angle = radian_to_degree(atan2(direction.x, direction.z));
	if (angle < -45)
		angle += 360;
	if (is_middle(-45, angle, 45) == true)
		return ("North");
	else if (is_middle(45, angle, 135) == true)
		return ("Est");
	else if (is_middle(135, angle, 225) == true)
		return ("South");
	else
		return ("Ouest");
}

void c_debug_screen::render()
{
	int nb_line = 0;

	draw_line(nb_line, "Player name : " + _engine->player()->name());
	draw_line(nb_line, "Player position : " + _engine->player()->pos().str());
	draw_line(nb_line, "Player direction : " + parse_direction(_engine->camera()->forward().invert()));
	draw_line(nb_line, "Player chunk : " + _engine->player_pos().str());
	draw_line(nb_line, "Nb chunk loaded : " + to_string(_engine->board()->chunks().size()));
	draw_line(nb_line, "FPS : " + to_string(print_fps));
}
#include "aha.h"

c_player_info::c_player_info(c_player* p_player, c_widget* p_parent) : c_widget(p_parent)
{
	_player = p_player;
	_player_face = new c_image_label(nullptr, this);
	_player_face->set_back(Color(120, 120, 120));
	_player_face->set_front(Color(160, 160, 160));
	_player_face->activate();
	_player_name = new c_text_label(_player->name(), this);
	_player_name->set_back(Color(120, 120, 120));
	_player_name->set_front(Color(160, 160, 160));
	_player_name->activate();
	_health_bar = new c_stat_bar(_player->health(), Color(175, 0, 0), this);
	_health_bar->activate();
	_mana_bar = new c_stat_bar(_player->mana(), Color(0, 0, 175), this);
	_mana_bar->activate();
}

void c_player_info::render()
{

}

void c_player_info::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_player_face->set_geometry(0, p_area.y);
	Vector2 tmp_pos = Vector2(p_area.y + 5.0f, 0.0f);
	Vector2 tmp_size = Vector2(p_area.x - p_area.y - 5, (p_area.y - 10) / 3.0f);
	_player_name->set_geometry(tmp_pos, tmp_size);
	_health_bar->set_geometry(tmp_pos + Vector2(0.0f, tmp_size.y + 5.0f), tmp_size);
	_mana_bar->set_geometry(tmp_pos + Vector2(0.0f, tmp_size.y + 5.0f) * 2, tmp_size);
}
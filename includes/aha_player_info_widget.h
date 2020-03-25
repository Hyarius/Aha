#ifndef AHA_PLAYER_INFO_WIDGET_H
#define AHA_PLAYER_INFO_WIDGET_H

#include "aha_item_slot.h"
#include "aha_player.h"
#include "aha_stat_bar.h"

class c_player_info : public c_widget
{
protected:
	c_player* _player;

	c_image_label* _player_face;
	c_text_label* _player_name;
	c_stat_bar* _health_bar;
	c_stat_bar* _mana_bar;
public:
	c_player_info(c_player* p_player, c_widget *p_parent = nullptr);
	c_image_label* player_face() { return (_player_face); }
	c_text_label* player_name() { return (_player_name); }
	c_stat_bar* health_bar() { return (_health_bar); }
	c_stat_bar* mana_bar() { return (_mana_bar); }
	void render();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
};

#endif
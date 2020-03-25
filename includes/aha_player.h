#ifndef AHA_PLAYER_H
#define AHA_PLAYER_H

#include "jgl.h"

#include "aha_entity.h"

#include "aha_inventory.h"

struct Stat
{
	int actual;
	int max;
};

class c_player : public c_entity
{
protected:
	int _selected;
	Stat _health;
	Stat _mana;
	float _move_speed;
	float _rot_speed;
	c_inventory* _inventory;
public:
	c_player(string p_name, Vector3 p_pos) : c_entity(p_name, p_pos, Team::ally)
	{
		_health = { 100, 100 };
		_mana = { 10, 20 };
		_selected = 0;
		_move_speed = 0.1f;
		_rot_speed = 0.5f;
		_inventory = new c_inventory();
	}
	int selected() { return (_selected); }
	Stat *health() { return (&_health); }
	Stat *mana() { return (&_mana); }
	float move_speed() { return (_move_speed); }
	float rot_speed() { return (_rot_speed); }
	c_inventory *inventory() { return (_inventory); }
};

#endif
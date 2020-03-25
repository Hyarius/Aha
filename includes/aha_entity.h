#ifndef AHA_ENTITY_H
#define AHA_ENTIT_H

#include "jgl.h"

enum class Team
{
	neutral = 0,
	ally = 1,
	enemy = 2
};

class c_entity
{
protected:
	Vector3 _pos;
	string _name;
	Team _team;

public:
	c_entity(string p_name, Vector3 p_pos, Team p_team)
	{
		_pos = p_pos;
		_name = p_name;
		_team = p_team;
	}
	Vector3 pos() { return (_pos); }
	string name() { return (_name); }
	Team team() { return (_team); }
};

#endif
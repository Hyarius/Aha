#ifndef AHA_INVENTORY_MENU
#define AHA_INVENTORY_MENU

class c_inventory_menu
{
protected:
	c_player* _player;
	c_frame* _backframe;
	c_shortcut_bar* _shortcut;

public:
	c_inventory_menu(c_player *p_player, c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		_player = p_player;

	}
};

#endif
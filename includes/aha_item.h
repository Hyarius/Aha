#ifndef AHA_ITEM_H
#define AHA_ITEM_H

enum class item_type
{
	error = -1,
	item = 0,
	block = 1
};

struct Item
{
	item_type type;
	int id;
	int icon;

	Item(int p_id = -1, int p_icon = -1);

	virtual void use(Data data = nullptr) = 0;
};

struct Block_item : public Item
{
	int block_id;

	Block_item(int p_id, int p_icon, int p_block_id);

	void use(Data data = nullptr);
};

#endif
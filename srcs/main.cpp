#include "aha.h"

c_tileset* block_tile = nullptr;
c_tileset* icon_tile = nullptr;

Vector3 chunk_size = { 15, 256, 15 };

int		main(int argc, char **argv)
{
	c_application app = c_application("Aha (c)", Vector2(840, 680));
	app.set_font_path("ressources/font/karma suture.ttf");
	app.set_max_fps(660);

	block_tile = new c_tileset("ressources/texture/tileset.png", Vector2(9, 4));
	icon_tile = new c_tileset("ressources/texture/icons.png", Vector2(3, 4));
	c_game_engine engine = c_game_engine("ressources/maps/saved_map.map");
	engine.set_geometry(0, app.size());
	engine.activate();


	

	return (app.run());
}

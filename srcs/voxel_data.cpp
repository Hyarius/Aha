#include "aha.h"

float block_alphas[] = {
	1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
};

size_t block_sprite_face[][3] = {
	{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
	{9, 10, 11}, {12, 13, 14}, {15, 16, 17},
	{18, 19, 20}, {21, 22, 23}, {24, 25, 26},
	{27, 28, 29}, {30, 31, 32}, {33, 34, 35}
};

Vector3 voxel_neighbour[6] = {
	{0.0f, -1.0f, 0.0f},//FACE DOWN
	{0.0f, 1.0f, 0.0f},//FACE TOP
	{0.0f, 0.0f, -1.0f},//FACE FRONT
	{0.0f, 0.0f, 1.0f},//FACE BACK
	{1.0f, 0.0f, 0.0f},//FACE RIGHT
	{-1.0f, 0.0f, 0.0f}//FACE LEFT
};

Vector3 voxel_vertices[8] = {
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f}
};

Vector2 voxel_uvs[4] = {
	{0, 0},
	{1, 0},
	{1, 1},
	{0, 1}
};

Vector3 voxel_normales[6] = {
	//FACE DOWN
	{0.0f, -1.0f, 0.0f},
	//FACE TOP
	{0.0f, 1.0f, 0.0f},
	//FACE FRONT
	{1.0f, 0.0f, 0.0f},
	//FACE BACK
	{-1.0f, 0.0f, 0.0f},
	//FACE RIGHT
	{0.0f, 0.0f, 1.0f},
	//FACE LEFT
	{0.0f, 0.0f, -1.0f}
};

int  voxel_face_vertices_index[6][2][3] = {
	//FACE DOWN
	{
		{2, 3, 1},
		{0, 1, 3}
	},
	//FACE TOP
	{
		{6, 5, 7},
		{4, 7, 5}
	},
	//FACE FRONT
	{
		{5, 1, 4},
		{0, 4, 1}
	},
	//FACE BACK
	{
		{6, 7, 2},
		{3, 2, 7}
	},
	//FACE RIGHT
	{
		{6, 2, 5},
		{1, 5, 2}
	},
	//FACE LEFT
	{
		{7, 4, 3},
		{0, 3, 4}
	},
};

int  voxel_face_uvs_index[6][2][3] = {
	//FACE DOWN
	{
		{2, 3, 1},
		{0, 1, 3}
	},
	//FACE TOP
	{
		{10, 9, 11},
		{8, 11, 9}
	},
	//FACE FRONT
	{
		{6, 5, 7},
		{4, 7, 5}
	},
	//FACE BACK
	{
		{6, 5, 7},
		{4, 7, 5}
	},
	//FACE RIGHT
	{
		{6, 5, 7},
		{4, 7, 5}
	},
	//FACE LEFT
	{
		{6, 5, 7},
		{4, 7, 5}
	},
};

int  voxel_face_normales_index[6][3] = {
	//FACE DOWN
	{0, 0, 0},
	//FACE TOP
	{1, 1, 1},
	//FACE FRONT
	{2, 2, 2},
	//FACE BACK
	{3, 3, 3},
	//FACE RIGHT
	{4, 4, 4},
	//FACE LEFT
	{5, 5, 5}
};
#pragma once

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR, ML, MC, MR, BL, BC, BR, Custom,
};

enum class Sides
{
	None = -1, Left, Right, Count
};

enum class Languages
{
	Korean, English
};

enum class Direction
{
	None = -1,
	Right,
	RightUp,
	Up,
	LeftUp, 
	Left, 
	LeftDown,
	Down,
	RightDown,
};
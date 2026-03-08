#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main() {
	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.Print();

	LBlock block = LBlock();

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(darkBlue);

		grid.Draw();

		block.Draw();

		EndDrawing();
	}
	CloseWindow();
}
#include <raylib.h>
#include "grid.h"

int main() {
	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.grid[0][0] = 3;
	grid.Print();

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(darkBlue);

		grid.Draw();

		EndDrawing();
	}
	CloseWindow();
}
#include "game.h"
#include <random>

Game::Game() {
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
}

Block Game::GetRandomBlock() {
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks() {
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() {
	grid.Draw();
	currentBlock.Draw();
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) {
		Reset();
		gameOver = false;
	}

	if (keyPressed == KEY_UP || keyPressed == KEY_W) {
		RotateBlock();
	}
	static float holdTimer = 0;
	static double lastStepTime = 0;

	float deltaTime = GetFrameTime();
	const float DAS_DELAY = 0.25f;
	const float DAS_SPEED = 0.10f;

	bool isLeftPressed = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
	bool isRightPressed = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
	bool isDownPressed = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);

	if (isLeftPressed || isRightPressed || isDownPressed) {
		if (holdTimer == 0) {
			if (isLeftPressed) MoveBlockLeft();
			if (isRightPressed) MoveBlockRight();
			if (isDownPressed) MoveBlockDown();
		}

		holdTimer += deltaTime;

		if (holdTimer >= DAS_DELAY) {
			if (GetTime() - lastStepTime >= DAS_SPEED) {
				if (isLeftPressed) MoveBlockLeft();
				if (isRightPressed) MoveBlockRight();
				if (isDownPressed) MoveBlockDown();
				lastStepTime = GetTime();
			}
		}
	}
	else {
		holdTimer = 0;
	}
}

void Game::MoveBlockLeft() {
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
	
}

void Game::MoveBlockRight() {
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
	
}

void Game::MoveBlockDown() {
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
	
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void Game::RotateBlock()
{
	if (!gameOver) {
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.UndoRotation();
		}
	}
}

void Game::LockBlock() {
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	grid.ClearFullRows();
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

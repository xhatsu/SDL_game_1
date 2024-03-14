#include"background.h"
	void backGround::renderChunk() {
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_RIGHT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN_RIGHT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP_RIGHT);
	}

	void backGround::stickChunk() {
		background_rect_UP.y = background_rect.y - 1440;
		background_rect_LEFT.y = background_rect.y;
		background_rect_RIGHT.y = background_rect.y;
		background_rect_UP_RIGHT.y = background_rect_UP.y;
		background_rect_UP_LEFT.y = background_rect_UP.y;
		background_rect_DOWN.y = background_rect.y + 1440;
		background_rect_DOWN_LEFT.y = background_rect_DOWN.y;
		background_rect_DOWN_RIGHT.y = background_rect_DOWN.y;

		background_rect_UP.x = background_rect.x;
		background_rect_LEFT.x = background_rect.x - 2560;
		background_rect_RIGHT.x = background_rect.x + 2560;
		background_rect_UP_RIGHT.x = background_rect_UP.x + 2560;
		background_rect_UP_LEFT.x = background_rect_UP.x - 2560;
		background_rect_DOWN.x = background_rect.x;
		background_rect_DOWN_LEFT.x = background_rect_DOWN.x - 2560;
		background_rect_DOWN_RIGHT.x = background_rect_DOWN.x + 2560;
	}

	void backGround::moveChunk(int direction) {
		switch (direction) {
		case DOWN:
			background_rect.y -= speed;
			background_rect_UP.y -= speed;
			background_rect_DOWN.y -= speed;
			background_rect_LEFT.y -= speed;
			background_rect_RIGHT.y -= speed;
			background_rect_UP_LEFT.y -= speed;
			background_rect_UP_RIGHT.y -= speed;
			background_rect_DOWN_RIGHT.y -= speed;
			background_rect_DOWN_LEFT.y -= speed;
			break;
		case UP:
			background_rect.y += speed;
			background_rect_UP.y += speed;
			background_rect_DOWN.y += speed;
			background_rect_LEFT.y += speed;
			background_rect_RIGHT.y += speed;
			background_rect_UP_LEFT.y += speed;
			background_rect_UP_RIGHT.y += speed;
			background_rect_DOWN_RIGHT.y += speed;
			background_rect_DOWN_LEFT.y += speed;
			break;
		case LEFT:
			background_rect.x += speed;
			background_rect_UP.x += speed;
			background_rect_DOWN.x += speed;
			background_rect_LEFT.x += speed;
			background_rect_RIGHT.x += speed;
			background_rect_UP_LEFT.x += speed;
			background_rect_UP_RIGHT.x += speed;
			background_rect_DOWN_RIGHT.x += speed;
			background_rect_DOWN_LEFT.x += speed;
			break;
		case RIGHT:
			background_rect.x -= speed;
			background_rect_UP.x -= speed;
			background_rect_DOWN.x -= speed;
			background_rect_LEFT.x -= speed;
			background_rect_RIGHT.x -= speed;
			background_rect_UP_LEFT.x -= speed;
			background_rect_UP_RIGHT.x -= speed;
			background_rect_DOWN_RIGHT.x -= speed;
			background_rect_DOWN_LEFT.x -= speed;
			break;
		default:
			break;
		}
	}

	void backGround::updateChunk(unsigned int state) {
		switch (state) {
		case UP:
			if (background_rect.y < -720) {
				background_rect.y = background_rect.y + 1440;
			}
			stickChunk();
			moveChunk(UP);
			renderChunk();
			if (background_rect.y >= 720) {
				background_rect.y -= 1440;
				background_rect_UP.y -= 1440;
				background_rect_DOWN.y -= 1440;
				background_rect_LEFT.y -= 1440;
				background_rect_RIGHT.y -= 1440;
				background_rect_UP_LEFT.y -= 1440;
				background_rect_UP_RIGHT.y -= 1440;
				background_rect_DOWN_RIGHT.y -= 1440;
				background_rect_DOWN_LEFT.y -= 1440;
			}
			break;
		case DOWN:
			if (background_rect.y > 0) {
				background_rect.y = background_rect.y - 1440;
			}
			stickChunk();
			moveChunk(DOWN);
			renderChunk();
			if (background_rect.y <= -1440) {
				background_rect.y += 1440;
				background_rect_UP.y += 1440;
				background_rect_DOWN.y += 1440;
				background_rect_LEFT.y += 1440;
				background_rect_RIGHT.y += 1440;
				background_rect_UP_LEFT.y += 1440;
				background_rect_UP_RIGHT.y += 1440;
				background_rect_DOWN_RIGHT.y += 1440;
				background_rect_DOWN_LEFT.y += 1440;
			}
			break;
		case LEFT:
			if (background_rect.x <= -1280) {
				background_rect.x = background_rect.x + 2560;
			}
			stickChunk();
			moveChunk(LEFT);
			renderChunk();
			if (background_rect.x >= 1280) {
				background_rect.x -= 2560;
				background_rect_UP.x -= 2560;
				background_rect_DOWN.x -= 2560;
				background_rect_LEFT.x -= 2560;
				background_rect_RIGHT.x -= 2560;
				background_rect_UP_LEFT.x -= 2560;
				background_rect_UP_RIGHT.x -= 2560;
				background_rect_DOWN_RIGHT.x -= 2560;
				background_rect_DOWN_LEFT.x -= 2560;
			}
			break;
		case RIGHT:
			if (background_rect.x >= 0) {
				background_rect.x = background_rect.x - 2560;
			}
			stickChunk();
			moveChunk(RIGHT);
			renderChunk();
			if (background_rect.x <= -2560) {
				background_rect.x += 2560;
				background_rect_UP.x += 2560;
				background_rect_DOWN.x += 2560;
				background_rect_LEFT.x += 2560;
				background_rect_RIGHT.x += 2560;
				background_rect_UP_LEFT.x += 2560;
				background_rect_UP_RIGHT.x += 2560;
				background_rect_DOWN_RIGHT.x += 2560;
				background_rect_DOWN_LEFT.x += 2560;
			}
			break;
		default:
			renderChunk();
			break;
		}

	}

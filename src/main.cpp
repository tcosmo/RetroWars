#include <SDL2/SDL.h>
#include <stdbool.h>

int main() {
  SDL_Window* screen =
      SDL_CreateWindow("Retro Wars", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

  SDL_Renderer* renderer =
      SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  bool is_running = true;
  SDL_Event ev;

  while (is_running) {
    if (SDL_PollEvent(&ev)) {
      switch (ev.type) {
        case SDL_QUIT:
          is_running = false;
          break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect dst = {.x = 50, .y = 0, .w = 40, .h = 40};

    SDL_RenderDrawRect(renderer, &dst);
    SDL_RenderPresent(renderer);
  }
}

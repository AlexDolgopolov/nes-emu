#include "framebuffero.h"
#include <stdio.h>
#include <SDL3/SDL.h>

extern uint32_t framebuffer[256 * 240];

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
SDL_Texture* texture = NULL;

bool framebuffero_init(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    // 1. Создаем строго ТОЛЬКО окно
    window = SDL_CreateWindow("NES Emulator", 256 * 3, 240 * 3, 0);
    if (!window) {
        SDL_Log("Window Error: %s", SDL_GetError());
        return false;
    }

    // 2. Создаем ТОЛЬКО рендерер, привязанный к нашему окну
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Renderer Error: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderLogicalPresentation(renderer, 256, 240, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 3. Создаем текстуру
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);
    if (!texture) {
        SDL_Log("Texture Error: %s", SDL_GetError());
        return false;
    }

    // 4. ВАЖНО: Отключаем сглаживание ПОСЛЕ того, как текстура создана!
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return true;
}

void framebuffero_output(){
    // 1. Копируем твой массив framebuffer в текстуру видеокарты
    // Pitch - это длина одной строки в байтах (256 пикселей * 4 байта)
    SDL_UpdateTexture(texture, NULL, framebuffer, 256 * sizeof(uint32_t));

    // 2. Очищаем экран (необязательно, если текстура рисуется на весь экран, но хороший тон)
    SDL_RenderClear(renderer);

    // 3. Растягиваем текстуру на весь экран (SDL сам применит Logical Presentation)
    SDL_RenderTexture(renderer, texture, NULL, NULL);

    // 4. Показываем результат пользователю
    SDL_RenderPresent(renderer);
}


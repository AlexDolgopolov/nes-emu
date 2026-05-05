/*
 * NES-emu
 * Copyright (C) 2026 Alex Dolgopolov
 *
 * This file is part of NES-emu.
 *
 * NES-emu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NES-emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NES-emu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "framebuffero.h"
#include "ppu.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include "debug.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
SDL_Texture* texture = NULL;
extern bool nes_running;

bool framebuffero_init(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Nes Emulator", 256 * 3, 240 * 3, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    DEBUG_PPU("Create window\n");

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
    uint32_t* framebuffer = get_framebuffer_ptr();
    SDL_UpdateTexture(texture, NULL, framebuffer, 256 * sizeof(uint32_t));

    // 2. Очищаем экран (необязательно, если текстура рисуется на весь экран, но хороший тон)
    SDL_RenderClear(renderer);

    // 3. Растягиваем текстуру на весь экран (SDL сам применит Logical Presentation)
    SDL_RenderTexture(renderer, texture, NULL, NULL);

    // 4. Показываем результат пользователю
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            nes_running = false;
        }
    }
}


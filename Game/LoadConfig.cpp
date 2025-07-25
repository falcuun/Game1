#include "json.hpp"
#include "Player.h"
#include <fstream>

#include <SDL3/SDL.h>

using json = nlohmann::json;

extern "C" SDL_FRect* load_animation_frames(const char* name, int* out_count) {
    std::ifstream file("player_config.json");
    if (!file.is_open()) return nullptr;

    json data = json::parse(file);
    file.close();

    if (!data.contains("animation_rectangles") || !data["animation_rectangles"].contains(name))
        return nullptr;

    const json& array = data["animation_rectangles"][name];
    int count = array.size();
    if (out_count) *out_count = count;

    SDL_FRect* rects = new SDL_FRect[count];
    for (int i = 0; i < count; ++i) {
        rects[i].x = array[i]["x"];
        rects[i].y = array[i]["y"];
        rects[i].w = array[i]["w"];
        rects[i].h = array[i]["h"];
    }

    return rects;
}

extern "C" void free_animation_frames(SDL_FRect* frames) {
    delete[] frames;
}

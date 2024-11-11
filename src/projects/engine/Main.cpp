#include <Windows.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include "lua5/lua.hpp"
#include "LuaBridge/LuaBridge.h"

void ShowMsg(const char* title, const char* message)
{
    MessageBoxA(nullptr, message, title, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luabridge::getGlobalNamespace(L)
        .beginNamespace("SDL")
            .addFunction("Init", SDL_Init)
            .addFunction("MessageBox", ShowMsg)
            .addFunction("Quit", SDL_Quit)
            .addFunction("CreateWindow", SDL_CreateWindow)
            .addFunction("CreateRenderer", SDL_CreateRenderer)
            .addFunction("PollEvent", SDL_PollEvent)
            .addFunction("Delay", SDL_Delay)
            .addFunction("DestroyWindow", SDL_DestroyWindow)
            .addFunction("DestroyRenderer", SDL_DestroyRenderer)
            .addFunction("GetError", SDL_GetError)
        .endNamespace();

    if (luaL_dofile(L, "game.lua")) {
        MessageBoxA(nullptr, lua_tostring(L, -1), "KiwiEngine - LUA Error", MB_OK | MB_ICONERROR);
        lua_pop(L, 1);
    }

    lua_close(L);

	return EXIT_SUCCESS;
}
#include <lua.h>
#include <lauxlib.h>
#include <hangul-1.0/hangul.h>

int lua_hangul_ic_process(lua_State* L) {
    // * hic ascii
    HangulInputContext* hic = lua_touserdata(L, -2);
    int ascii = lua_tointeger(L, -1);
    lua_pushboolean(L, hangul_ic_process(hic, ascii)); // * hic ascii result
    return 1;
}

int lua_hangul_ic_get_preedit_string(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushlightuserdata(L, hangul_ic_get_preedit_string(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_get_commit_string(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushlightuserdata(L, hangul_ic_get_commit_string(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_reset(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    hangul_ic_reset(hic); // * hic
    return 0;
}

int lua_hangul_ic_flush(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushlightuserdata(L, hangul_ic_flush(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_backspace(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_backspace(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_is_empty(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_is_empty(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_has_choseong(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_has_choseong(hic)); // * hic result
    return 1;
}

int lua_hangul_ic_has_jungseong(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_has_jungseong(hic));
    return 1;
}

int lua_hangul_ic_has_jongseong(lua_State* L) {
    // * hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_has_jongseong(hic));
    return 1;
}

int lua_hangul_ic_get_option(lua_State* L) {
    // * hic option
    lua_tointeger(L, -2); // 
    HangulInputContext* hic = lua_touserdata(L, -2);
    int option = lua_tointeger(L, -1);
    lua_pushboolean(L, hangul_ic_get_option(L, hic, option));
    return 1;
}

int lua_hangul_ic_set_option(lua_State* L) {
    // * hic option value
    HangulInputContext* hic = lua_touserdata(L, -3);
    int option = lua_tointeger(L, -2);
    bool value = lua_toboolean(L, -1);
    hangul_ic_set_option(hic, option, value);
    return 0;
}

int lua_hangul_ic_select_keyboard(lua_State* L) {
    HangulInputContext* hic = lua_touserdata(L, -2);
    const char* id = lua_tostring(L, -1);
    hangul_ic_select_keyboard(hic, id);
    return 0;
}

int lua_hangul_ic_is_transliteration(lua_State* L) {
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pushboolean(L, hangul_ic_is_transliteration(hic)); // result
    return 1;
}

static const struct luaL_Reg lua_hangul_ic_methods[] = {
    {"process", lua_hangul_ic_process},
    {"get_preedit_string", lua_hangul_ic_get_preedit_string},
    {"get_commit_string", lua_hangul_ic_get_commit_string},
    {"reset", lua_hangul_ic_reset},
    {"flush", lua_hangul_ic_flush},
    {"backspace", lua_hangul_ic_backspace},
    {"empty", lua_hangul_ic_is_empty},
    {"has_choseong", lua_hangul_ic_has_choseong},
    {"has_jungseong", lua_hangul_ic_has_jungseong},
    {"has_jongseong", lua_hangul_ic_has_jongseong},
    {"get_option", lua_hangul_ic_get_option},
    {"set_option", lua_hangul_ic_set_option},
    {"select_keyboard", lua_hangul_ic_select_keyboard},
    {"is_transliteration", lua_hangul_ic_is_transliteration},
    {NULL, NULL}
};

int lua_hangul_ic_new(lua_State* L) {
    lua_newtable(L); // table
    luaL_setfuncs(L, lua_hangul_ic_methods, 0); //
}

static const struct luaL_Reg lua_hangul_functions[] = {
    {"ic_new", lua_hangul_ic_new},
    {NULL, NULL}
};

int luaopen_hangul(lua_State* L) {
    luaL_newmetatable(L, "lua_hangul_ic"); // lua_hangul_ic
    lua_pushvalue(L, -1); // lua_hangul_ic lua_hangul_ic
    lua_setfield(L, -2, "__index"); // lua_hangul_ic
    luaL_setfuncs(L, lua_hangul_ic_methods, 0); //
    luaL_newlib(L, lua_hangul_functions);
    return 1;
}

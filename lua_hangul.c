#include <lua.h>
#include <luaxlib.h>
int lua_hangul_ic_process(lua_State* L) {
}
int lua_hangul_ic_get_preedit_string(lua_State* L) {
}
int lua_hangul_ic_get_commit_string(lua_State* L) {
}
int lua_hangul_ic_reset(lua_State* L) {
}
int lua_hangul_ic_flush(lua_State* L) {
}
int lua_hangul_ic_backspace(lua_State* L) {
}
int lua_hangul_ic_empty(lua_State* L) {
}
int lua_hangul_ic_has_choseong(lua_State* L) {
}
int lua_hangul_ic_has_jungseong(lua_State* L) {
}
int lua_hangul_ic_has_jongseong(lua_State* L) {
}
int lua_hangul_ic_get_option(lua_State* L) {
}

int lua_hangul_ic_set_option(lua_State* L) {
}





static const struct luaL_Reg lua_hangul_ic_methods[] = {
    {"process", lua_hangul_ic_process},
    {"get_preedit_string", lua_hangul_ic_get_preedit_string},
    {"get_commit_string", lua_hangul_ic_get_commit_string},
    {"reset", lua_hangul_ic_reset},
    {"flush", lua_hangul_ic_flush},
    {"backspace", lua_hangul_ic_backspace},
    {"empty", lua_hangul_ic_empty},
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
    lua_setfuncs(L, hangul_ic_methods, 0); //
}

static const struct luaL_Reg lua_hangul_functions[] = {
    {"ic_new", lua_hangul_ic_new},
    {NULL, NULL}
};

int luaopen_hangul(lua_State* L) {
    luaL_newmetatable(L, "lua_hangul_ic"); // lua_hangul_ic
    lua_pushvalue(L, -1); // lua_hangul_ic lua_hangul_ic
    lua_setfield(L, -2, "__index"); // lua_hangul_ic
    lua_setfuncs(L, lua_hangul_ic_methods, 0);

    luaL_newlib(L, lua_hangul_functions);
    return 1;
}

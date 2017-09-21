/*
 * Lua extension library for libhangul.
 * Author: Byeonggon Lee <gonny952@gmail.com>
 * License: Same as libhangul.
 */

#include <lua.h>
#include <lauxlib.h>
#include <hangul.h>
#include <iconv.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include <err.h>

int utf8_to_ucs4(char* inbuf, size_t inbufbytes, ucschar* outbuf, size_t outbufbytes) {
    char* inbuftemp = inbuf;
    char* outbuftemp = (char*)outbuf;
    size_t inbufbytesleft = inbufbytes;
    size_t outbufbytesleft = outbufbytes;

    iconv_t cd = iconv_open("UCS-4LE", "UTF-8");
    if(cd == (iconv_t) - 1) {
        fprintf(stderr, "iconv_open failed with %d\n", errno);
        return -1;
    }

    int rc = iconv(cd, &inbuftemp, &inbufbytesleft, &outbuftemp, &outbufbytesleft);
    if(rc == -1) {
        fprintf(stderr, "LINE %d: iconv failed with -1. errno is %d: %s\n", __LINE__, errno, strerror(errno));
        return -1;
    }

    rc = iconv_close(cd);
    if(rc != 0) {
        fprintf(stderr, "iconv_close failed with %d\n", errno);
        return -1;
    }
}

int ucs4_to_utf8(ucschar* inbuf, size_t inbufbytes, char* outbuf, size_t outbufbytes) {
    char* inbuftemp = (char*)inbuf;
    char* outbuftemp = outbuf;
    size_t inbufbytesleft = inbufbytes;
    size_t outbufbytesleft = outbufbytes;

    iconv_t cd = iconv_open("UTF-8", "UCS-4LE");
    if(cd == (iconv_t) - 1) {
        fprintf(stderr, "iconv_open failed with %d\n", errno);
        return -1;
    }

    int rc = iconv(cd, &inbuftemp, &inbufbytesleft, &outbuftemp, &outbufbytesleft);
    if(rc == (size_t) - 1) {
        fprintf(stderr, "LINE %d: iconv failed with -1. errno is %d: %s\n", __LINE__, errno, strerror(errno));
        return -1;
    }

    rc = iconv_close(cd);
    if(rc != 0) {
        fprintf(stderr, "iconv_close failed with %d\n", errno);
        return -1;
    }
    return 0;
}

int lua_hangul_ic_process(lua_State* L) {
    // lhic ascii
    if(lua_gettop(L) != 2)
        luaL_error(L, "Expected 2 parameters");
    lua_getfield(L, -2, "c_object"); // lhic ascii hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic ascii
    int ascii = lua_tointeger(L, -1);
    lua_pushboolean(L, hangul_ic_process(hic, ascii)); // lhic ascii result
    return 1;
}

int lua_hangul_ic_get_preedit_string(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Expected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    ucschar* preedit_string = hangul_ic_get_preedit_string(hic);
    char result[4];
    ucs4_to_utf8(preedit_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // lhic result
    return 1;
}

int lua_hangul_ic_get_commit_string(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    ucschar* commit_string = hangul_ic_get_commit_string(hic);
    char result[4];
    ucs4_to_utf8(commit_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // lhic result
    return 1;
}

int lua_hangul_ic_reset(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    hangul_ic_reset(hic); // lhic
    return 0;
}

int lua_hangul_ic_flush(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    ucschar* flush_string = hangul_ic_flush(hic);
    char result[4];
    ucs4_to_utf8(flush_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // lhic result
    return 1;
}

int lua_hangul_ic_backspace(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    lua_pushboolean(L, hangul_ic_backspace(hic)); // lhic result
    return 1;
}

int lua_hangul_ic_is_empty(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    lua_pushboolean(L, hangul_ic_is_empty(hic)); // lhic result
    return 1;
}

int lua_hangul_ic_has_choseong(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    lua_pushboolean(L, hangul_ic_has_choseong(hic)); // lhic result
    return 1;
}

int lua_hangul_ic_has_jungseong(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic 
    lua_pushboolean(L, hangul_ic_has_jungseong(hic)); // lhic result
    return 1;
}

int lua_hangul_ic_has_jongseong(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    lua_pushboolean(L, hangul_ic_has_jongseong(hic)); // lhic result
    return 1;
}
/*
int lua_hangul_ic_get_option(lua_State* L) {
    // * hangul_ic option
    lua_tointeger(L, -2); // 
    HangulInputContext* hic = lua_touserdata(L, -2);
    int option = lua_tointeger(L, -1);
    lua_pushboolean(L, hangul_ic_get_option(L, hic, option));
    return 1;
}

int lua_hangul_ic_set_option(lua_State* L) {
    // * hangul_ic option value
    HangulInputContext* hic = lua_touserdata(L, -3);
    int option = lua_tointeger(L, -2);
    bool value = lua_toboolean(L, -1);
    hangul_ic_set_option(hic, option, value);
    return 0;
}
*/
int lua_hangul_ic_select_keyboard(lua_State* L) {
    // lhic id
    if(lua_gettop(L) != 2)
        luaL_error(L, "Expect 2 parameters");
    lua_getfield(L, -2, "c_object"); // lhic id hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic id
    const char* id = lua_tostring(L, -1);
    hangul_ic_select_keyboard(hic, id);
    return 0;
}

int lua_hangul_ic_is_transliteration(lua_State* L) {
    // lhic
    if(lua_gettop(L) != 1)
        luaL_error(L, "Exepected 1 parameter");
    lua_getfield(L, -1, "c_object"); // lhic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // lhic
    lua_pushboolean(L, hangul_ic_is_transliteration(hic)); // lhic result
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
//    {"get_option", lua_hangul_ic_get_option},
//    {"set_option", lua_hangul_ic_set_option},
    {"select_keyboard", lua_hangul_ic_select_keyboard},
    {"is_transliteration", lua_hangul_ic_is_transliteration},
    {NULL, NULL}
};

int lua_hangul_ic_new(lua_State* L) {
    // (keyboard)
    lua_newtable(L); // (keyboard) lhic
    HangulInputContext* hic;
    if(lua_gettop(L) == 2) // keyboard lhic
        hic = hangul_ic_new(lua_tostring(L, -1));
    else
        hic = hangul_ic_new("2");
    lua_pushlightuserdata(L, hic); // (keyboard) lhic hic
    lua_setfield(L, -2, "c_object"); // (keyboard) lhic
    luaL_setfuncs(L, lua_hangul_ic_methods, 0); // (keyboard) lhic
    return 1;
}

static const struct luaL_Reg lua_hangul_functions[] = {
    {"ic_new", lua_hangul_ic_new},
    {NULL, NULL}
};

int luaopen_hangul(lua_State* L) {
    luaL_newmetatable(L, "lua_hangul_ic"); // lua_hangul_ic
    lua_pushvalue(L, -1); // lua_hangul_ic lua_hangul_ic
    lua_setfield(L, -2, "__index"); // lua_hangul_ic
    luaL_setfuncs(L, lua_hangul_ic_methods, 0); // lua_hangul_ic
    lua_pop(L, 1); //
    luaL_newlib(L, lua_hangul_functions); // library
    return 1;
}

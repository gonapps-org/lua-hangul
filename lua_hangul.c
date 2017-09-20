#include <lua.h>
#include <lauxlib.h>
#include <hangul-1.0/hangul.h>
#include <iconv.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include <err.h>

void utf8_to_ucs4(char* inbuf, size_t inbufbytes, ucschar* outbuf, size_t outbufbytes) {
    char* inbuftemp = inbuf;                                                                                                                                 
    char* outbuftemp = (char*)outbuf;                                                                                                                        
    size_t inbufbytesleft = inbufbytes;                                                                                                                      
    size_t outbufbytesleft = outbufbytes;                                                                                                                    

    iconv_t cd = iconv_open("UCS-4LE", "UTF-8");                                                                                                             
    if (cd == (iconv_t) - 1) fprintf(stderr, "iconv_open failed with %d\n", errno);                                                                          

    int rc = iconv(cd, &inbuftemp, &inbufbytesleft, &outbuftemp, &outbufbytesleft);                                                                          
    if (rc == -1) fprintf(stderr, "LINE %d: iconv failed with -1. errno is %d: %s\n", __LINE__, errno, strerror(errno));                                     

    rc = iconv_close(cd);                                                                                                                                    
    if (rc != 0) fprintf(stderr, "iconv_close failed with %d\n", errno);                                                                                     
}

void ucs4_to_utf8(ucschar* inbuf, size_t inbufbytes, char* outbuf, size_t outbufbytes) {
    char* inbuftemp = (char*)inbuf;                                                                                                                          
    char* outbuftemp = outbuf;                                                                                                                               
    size_t inbufbytesleft = inbufbytes;                                                                                                                      
    size_t outbufbytesleft = outbufbytes;                                                                                                                    

    iconv_t cd = iconv_open("UTF-8", "UCS-4LE");                                                                                                             
    if (cd == (iconv_t) - 1) fprintf(stderr, "iconv_open failed with %d\n", errno);                                                                          

    int rc = iconv(cd, &inbuftemp, &inbufbytesleft, &outbuftemp, &outbufbytesleft);                                                                          
    if (rc == (size_t) - 1) fprintf(stderr, "LINE %d: iconv failed with -1. errno is %d: %s\n", __LINE__, errno, strerror(errno));                           

    rc = iconv_close(cd);                                                                                                                                    
    if (rc != 0) fprintf(stderr, "iconv_close failed with %d\n", errno);
}

int lua_hangul_ic_process(lua_State* L) {
    // * hangul_ic ascii
    lua_getfield(L, -2, "hic"); // * hangul_ic ascii hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic ascii
    int ascii = lua_tointeger(L, -1);
    lua_pushboolean(L, hangul_ic_process(hic, ascii)); // * hangul_ic ascii result
    return 1;
}

int lua_hangul_ic_get_preedit_string(lua_State* L) {
    // * hangul_ic 
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    ucschar* preedit_string = hangul_ic_get_preedit_string(hic);
    char result[4];
    ucs4_to_utf8(preedit_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_get_commit_string(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    ucschar* commit_string = hangul_ic_get_commit_string(hic);
    char result[4];
    ucs4_to_utf8(commit_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_reset(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    hangul_ic_reset(hic); // * hangul_ic
    return 0;
}

int lua_hangul_ic_flush(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    ucschar* flush_string = hangul_ic_flush(hic);
    char result[4];
    ucs4_to_utf8(flush_string, sizeof(ucschar), result, sizeof(ucschar));
    lua_pushstring(L, result); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_backspace(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_backspace(hic)); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_is_empty(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_is_empty(hic)); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_has_choseong(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_has_choseong(hic)); // * hangul_ic result
    return 1;
}

int lua_hangul_ic_has_jungseong(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_has_jungseong(hic));
    return 1;
}

int lua_hangul_ic_has_jongseong(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_has_jongseong(hic));
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
    // * hangul_ic id
    lua_getfield(L, -2, "hic"); // * hangul_ic id hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic id
    const char* id = lua_tostring(L, -1);
    hangul_ic_select_keyboard(hic, id);
    return 0;
}

int lua_hangul_ic_is_transliteration(lua_State* L) {
    // * hangul_ic
    lua_getfield(L, -1, "hic"); // * hangul_ic hic
    HangulInputContext* hic = lua_touserdata(L, -1);
    lua_pop(L, 1); // * hangul_ic
    lua_pushboolean(L, hangul_ic_is_transliteration(hic)); // * hagul_ic result
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
    lua_newtable(L); // hangul_ic
    HangulInputContext* hic = hangul_ic_new("2");
    lua_pushlightuserdata(L, hic); // hangul_ic hic
    lua_setfield(L, -2, "hic"); // hangul_ic
    luaL_setfuncs(L, lua_hangul_ic_methods, 0); // hangul_ic
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

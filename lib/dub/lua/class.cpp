/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class {{class.name}}
 *
 * This file has been generated by dub {{dub.VERSION}}.
 */
#include "dub/dub.h"
#include "{{self:header(class.header)}}"

{% if class:namespace() then %}
using namespace {{class:namespace().name}};
{% end %}

{% for method in class:methods() do %}
/** {{method:fullname()}}
 * {{method.location}}
 */
static int {{class.name}}_{{method.cname}}(lua_State *L) {
{% if method:neverThrows() then %}

  {| self:functionBody(class, method) |}
{% else %}
  try {
    {| self:functionBody(class, method) |}
  } catch (std::exception &e) {
    lua_pushfstring(L, "{{self:libName(method)}}: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "{{self:libName(method)}}: Unknown exception");
  }
  return lua_error(L);
{% end %}
}

{% end %}

{% if not class:method('__tostring') then %}

// --=============================================== __tostring
static int {{class.name}}___tostring(lua_State *L) {
{% if class.dub.destroy == 'free' then %}
  {{class.name}} **userdata = (({{class.name}}**)dub_checksdata_n(L, 1, "{{self:libName(class)}}"));
  lua_pushfstring(L, "{{self:libName(class)}}: %p (full)", *userdata);
{% else %}
  DubUserdata *userdata = ((DubUserdata*)dub_checksdata_n(L, 1, "{{self:libName(class)}}"));
  lua_pushfstring(L, "{{self:libName(class)}}: %p", userdata->ptr);
{% end %}
  return 1;
}
{% end %}

// --=============================================== METHODS

static const struct luaL_Reg {{class.name}}_member_methods[] = {
{% for method in class:methods() do %}
  { {{string.format('%-15s, %-20s', '"'..self:bindName(method)..'"', class.name .. '_' .. method.cname)}} },
{% end %}
{% if not class:method('__tostring') then %}
  { {{string.format('%-15s, %-20s', '"__tostring"', class.name .. '___tostring')}} },
{% end %}
  { NULL, NULL},
};

{% if class.has_constants then %}
// --=============================================== CONSTANTS
static const struct dub_const_Reg {{class.name}}_const[] = {
{% for const in class:constants() do %}
  { {{string.format('%-15s, %-20s', '"'.. const ..'"', class.name..'::'..const)}} },
{% end %}
  { NULL, NULL},
};
{% end %}

extern "C" int luaopen_{{self:openName(class)}}(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "{{self:libName(class)}}");
  // <mt>
{% if class.has_constants then %}
  // register class constants
  dub_register_const(L, {{class.name}}_const);
{% end %}

  // register member methods
  luaL_register(L, NULL, {{ class.name }}_member_methods);
  // save meta-table in {{self:libName(class.parent)}}
  dub_register(L, "{{self:libName(class.parent)}}", "{{self:name(class)}}");

  return 1;
}

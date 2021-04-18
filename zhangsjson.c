#include "zhangsjson.h"

#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

// 跳过空白必然成功,不需要返回值
//  ws = *(%x20 / %x09 / %x0A / %x0D)
static void zhangs_parse_whitespace(zhangs_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        ++p;
    c->json = p;
}

// null == "null"
static int zhangs_parse_null(zhangs_context *c, zhangs_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return ZHANGS_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = ZHANGS_NULL;
    return ZHANGS_PARSE_OK;
}

// t ➔ true
static int zhangs_parse_true(zhangs_context *c, zhangs_value *v)
{
    return ZHANGS_PARSE_OK;
}

// f ➔ false
static int zhangs_parse_false(zhangs_context *c, zhangs_value *v)
{
    return ZHANGS_PARSE_OK;
}

// n ➔ null
// t ➔ true
// f ➔ false
// " ➔ string
// 0-9/- ➔ number
// [ ➔ array
// { ➔ object
static int zhangs_parse_value(zhangs_context *c, zhangs_value *v)
{
    switch (*(c->json)) {
    case 'n': return zhangs_parse_null(c, v);
    case '\0': return ZHANGS_PARSE_EXPECT_VALUE;
    default: return ZHANGS_PARSE_INVALID_VALUE;
    }
}

// JSON-text = ws value ws
// ws = *(%x20 / %x09 / %x0A / %x0D)
// value = null / false / true
// null  = "null"
// false = "false"
// true  = "true"
int zhangs_parse(const char *json, zhangs_value *v)
{
    // 如果那个错误是由于程序员错误编码所造成的（例如传入不合法的参数），那么应用断言；
    // 如果那个错误是程序员无法避免，而是由运行时的环境所造成的，就要处理运行时错误（例如开启文件失败）
    assert(v != NULL);
    zhangs_context c;
    c.json = json;
    v->type = ZHANGS_NULL;
    zhangs_parse_whitespace(&c);
    int ret = zhangs_parse_value(&c, v);
    if (ret == ZHANGS_PARSE_OK) {
        zhangs_parse_whitespace(&c);
        if (c.json[0] != '\0')
            ret = ZHANGS_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

zhangs_type zhangs_get_type(const zhangs_value *v)
{
    return v->type;
}

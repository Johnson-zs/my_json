#include "zhangsjson.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do { \
        test_count++; \
        if (equality) { \
            test_pass++; \
        } else { \
            main_ret = 1; \
            fprintf(stderr, "%s:%d: expect: "format", actual: "format"\n", __FILE__, __LINE__, expect, actual); \
        } \
    } while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual, "%d")

static void test_parse_null()
{
    zhangs_value v;
    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_OK, zhangs_parse("null", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, zhangs_get_type(&v));

    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_OK, zhangs_parse("    null   ", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, zhangs_get_type(&v));
}

static void test_parse_true()
{
    zhangs_value v;
    v.type = ZHANGS_FALSE;

    EXPECT_EQ_INT(ZHANGS_PARSE_OK, zhangs_parse("true", &v));
    EXPECT_EQ_INT(ZHANGS_TRUE, v.type);
}

static void test_parse_false()
{
    zhangs_value v;
    v.type = ZHANGS_TRUE;

    EXPECT_EQ_INT(ZHANGS_PARSE_OK, zhangs_parse("false", &v));
    EXPECT_EQ_INT(ZHANGS_FALSE, v.type);
}

static void test_parse_expect_value()
{
    zhangs_value v;
    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_EXPECT_VALUE, zhangs_parse("", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, v.type);

    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_EXPECT_VALUE, zhangs_parse(" ", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, v.type);
}

static void test_parse_invalid_value()
{
    zhangs_value v;
    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_INVALID_VALUE, zhangs_parse("t", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, v.type);

    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_INVALID_VALUE, zhangs_parse("nul", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, v.type);
}

static void test_parse_root_not_singular()
{
    zhangs_value v;
    v.type = ZHANGS_FALSE;
    EXPECT_EQ_INT(ZHANGS_PARSE_ROOT_NOT_SINGULAR, zhangs_parse("null t", &v));
    EXPECT_EQ_INT(ZHANGS_NULL, v.type);
}

static void test_parse()
{
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
    test_parse_null();
    test_parse_true();
    test_parse_false();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

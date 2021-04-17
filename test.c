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
}

static void test_parse()
{
    test_parse_null();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

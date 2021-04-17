#ifndef ZHANGSJSON_H_
#define ZHANGSJSON_H_

// json 值的类型
typedef enum {
    ZHANGS_NULL,
    ZHANGS_FALSE,
    ZHANGS_TRUE,
    ZHANGS_NUMBER,
    ZHANGS_STRING,
    ZHANGS_ARRAY,
    ZHANGS_OBJECT
} zhangs_type;

// json value
typedef struct {
   zhangs_type type;
} zhangs_value;

// error code
enum {
    ZHANGS_PARSE_OK = 0,
    ZHANGS_PARSE_EXPECT_VALUE,
    ZHANGS_PARSE_INVALID_VALUE,
    ZHANGS_PARSE_ROOT_NOT_SINGULAR
};

// 减少解析函数之间传递多个参数
typedef struct {
    const char *json;
} zhangs_context;

int zhangs_parse(const char *json, zhangs_value *v);
zhangs_type zhangs_get_type(const zhangs_value *v);

#endif /* ZHANGSJSON_H_ */

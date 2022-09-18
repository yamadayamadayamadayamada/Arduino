
#define LED_ERROR 13


/* 赤色LEDを点灯させて関数から抜ける */
#define ERROR() \
do{ \
    AlartError();\
    return;\
}while (0)


void AlartError(void);

#define LED_ERROR 13


/* 赤色LEDを点灯させて関数から抜ける */
#define ERROR() \
do{ \
    AlertError();\
    return;\
}while (0)

void AlertInit(void);
void AlertError(void);
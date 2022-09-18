#ifndef ALERT_H_
#define ALERT_H_

#define LED_ERROR 13

/* 赤色LEDを点灯させて関数から抜ける */
#define ERROR(mess)       \
    do                    \
    {                     \
        AlertError(mess); \
        return;           \
    } while (0)

#define CHECK_NOT_EQ(val1, val2, mess) \
    do                                 \
    {                                  \
        if ((val1) == (val2))          \
        {                              \
            AlertError(mess);          \
            return;                    \
        }                              \
    } while (0)

void AlertInit(void);
void AlertError(const char *mess);

#endif

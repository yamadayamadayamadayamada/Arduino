#include <Arduino.h>

#include "CommonDef.h"
#include "Serial.h"
#include "Task.h"
#include "FullColorLed.h"

#define LINE_SIZE 256
#define ARGC_SIZE 8
#define ARGV_SIZE 64

#define IS_EOF(Character) ((Character) == '\r' || (Character) == '\n' || (Character) == '\0')
#define IS_SPACE(Character) ((Character) == ' ')

static char gs_Line[LINE_SIZE];
static const char *gs_p_LineEndAdd = &gs_Line[LINE_SIZE - 1];
static char *gs_p_LineRead;

static char *gs_Argv[ARGC_SIZE];

static UInt32 get_argc(char *Line, char **pp_argv);

typedef struct tagCmd
{
    const char *cmd;
    void (*func)(int argc, char **argv);
} SCmd;

static const SCmd CMD_TBL[] =
    {
        {"led", CmdFullColorLed},
};

void SerialInit(void)
{
    Serial.begin(115200);
    Serial.print("Hello Arduino!\n");

    gs_p_LineRead = &gs_Line[0];
}

void SerialRead(void)
{
    if (Serial.available() <= 0)
    {
        return;
    }

    CHECK_NOT_EQ(gs_p_LineRead, gs_p_LineEndAdd, "[error]line read buffer over");

    *gs_p_LineRead = Serial.read(); // 1バイト分のデータを読み取る
    if (IS_EOF(*gs_p_LineRead))
    {
        *gs_p_LineRead++;
        *gs_p_LineRead = '\0';

        KIC_TASK(ID_COMMAND);
        return;
    }
    *gs_p_LineRead++;
}

void TaskCmd(UInt32 FrameIndex)
{
    UInt32 i;
    UInt32 Argc;

    /* echo */
    Serial.println(gs_Line);

    Argc = get_argc(gs_Line, gs_Argv);
    
    if(Argc == 0) goto TASKCMD_END;

    for (i = 0; i < sizeof(CMD_TBL) / sizeof(SCmd); i++)
    {
        if (!strcmp(CMD_TBL[i].cmd, gs_Argv[0]))
        {
            CMD_TBL[i].func(Argc, gs_Argv);
            goto TASKCMD_END;
        }
    }


      Serial.println("unknown command");


    /* TaskCmd end */
TASKCMD_END:
    gs_p_LineRead = &gs_Line[0];
    Serial.print(">");
}

static UInt32 get_argc(char *Line, char **pp_Argv)
{
    UInt32 i;
    UInt32 Argc = 0;

    if (!IS_SPACE(Line[i]) && !IS_EOF(Line[i]))
    {
        pp_Argv[Argc] = &Line[0];
        Argc++;
    }

    for (i = 1; i < LINE_SIZE; i++)
    {
        if (IS_EOF(Line[i]))
        {
            Line[i] = '\0';
            return Argc;
        }

        if (IS_SPACE(Line[i]))
        {
            Line[i] = '\0';
            continue;
        }

        if (IS_EOF(Line[i - 1]))
        {
            pp_Argv[Argc] = &Line[i];
            Argc++;
        }
    }

    ERROR_RETURN("[error]Line without end", 0);
}

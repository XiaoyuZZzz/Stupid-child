#ifndef COMMAND_H__
#define COMMAND_H__

#include "sc_log.h"

typedef struct {
    const char* command_name;           /**命令名称*/
    void(*command_fn)(void);            /**命令对应的函数操作*/
} COMMAND_ENTRY;


#define REGISTER_COMMAND(cmd, cmd_fn) \
    __attribute__((used,section(".command_section"))) \
    static const COMMAND_ENTRY command_##cmd = { \
        .command_name = #cmd, \
        .command_fn = cmd_fn \
    }

#define REGISTER_COMMAND_FUNCTION(name) \
    void name(void)



void process_command(const char* input);

/******************************************command_name*************************************/
#define SC_VERSION 						"version"
#define SC_HELLO                        "hello"

#endif

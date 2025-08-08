/*
 * @file         : command.c
 * @Author       : shuyu
 * @LastEditTime : 2025-08-08 18:14
 * @Description  : 操作命令，需要添加新的指令在此添加声明
 */

#include "command.h"


/***************************command funciton***********************/
REGISTER_COMMAND_FUNCTION(version) {
    LOG(INFO,RED,"%s",get_sc_log_version());
}

REGISTER_COMMAND_FUNCTION(hello) {
    LOG(INFO,RED,"hello world");
}

/***************************command define***********************/
REGISTER_COMMAND(SC_VERSION,version);
REGISTER_COMMAND(SC_HELLO,hello);


extern uint32_t     command_section$$Base;
extern uint32_t     command_section$$Limit;

/**TOP_API*/
void process_command(const char* input) {
//	// 直接使用符号地址
//    const COMMAND_ENTRY* start = (const COMMAND_ENTRY*)&command_section$$Base;
//    const COMMAND_ENTRY* end = (const COMMAND_ENTRY*)&command_section$$Limit;
//    for (const COMMAND_ENTRY* cmd = start; cmd < end; cmd++){
//        // FIXME: @sy
//        if (strcmp(input, cmd->command_name) == 0) {
//            cmd->command_fn(); // 执行命令
//            return;
//        }
// 	   LOG(INFO,RED,"command_name:%s\r\n",cmd->command_name);
//        cmd++;
//    }
// 	return ;
}


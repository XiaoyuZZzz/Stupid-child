/*
 * @Author       : 824229900@qq.com
 * @Date         : 2025-07-31 21:52
 * @LastEditors  : SuperYu 824229900@qq.com
 * @LastEditTime : 2025-07-31 23:53
 * @Description  : 
 */

 #include "c_unit.h"
 
void* c_memcpy(void* dest, const void* src, size_t num) {
    char* dest_ptr = (char*)dest;       
    const char* src_ptr = (const char*)src; 
    void* ret = dest;                   
    
    while (num--) {
        *dest_ptr++ = *src_ptr++;      
    }
    
    return ret;
}


size_t c_strlen(char *arr)
{
	char* p1 = arr, * p2 = arr;
	while (*p2++ != '\0');
	return p2 - p1 - 1;
}

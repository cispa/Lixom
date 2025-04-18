#ifndef _MODXOM_H_
#define _MODXOM_H_

#ifndef __KERNEL__
#include <stdint.h>
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12
#endif
#ifndef MAX_ORDER
#define MAX_ORDER 11
#endif


#define MODXOM_CMD_NOP              0
#define MODXOM_CMD_FREE             1
#define MODXOM_CMD_LOCK             2
#define MODXOM_CMD_INIT_SUBPAGES    3
#define MODXOM_CMD_WRITE_SUBPAGES   4
#define MODXOM_CMD_GET_SECRET_PAGE  5
#define MODXOM_CMD_MARK_REG_CLEAR   6

#define REG_CLEAR_TYPE_NONE     0
#define REG_CLEAR_TYPE_VECTOR   1
#define REG_CLEAR_TYPE_FULL     2

#ifndef SUBPAGE_SIZE
#define SUBPAGE_SIZE (PAGE_SIZE / (sizeof(uint32_t) << 3))
#endif

#define MAX_SUBPAGES_PER_CMD ((PAGE_SIZE - sizeof(uint8_t)) / (sizeof(xom_subpage_write_info)))

#define MODXOM_PROC_FILE_NAME   "xom"
#define XOM_FILE                ("/proc/" MODXOM_PROC_FILE_NAME)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t cmd;
    uint32_t num_pages;
    uint64_t base_addr;
} modxom_cmd, *pmodxom_cmd;

typedef struct {
    uint8_t target_subpage;
    uint8_t data[SUBPAGE_SIZE];
} xom_subpage_write_info;

typedef struct {
    uint8_t num_subpages;
    xom_subpage_write_info write_info [MAX_SUBPAGES_PER_CMD];
} xom_subpage_write_command;

typedef struct {
    modxom_cmd mxom_cmd;
    xom_subpage_write_command xen_cmd;
} xom_subpage_write;


#ifdef __cplusplus
}
#endif

#endif
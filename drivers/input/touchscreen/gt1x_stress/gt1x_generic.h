/* drivers/input/touchscreen/gt1x_generic.h
 *
 * 2010 - 2014 Goodix Technology.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be a reference
 * to you, when you are integrating the GOODiX's CTP IC into your system,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * Version: 1.0   
 * Revision Record: 
 *      V1.0:  first release. 2014/09/28.
 *
 */

#ifndef _GT1X_GENERIC_H_
#define _GT1X_GENERIC_H_

#include <linux/hrtimer.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
//#include <linux/io.h>

#include <linux/jiffies.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/byteorder/generic.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#include <linux/interrupt.h>
#include <linux/time.h>

#include <linux/proc_fs.h>
#include <asm/uaccess.h>

/***************************PART1:ON/OFF define*******************************/

#define GTP_DRIVER_SEND_CFG   1	// send config to TP while initializing (for no config built in TP's flash)
#define GTP_CUSTOM_CFG        0	// customize resolution & interrupt trigger mode

#define GTP_CHANGE_X2Y        0	// exchange xy
#define GTP_WARP_X_ON         0
#define GTP_WARP_Y_ON         0

#define GTP_GESTURE_WAKEUP    0	// gesture wakeup module
#define KEY_GESTURE           KEY_F24	// customize gesture-key

#define GTP_HOTKNOT           0	// hotknot module
#define HOTKNOT_TYPE          0	// 0: hotknot in flash; 1: hotknot in driver
#define HOTKNOT_BLOCK_RW      0

#define GTP_PROXIMITY         0	// proximity module (function as the p-sensor),only supports MTK platform

#define GTP_HAVE_TOUCH_KEY    0
#define GTP_WITH_STYLUS       0
#define GTP_HAVE_STYLUS_KEY   0

#define GTP_AUTO_UPDATE       1	// auto update FW to TP FLASH while initializing
#define GTP_HEADER_FW_UPDATE  1	// firmware in gt1x_firmware.h

#define GTP_POWER_CTRL_SLEEP  0	// turn off power on suspend
#define GTP_ICS_SLOT_REPORT   1
#define GTP_CREATE_WR_NODE    1	// create the interface to support gtp_tools

#define GTP_ESD_PROTECT       0	// esd-protection module (with a cycle of 2 seconds)
#define GTP_CHARGER_SWITCH    1	// charger plugin & plugout detect

#define GTP_DEBUG_ON          0	// enable log printed by GTP_DEBUG(...)
#define GTP_DEBUG_ARRAY_ON    0
#define GTP_DEBUG_FUNC_ON     0

#define CFG_GROUP_LEN(p_cfg_grp)  (sizeof(p_cfg_grp) / sizeof(p_cfg_grp[0]))

/***************************PART2:TODO define**********************************/
/*TODO: puts the config info corresponded to your TP here, the following is just
          a sample config, send this config should cause the chip cannot work normally*/

/* TODO define your config for Sensor_ID == 0 here, if needed */
//goworld
#define GTP_CFG_GROUP0 {\
0x48,0x38,0x04,0x80,0x07,0x0A,0x3D,0x10,0x00,0x40,0x20,0x08,0x50,\
0x3C,0x53,0x01,0x00,0x00,0x00,0x00,0x3C,0x85,0x90,0xD5,0x08,0x04,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x28,0x1D,0x46,0x48,0xEB,\
0x06,0x38,0x6D,0x38,0x0D,0x43,0x24,0x00,0x05,0x2D,0x70,0x80,0x94,\
0x02,0x00,0x0D,0x03,0xD0,0x38,0xAC,0x43,0x93,0x4E,0x80,0x59,0x72,\
0x64,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x23,0x23,0x81,0x00,0x0F,0x0F,0x04,0x0E,0x88,0x88,0x88,\
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x04,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0xD0,0x07,0x3C,0x32,0x0E,0x0F,0x0A,\
0x08,0x06,0x04,0x05,0x02,0x03,0x07,0x09,0x0B,0x0C,0x0D,0x10,0x13,\
0x12,0x15,0x14,0x17,0x16,0x19,0x18,0x1B,0x1A,0x1C,0x1D,0x1E,0x1F,\
0xFF,0xFF,0x00,0x10,0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,\
0x06,0x05,0x04,0x03,0x02,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x11,0xC8,\
0x00,0x13,0x32,0x6D,0x01,0x19,0x28,0x00,0x5A,0xA0,0x00,0x00,0xD0,\
0x07,0x32,0x7E,0xC8,0x01\
}

/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CFG_GROUP0_CHARGER {\
}

/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CFG_GROUP0_GLOVED {\
0x45,0x38,0x04,0x80,0x07,0x0A,0x3D,0x10,0x00,0x40,0x00,0x08,0x50,\
0x3C,0x53,0x01,0x00,0x00,0x00,0x00,0x3C,0x85,0x90,0xD5,0x08,0x04,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x28,0x1D,0x88,0x8A,0xF6,\
0x05,0x38,0x6D,0x38,0x0D,0x44,0x24,0x00,0x06,0x41,0xC4,0x80,0x94,\
0x02,0x00,0x0E,0x02,0xD2,0x49,0xA7,0x60,0x8D,0x71,0x80,0x8D,0x71,\
0xB0,0x6E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x23,0x23,0x81,0x00,0x0F,0x0F,0x04,0x0E,0x88,0x88,0x88,\
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x04,0x03,0x14,\
0x0A,0x02,0x14,0x78,0xB4,0xB4,0x58,0x82,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0xD0,0x07,0x3C,0x32,0x0E,0x0F,0x0A,\
0x08,0x06,0x04,0x05,0x02,0x03,0x07,0x09,0x0B,0x0C,0x0D,0x10,0x13,\
0x12,0x15,0x14,0x17,0x16,0x19,0x18,0x1B,0x1A,0x1C,0x1D,0x1E,0x1F,\
0xFF,0xFF,0x00,0x10,0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,\
0x06,0x05,0x04,0x03,0x02,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x13,0x32,0x6D,0x01,0x19,0x28,0x00,0x5A,0xA0,0x01,0x00,0xD0,\
0x07,0x50,0x43,0x50,0x01\
}

/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CFG_GROUP1 {\
    }

/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CFG_GROUP1_CHARGER {\
}

#define GTP_CFG_GROUP1_GLOVED {\
}

/* TODO define your config for Sensor_ID == 2 here, if needed */
//truly
#define GTP_CFG_GROUP2 {\
}

/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CFG_GROUP2_CHARGER {\
    }

/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CFG_GROUP2_GLOVED {\
}

/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CFG_GROUP3 {\
    }

/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CFG_GROUP3_CHARGER {\
    }

#define GTP_CFG_GROUP3_GLOVED {\
}

/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CFG_GROUP4 {\
    }

/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CFG_GROUP4_CHARGER {\
    }

#define GTP_CFG_GROUP4_GLOVED {\
}

/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CFG_GROUP5 {\
    }

/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CFG_GROUP5_CHARGER {\
    }

#define GTP_CFG_GROUP5_GLOVED {\
}

#if GTP_CUSTOM_CFG
#define GTP_MAX_HEIGHT   4096
#define GTP_MAX_WIDTH    4096
#define GTP_INT_TRIGGER  1	//0:Rising 1:Falling
#define GTP_WAKEUP_LEVEL 1
#else
#define GTP_MAX_HEIGHT   4096
#define GTP_MAX_WIDTH    4096
#define GTP_INT_TRIGGER  1
#define GTP_WAKEUP_LEVEL 1
#endif

#define GTP_MAX_TOUCH    10

#if GTP_WITH_STYLUS
#define GTP_STYLUS_KEY_TAB {BTN_STYLUS, BTN_STYLUS2}
#endif

#if GTP_HAVE_TOUCH_KEY
#define GTP_KEY_TAB	 {KEY_BACK, KEY_HOMEPAGE, KEY_MENU, KEY_SEARCH}
#define GTP_MAX_KEY_NUM  4
#endif

/****************************PART3:OTHER define*********************************/
#define GTP_DRIVER_VERSION          "V1.0<2014/09/28>"
#define GTP_I2C_NAME                "Goodix-TS"
#define GT1X_DEBUG_PROC_FILE        "gt1x_debug"
#define GTP_POLL_TIME               10
#define GTP_ADDR_LENGTH             2
#define GTP_CONFIG_MIN_LENGTH       186
#define GTP_CONFIG_MAX_LENGTH       240
#define GTP_MAX_I2C_XFER_LEN        250
#define SWITCH_OFF                  0
#define SWITCH_ON                   1

#define GTP_REG_MATRIX_DRVNUM           0x8069
#define GTP_REG_MATRIX_SENNUM           0x806A
#define GTP_REG_RQST                    0x8044
#define GTP_REG_BAK_REF                 0x90EC
#define GTP_REG_MAIN_CLK                0x8020
#define GTP_REG_HAVE_KEY                0x8057
#define GTP_REG_HN_STATE                0x8800

#define GTP_REG_WAKEUP_GESTURE         0x814C
#define GTP_REG_WAKEUP_GESTURE_DETAIL  0xA2A0	// need change

#define GTP_BAK_REF_PATH                "/data/gt1x_ref.bin"
#define GTP_MAIN_CLK_PATH               "/data/gt1x_clk.bin"

/* request type */
#define GTP_RQST_CONFIG                 0x01
#define GTP_RQST_BAK_REF                0x02
#define GTP_RQST_RESET                  0x03
#define GTP_RQST_MAIN_CLOCK             0x04
#define GTP_RQST_HOTKNOT_CODE           0x20
#define GTP_RQST_RESPONDED              0x00
#define GTP_RQST_IDLE                   0xFF

#define HN_DEVICE_PAIRED                0x80
#define HN_MASTER_DEPARTED              0x40
#define HN_SLAVE_DEPARTED               0x20
#define HN_MASTER_SEND                  0x10
#define HN_SLAVE_RECEIVED               0x08

/*Register define */
#define GTP_READ_COOR_ADDR          0x814E
#define GTP_REG_CMD                 0x8040
#define GTP_REG_SENSOR_ID           0x814A
#define GTP_REG_CONFIG_DATA         0x8050
#define GTP_REG_CONFIG_RESOLUTION   0x8051
#define GTP_REG_CONFIG_TRIGGER      0x8056
#define GTP_REG_CONFIG_CHECKSUM     0x813C
#define GTP_REG_CONFIG_UPDATE       0x813E
#define GTP_REG_VERSION             0x8140
#define GTP_REG_HW_INFO             0x4220
#define GTP_REG_REFRESH_RATE	    0x8056
#define GTP_REG_ESD_CHECK           0x8043
#define GTP_REG_FLASH_PASSBY        0x8006
#define GTP_REG_HN_PAIRED           0x81AA
#define GTP_REG_HN_MODE             0x81A8
#define GTP_REG_MODULE_SWITCH3      0x8058

#define set_reg_bit(reg,index,val)	((reg)^=(!(val)<<(index)))

/* cmd define */
#define GTP_CMD_SLEEP               0x05
#define GTP_CMD_CHARGER_ON          0x06
#define GTP_CMD_CHARGER_OFF         0x07
#define GTP_CMD_GESTURE_WAKEUP      0x08
#define GTP_CMD_CLEAR_CFG           0x10
#define GTP_CMD_ESD                 0xAA
#define GTP_CMD_HN_TRANSFER         0x22
#define GTP_CMD_HN_EXIT_SLAVE       0x28

/* define offset in the config*/
#define RESOLUTION_LOC              (GTP_REG_CONFIG_RESOLUTION - GTP_REG_CONFIG_DATA)
#define TRIGGER_LOC                 (GTP_REG_CONFIG_TRIGGER - GTP_REG_CONFIG_DATA)
#define MODULE_SWITCH3_LOC	     	(GTP_REG_MODULE_SWITCH3 - GTP_REG_CONFIG_DATA)

#define GTP_I2C_ADDRESS       		0xBA

#if GTP_WARP_X_ON
#define GTP_WARP_X(x_max, x) ( x_max - 1 - x )
#else
#define GTP_WARP_X(x_max, x) x
#endif

#if GTP_WARP_Y_ON
#define GTP_WARP_Y(y_max, y) ( y_max - 1 - y )
#else
#define GTP_WARP_Y(y_max, y) y
#endif

#define IS_NUM_OR_CHAR(x)    (((x) > 'A' && (x) < 'Z') || ((x) > '0' && (x) < '9'))

//Log define
#define GTP_INFO(fmt,arg...)           printk("<<GTP-INF>>[%s:%d] "fmt"\n", __func__, __LINE__, ##arg)
#define GTP_ERROR(fmt,arg...)          printk("<<GTP-ERR>>[%s:%d] "fmt"\n", __func__, __LINE__, ##arg)
#define GTP_DEBUG(fmt,arg...)          do{\
                                         if(GTP_DEBUG_ON)\
                                         printk("<<GTP-DBG>>[%s:%d]"fmt"\n",__func__, __LINE__, ##arg);\
                                       }while(0)
#define GTP_DEBUG_ARRAY(array, num)    do{\
                                         s32 i;\
                                         u8* a = array;\
                                         if(GTP_DEBUG_ARRAY_ON)\
                                         {\
                                            printk("<<GTP-DBG>>");\
                                            for (i = 0; i < (num); i++)\
                                            {\
                                                printk("%02x ", (a)[i]);\
                                                if ((i + 1 ) %10 == 0)\
                                                {\
                                                    printk("\n<<GTP-DBG>>");\
                                                }\
                                            }\
                                            printk("\n");\
                                        }\
                                       }while(0)
#define GTP_DEBUG_FUNC()               do{\
                                         if(GTP_DEBUG_FUNC_ON)\
                                         printk("<<GTP-FUNC>> Func:%s@Line:%d\n",__func__,__LINE__);\
                                       }while(0)

#define GTP_SWAP(x, y)                 do{\
                                         typeof(x) z = x;\
                                         x = y;\
                                         y = z;\
                                       }while (0)

#pragma pack(1)
struct gt1x_version_info {
	u8 product_id[5];
	u32 patch_id;
	u32 mask_id;
	u8 sensor_id;
	u8 match_opt;
};
#pragma pack()

typedef enum {
	DOZE_DISABLED = 0,
	DOZE_ENABLED = 1,
	DOZE_WAKEUP = 2,
} DOZE_T;

typedef enum {
	CHIP_TYPE_GT1X = 0,
	CHIP_TYPE_GT2X = 1,
	CHIP_TYPE_NONE = 0xFF
} CHIP_TYPE_T;

#define _ERROR(e)      ((0x01 << e) | (0x01 << (sizeof(s32) * 8 - 1)))
#define ERROR          _ERROR(1)	//for common use
//system relevant
#define ERROR_IIC      _ERROR(2)	//IIC communication error.
#define ERROR_MEM      _ERROR(3)	//memory error.

//system irrelevant
#define ERROR_HN_VER   _ERROR(10)	//HotKnot version error.
#define ERROR_CHECK    _ERROR(11)	//Compare src and dst error.
#define ERROR_RETRY    _ERROR(12)	//Too many retries.
#define ERROR_PATH     _ERROR(13)	//Mount path error
#define ERROR_FW       _ERROR(14)
#define ERROR_FILE     _ERROR(15)
#define ERROR_VALUE    _ERROR(16)	//Illegal value of variables

/* bit operation */
#define SET_BIT(data, flag)	((data) |= (flag))
#define CLR_BIT(data, flag)	((data) &= ~(flag))
#define CHK_BIT(data, flag)	((data) & (flag))

/* touch states */
#define BIT_TOUCH			0x01
#define BIT_TOUCH_KEY		0x02
#define BIT_STYLUS			0x04
#define BIT_STYLUS_KEY		0x08
#define BIT_HOVER			0x10

#include <linux/input.h>
struct i2c_msg;

/*          Export global variables and functions          */

/* Export from gt1x_extents.c and gt1x_firmware.h */
#if GTP_HOTKNOT
extern u8 hotknot_enabled;
extern u8 hotknot_transfer_mode;
extern u8 gt1x_patch_jump_fw[];
extern u8 hotknot_auth_fw[];
extern u8 hotknot_transfer_fw[];
#if HOTKNOT_BLOCK_RW
extern s32 hotknot_paired_flag;
extern s32 hotknot_event_handler(u8 * data);
#endif
#endif //GTP_HOTKNOT
extern s32 gt1x_init_node(void);

#if GTP_GESTURE_WAKEUP
extern DOZE_T gesture_doze_status;
extern int gesture_enabled;
extern s32 gesture_event_handler(struct input_dev *dev);
extern s32 gesture_enter_doze(void);
extern void gesture_clear_wakeup_data(void);
#endif

/* Export from gt1x_tpd.c */
extern void gt1x_touch_down(s32 x, s32 y, s32 z, s32 size, s32 id);
extern void gt1x_touch_up(s32 id);
extern void gt1x_power_switch(s32 state);
extern void gt1x_irq_enable(void);
extern void gt1x_irq_disable(void);
extern int gt1x_debug_proc(u8 * buf, int count);

struct fw_update_info {
	int update_type;
	int status;
	int progress;
	int max_progress;
	struct fw_info *firmware;
	u32 fw_length;

	// file update
	char *fw_name;
	u8 *buffer;
	mm_segment_t old_fs;
	struct file *fw_file;

	// header update
	u8 *fw_data;
};

/* Export form gt1x_update.c */
extern struct fw_update_info update_info;

extern u8 gt1x_default_FW[];
extern int gt1x_hold_ss51_dsp(void);
extern int gt1x_auto_update_proc(void *data);
extern int gt1x_update_firmware(char *filename);
extern void gt1x_enter_update_mode(void);
extern void gt1x_leave_update_mode(void);
extern int gt1x_hold_ss51_dsp_no_reset(void);
extern int gt1x_load_patch(u8 * patch, u32 patch_size, int offset, int bank_size);
extern int gt1x_startup_patch(void);

/* Export from gt1x_tool.c */
#if GTP_CREATE_WR_NODE
extern int gt1x_init_tool_node(void);
extern void gt1x_deinit_tool_node(void);
#endif

/* Export from gt1x_generic.c */
extern struct i2c_client *gt1x_i2c_client;

extern CHIP_TYPE_T gt1x_chip_type;
extern struct gt1x_version_info gt1x_version;

extern s32 gt1x_init_debug_node(void);
extern void gt1x_deinit_debug_node(void);

extern s32 _do_i2c_read(struct i2c_msg *msgs, u16 addr, u8 * buffer, s32 len);
extern s32 _do_i2c_write(struct i2c_msg *msg, u16 addr, u8 * buffer, s32 len);
extern s32 gt1x_i2c_write(u16 addr, u8 * buffer, s32 len);
extern s32 gt1x_i2c_read(u16 addr, u8 * buffer, s32 len);
extern s32 gt1x_i2c_test(void);
extern s32 gt1x_i2c_read_dbl_check(u16 addr, u8 * buffer, s32 len);

extern u8 gt1x_config[];
extern u32 gt1x_cfg_length;
extern u8 gt1x_int_type;
extern u8 gt1x_wakeup_level;
extern u32 gt1x_abs_x_max;
extern u32 gt1x_abs_y_max;
extern u8 gt1x_rawdiff_mode;
extern u8 gt1x_driver_num;
extern u8 gt1x_sensor_num;
extern u8 gt1x_init_failed;

extern s32 gt1x_init(void);
extern void gt1x_deinit(void);
extern s32 gt1x_read_version(struct gt1x_version_info *ver_info);
extern s32 gt1x_enter_sleep(void);
extern s32 gt1x_wakeup_sleep(void);
extern s32 gt1x_init_panel(void);
extern s32 gt1x_get_chip_type(void);
extern s32 gt1x_request_event_handler(void);
extern int gt1x_send_cmd(u8 cmd, u8 data);
extern s32 gt1x_send_cfg(u8 * config, int cfg_len);
extern void gt1x_select_addr(void);
extern s32 gt1x_reset_guitar(void);
extern void gt1x_power_reset(void);
extern int gt1x_parse_config(char *filename, u8 * gt1x_config);
extern s32 gt1x_touch_event_handler(u8 * data, struct input_dev *dev, struct input_dev *pen_dev);

#if GTP_HAVE_TOUCH_KEY
extern const u16 gt1x_touch_key_array[];
#endif

#if GTP_WITH_STYLUS
extern struct input_dev *pen_dev;
extern void gt1x_pen_down(s32 x, s32 y, s32 size, s32 id);
extern void gt1x_pen_up(s32 id);
#endif

#if GTP_PROXIMITY
extern u8 gt1x_proximity_flag;
extern u8 gt1x_proximity_detect;
extern void gt1x_report_ps(u8 state);
extern void gt1x_ps_init(void);
extern int gt1x_prox_event_handler(u8 * data);
#endif

#if GTP_ESD_PROTECT
extern void gt1x_init_esd_protect(void);
extern void gt1x_deinit_esd_protect(void);
extern s32 gt1x_init_ext_watchdog(void);
extern void gt1x_esd_switch(s32 on);
#endif

#if GTP_CHARGER_SWITCH
extern u8 gt1x_config_charger[GTP_CONFIG_MAX_LENGTH];
extern u32 gt1x_get_charger_status(void);
extern void gt1x_charger_switch(s32 on);
extern void gt1x_charger_config(s32 dir_update);
#endif

#ifdef CONFIG_CREATE_GLOVED_INTERFACE
extern u8 gt1x_config_gloved[GTP_CONFIG_MAX_LENGTH];
extern int current_gloved_finger_state;
extern int g_gloved_flag;
extern void write_gloved_value(u8 value);
extern int gloved_finger_proc_init(void);
#endif
//#define ndt_i2c_comm_lock()  __ndt_i2c_comm_lock(__func__, __LINE__);
//#define ndt_i2c_comm_unlock()  __ndt_i2c_comm_unlock(__func__, __LINE__);

int ndt_stress_set_vlaue(unsigned short x1,  unsigned short y1, unsigned char status);
int ndt_stress_get_vlaue(unsigned int *value);
int ndt_stress_suspend(void);
int ndt_stress_resume(void);
void ndt_i2c_comm_lock(void);
void ndt_i2c_comm_unlock(void);

#endif // _GT1X_GENERIC_H_
#ifndef SEG7_DISPLAY_MOD
#define SEG7_DISPLAY_MOD

#define GPIO_PINS_NUMBER	8

#define DEVICE_FILE_NAME	(unsigned char *)"7_segDisplay"
#define DEVICE_DRIVER_NAME	(unsigned char*)"seg7 dislplay"
#define CLASS_NAME			(unsigned char*)"Seg7_class"

int open_module (struct inode *node, struct file *file_mod);
ssize_t write_module(struct file *file_mod, const char __user *user_buffer, size_t count, loff_t *offs);
int close_module (struct inode *node, struct file *file_mod);
int module_probe(struct platform_device *pdev);
void module_shutdown(struct platform_device *pdev);


#endif

/* #define D7S_SEGA	2		
#define D7S_SEGB	3
#define D7S_SEGC	4
#define D7S_SEGD	17
#define D7S_SEGE	27
#define D7S_SEGF	22
#define D7S_SEGG	10
#define COM_PIN		26 */

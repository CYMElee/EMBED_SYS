#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>  //using allocate memory
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/printk.h>
#include <linux/atomic.h>

//===the character buffer and file struct that store input.txt====//
char *input_buf = NULL  ;
loff_t input_offset = 0;

int input_index = 0;

struct file *input_file;

//===the character buffer and file struct that store output.txt====//
char *output_buf = NULL;
struct file *output_file;
int output_index = 0;

loff_t output_offset = 0;


static int fileIO_init(void)
{
	//==allocate mamory ====//
	input_buf = kmalloc(2048*sizeof(char),GFP_DMA);
	output_buf = kmalloc(2048*sizeof(char),GFP_DMA);
	printk("success allocate momory");
	input_offset = 0;
	
	input_index = 0;
	
	output_index = 0;
	output_offset = 0;
	
	//==open input.txt and save into buffer ==//
	input_file = filp_open("/home/lee/yajie_ws/homework1/file_io/input.txt", 			O_RDONLY,0);
	printk("success open intput file");
	kernel_read(input_file, input_buf ,1024, &input_offset);
	
	while(input_buf[input_index] >='a' && input_buf[input_index] <='z')
	{
	input_index++;
	}
	input_index--;
	while(input_index >=0)
	{
	
	output_buf[output_index] = input_buf[input_index];
	
	
	input_index--;
	output_index++;
	}
	
	output_file = filp_open("/home/lee/yajie_ws/homework1/file_io/output.txt", 			O_WRONLY,0);
	
	kernel_write(output_file, output_buf ,output_index, &output_offset);
	
	
	


	return 0;
}

 
static void fileIO_exit(void)
{
	kfree(input_buf);
	kfree(output_buf);

	filp_close(input_file, NULL);
	filp_close(output_file, NULL);



}


module_init(fileIO_init);
module_exit(fileIO_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fileIO");
MODULE_AUTHOR("NCRL,LEE,YA-JIE");

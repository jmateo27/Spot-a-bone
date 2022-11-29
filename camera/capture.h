/*
 *  V4L2 video capture example, modified by Derek Molloy for the Logitech C920 camera
 *  Modifications, added the -F mode for H264 capture and associated help detail
 *  www.derekmolloy.ie
 *
 *  V4L2 video capture example
 *
 *  This program can be used and distributed without restrictions.
 *
 *      This program is provided with the V4L2 API
 * see http://linuxtv.org/docs.php for more information
 */

#ifndef CAPTURE_H_
#define CAPTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

static void errno_exit(const char *s);
static int xioctl(int fh, int request, void *arg);
static void process_image(const void *p, int size);
static int read_frame(void);
static void mainloop(void);
static void stop_capturing(void);
static void start_capturing(void);
static void uninit_device(void);
static void init_read(unsigned int buffer_size);
static void init_mmap(void);
static void init_userp(unsigned int buffer_size);
static void init_device(void);
static void close_device(void);
static void open_device(void);
static void usage(FILE *fp, int argc, char **argv);

#endif
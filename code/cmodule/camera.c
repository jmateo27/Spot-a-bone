/* V4L2 video picture grabber
   Copyright (C) 2009 Mauro Carvalho Chehab <mchehab@infradead.org>
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation version 2 of the License.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   Modified by Derek Molloy (www.derekmolloy.ie)
   Modified to change resolution details and set paths for the Beaglebone.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <libv4l2.h>
#include <stdbool.h>
#include <time.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

// char *photosDir = "/mnt/remote/myApps/spotabone/photos/";
char *commandFile = "/mnt/remote/myApps/spotabone/camera.txt";

// PROTOTYPES
bool isCommand();

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

struct buffer
{
	void *start;
	size_t length;
};

static void xioctl(int fh, int request, void *arg)
{
	int r;

	do
	{
		r = v4l2_ioctl(fh, request, arg);
	} while (r == -1 && ((errno == EINTR) || (errno == EAGAIN)));

	if (r == -1)
	{
		fprintf(stderr, "error %d, %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{

	while (1)
	{
		while (!isCommand()){
			msleep(50);
		};
		struct v4l2_format fmt;
		struct v4l2_buffer buf;
		struct v4l2_requestbuffers req;
		enum v4l2_buf_type type;
		fd_set fds;
		struct timeval tv;
		int r, fd = -1;
		unsigned int i, n_buffers;
		char *dev_name = "/dev/video0";
		char out_name[256], new_name[256];
		FILE *fout;
		struct buffer *buffers;

		fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
		if (fd < 0)
		{
			perror("Cannot open device");
			exit(EXIT_FAILURE);
		}

		CLEAR(fmt);
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.width = 1920;
		fmt.fmt.pix.height = 1080;
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
		xioctl(fd, VIDIOC_S_FMT, &fmt);
		if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24)
		{
			printf("Libv4l didn't accept RGB24 format. Can't proceed.\n");
			exit(EXIT_FAILURE);
		}
		if ((fmt.fmt.pix.width != 640) || (fmt.fmt.pix.height != 480))
			printf("Warning: driver is sending image at %dx%d\n",
				   fmt.fmt.pix.width, fmt.fmt.pix.height);

		CLEAR(req);
		req.count = 2;
		req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		req.memory = V4L2_MEMORY_MMAP;
		xioctl(fd, VIDIOC_REQBUFS, &req);

		buffers = calloc(req.count, sizeof(*buffers));
		for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
		{
			CLEAR(buf);

			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			buf.index = n_buffers;

			xioctl(fd, VIDIOC_QUERYBUF, &buf);

			buffers[n_buffers].length = buf.length;
			buffers[n_buffers].start = v4l2_mmap(NULL, buf.length,
												 PROT_READ | PROT_WRITE, MAP_SHARED,
												 fd, buf.m.offset);

			if (MAP_FAILED == buffers[n_buffers].start)
			{
				perror("mmap");
				exit(EXIT_FAILURE);
			}
		}

		for (i = 0; i < n_buffers; ++i)
		{
			CLEAR(buf);
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			buf.index = i;
			xioctl(fd, VIDIOC_QBUF, &buf);
		}
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		xioctl(fd, VIDIOC_STREAMON, &type);

		for (i = 0; i < 5; i++)
		{
			do
			{
				FD_ZERO(&fds);
				FD_SET(fd, &fds);

				/* Timeout. */
				tv.tv_sec = 2;
				tv.tv_usec = 0;

				r = select(fd + 1, &fds, NULL, NULL, &tv);
			} while ((r == -1 && (errno = EINTR)));
			if (r == -1)
			{
				perror("select");
				return errno;
			}

			CLEAR(buf);
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			xioctl(fd, VIDIOC_DQBUF, &buf);

			sprintf(out_name, "grabber%03d.ppm", i);
			sprintf(new_name, "/mnt/remote/myApps/spotabone/photos/grabber%03d.ppm", i);
			fout = fopen(out_name, "w");
			if (!fout)
			{
				perror("Cannot open image");
				exit(EXIT_FAILURE);
			}
			fprintf(fout, "P6\n%d %d 255\n",
					fmt.fmt.pix.width, fmt.fmt.pix.height);
			fwrite(buffers[buf.index].start, buf.bytesused, 1, fout);
			fclose(fout);

			xioctl(fd, VIDIOC_QBUF, &buf);
			// move the file to the new directory;
			rename(out_name, new_name);
		}

		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		xioctl(fd, VIDIOC_STREAMOFF, &type);
		for (i = 0; i < n_buffers; ++i)
			v4l2_munmap(buffers[i].start, buffers[i].length);
		v4l2_close(fd);
	}

	return 0;
}

typedef int FD;

bool isCommand()
{
	FD pFile = open(commandFile, O_RDWR);
	if (!pFile)
	{
		printf("ERROR: Unable to open file (%s) for read\n", commandFile);
		exit(-1);
	}
	// FILE *pFile = fopen(commandFile, "r");
	// if (pFile == NULL)
	// {
	// 	printf("ERROR: Unable to open file (%s) for read\n", commandFile);
	// 	exit(-1);
	// }
	// Read string (line)
	char result[256];
	ssize_t count;
	count = read(pFile, result, 16);
	// Close
	// fclose(pFile);
	fclose(fopen(commandFile, "w")); // Clear the file
	if (count > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

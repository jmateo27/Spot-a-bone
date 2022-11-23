#include "includes/socketIO.h"

static int socketfd_s, connectionfd_s;
static struct sockaddr_un address_s;

void Socket_init()
{
    struct sockaddr_un address;
    int socket_fd, connection_fd;


    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }

    unlink("/tmp/demo_socket");
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, UNIX_PATH_MAX, "/tmp/demo_socket");

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_un)) != 0)
    {
        printf("bind() failed\n");
        return 1;
    }
    if (listen(socket_fd, 5) != 0)
    {
        printf("listen() failed\n");
        return 1;
    }

    // Save the variables globally
    socketfd_s = socket_fd;
    connectionfd_s = connection_fd;
    address_s = address;
}

void Socket_send(char *msg)
{
    socklen_t address_length;
    address_length = sizeof(address_s);
    while ((connectionfd_s = accept(socketfd_s, (struct sockaddr *)&address_s, &address_length)) > -1)
    {
        if (write(socketfd_s, msg, strlen(msg) < 0))
            printf("ERROR writing to socket\n");
        break;
    }
}

void Socket_cleanup()
{
    close(socketfd_s);
}
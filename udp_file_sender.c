#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int arc, char *argv[])
{
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    char *tenFile = argv[1];
    sendto(sender, tenFile, strlen(tenFile), 0, (struct sockaddr *)&addr, sizeof(addr));

    // buf chứa nội dụng file
    char buf[2048];
    int ret;

    FILE *f = fopen(tenFile, "r");
    while (!feof(f))
    {
        ret = fread(buf, 1, sizeof(buf), f);
        if (ret <= 0)
            break;
    }

    sendto(sender, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
    fclose(f);
    close(sender);
}

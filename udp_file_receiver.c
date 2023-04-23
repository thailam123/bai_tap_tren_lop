#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char*argv[])
{
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    bind(receiver, (struct sockaddr *)&addr, sizeof(addr));

    char buf[16];

    int ret = recvfrom(receiver, buf, sizeof(buf), 0,
                       NULL, NULL);
    if (ret <= 0)
    {
        return 1;
    }

    buf[ret] = 0;
    printf("%d bytes received: %s\n", ret, buf);

    char tenFile[] = "file_receiver.txt";
    // chứa nội dung file
    char buf1[2048];
    FILE *f = fopen(tenFile, "w");

    ret = recvfrom(receiver, buf1, sizeof(buf1), 0, NULL, NULL);
    if (ret <= 0)
        return 1;

    fwrite(buf1, 1, ret, f);

    fclose(f);
    close(receiver);
}

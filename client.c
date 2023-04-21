#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }
    // bài làm
    // đọc nội dung văn bản lưu vào buf
    char filename[] = "vanban.txt";
    FILE *f = fopen(filename, "r");
    char buf[2048];

    while (!feof(f))
    {
        fread(buf, 1, sizeof(buf), f);
    }

    send(client, buf, strlen(buf), 0);
    
    // kết thúc bài làm
    fclose(f);
    close(client);
}

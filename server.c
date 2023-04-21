#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    int client = accept(listener, NULL, NULL);
    if (client == -1)
    {
        perror("accept() failed");
        return 1;
    }
    printf("New client connected: %d\n", client);
    // bài làm
    char buf[20];
    // buf strcat
    char buf_strcat[2048] = "";
    while (1)
    {

        int ret = recv(client, buf, sizeof(buf), 0);
        buf[ret] = 0;
        if (ret <= 0)
            break;
        strcat(buf_strcat, buf);
    }

    // buf sau khi tách chuỗi

    char buf1[2048];

    // tách chuỗi ký tự lưu vào buf1
    const char s[6] = " \n";
    char *token;

    token = strtok(buf_strcat, s);

    while (token != NULL)
    {
        strcat(buf1, token);
        token = strtok(NULL, s);
    }
    
    //phần frequency
    char what[] = "0123456789";

    int what_len = strlen(what);
    int count = 0;

    char *where = buf1;

    if (what_len)
        while ((where = strstr(where, what)))
        {
            where += what_len;
            count++;
        }
    printf("số lần xuất hiện của xâu \"0123456789\"là: %d\n",count);

    // kết thúc bài làm

    close(client);
    close(listener);
}

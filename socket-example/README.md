[TOC]

## Linux 网络编程基础 API

### socket 地址 API

- 字节序转化函数

  小端字节序（主机字节序）和大端字节序（网络字节序）。

  一般需要使用 htonl/htons 把 ipv4地址 和 端口号 啥的转化为大端字节序。

  ```c
  #include <netinet/in.h>
  // 32 位小端字节序转化为 32 位大端字节序
  unsigned logn int htonl(unsigned long int hostlong);
  // 16 位
  unsigned short int htons(unsigned short int hostshort);
  // 32 位大端字节序转化为 32 位小端字节序
  unsigned long int ntohl(unsigned long int netlong);
  // 16 位
  unsigned short int ntohs(unsigned short int netshort);
  ```

- IP 地址转化函数

  在使用动态地址的情况下，使用这些函数是标准做法。

   ```c
  #include <arpa/inet.h>
  // 只支持 ipv4，把 ipv4 字符串转化为 32 位网络字节序
  in_addr_t inet_addr(const char *cp);
  /*
  struct sockaddr_in addr;
  addr.sin_addr.s_addr = inet_addr("192.168.1.100");
  */
  
  // 把 ipv4 字符串转化为 struct in_addr
  int inet_ation(const char *cp, struct in_addr *inp);
  /*
  struct sockaddr_in addr;
  inet_aton("192.168.1.100", &addr.sin_addr);
  */
  
  // 支持 ipv4 和 ipv6
  // af : AF_INET/AF_INET6
  // src: 字符串 IP
  // dst: struct in_addr* 或者 struct in6_addr
  int inet_pton(int af, const char *src, void *dst);
  /*
  struct sockaddr_in addr;
  inet_pton(AF_INET, "192.168.1.100", &addr.sin_addr);
  */
  
  // 二进制 -> 字符串 ipv4
  // 返回静态缓冲区
  char* inet_ntoa(struct in_addr in);
  /*
  struct sockaddr_in addr;
  char* ip_str = inet_ntoa(addr.sin_addr);
  */
  
  // 支持 ipv4 和 ipv6
  // af  : AF_INET/AF_INET6
  // src : struct in_addr*/struct in6_addr*
  // dst : 输出缓冲区 char buf[INET_ADDRSTRLEN];
  // size: 缓冲区大小
  const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
  /*
  char buf[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf));
  */
   ```

### 创建 socket

```c
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain,int type,int protocol);
```


#include "string.h"

#include "wyatt_sock.h"

float PacketDropRate = 0;

int GetError()
{
#ifdef _WIN32
  int err;
  err = WSAGetLastError();
  if (err == WSAEWOULDBLOCK)
    return EBLOCK;
  return err;
#else
  if (errno == EAGAIN || errno == EWOULDBLOCK)
    return EBLOCK;
  return errno;
#endif
}

void SetNonBlocking(SOCKET sock)
{
  //make the socket non-blocing
  unsigned long  mode = 1;
#ifdef _WIN32
  ioctlsocket(sock, FIONBIO, &mode);
#else
  ioctl(sock, FIONBIO, &mode);
#endif
}

void Close(SOCKET sock, bool now)
{
  if (now)
  {
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
  }
  else
  {
    shutdown(sock, SD_SEND);
  }
}

int SendTCP(SOCKET sock, const char* buffer, int bytes)
{
  int result = send(sock, buffer, bytes, MSG_NOSIGNAL);
  if (result == SOCKET_ERROR)
    return -1;
  else
    return result;
}


int Send(SOCKET sock, const char* buffer, int bytes, const sockaddr_in* dest)
{
  if (rand() / double(RAND_MAX) < PacketDropRate)
    return bytes;
  int result = sendto(sock, buffer, bytes, 0, (sockaddr*)dest, sizeof(sockaddr_in));
  if (result == SOCKET_ERROR)
    return -1;
  else
    return result;
}

int Receive(SOCKET sock, char* buffer, int maxBytes, sockaddr_in *addr)
{
#ifdef _WIN32
  int size = sizeof(sockaddr);
#else
  unsigned size = sizeof(sockaddr);
#endif

  int bytes = recvfrom(sock, buffer, maxBytes, 0, reinterpret_cast<sockaddr*>(addr), &size);
  if (bytes == SOCKET_ERROR)
    return -1;

  return bytes;
}

int Receive(SOCKET sock, char* buffer, int maxBytes)
{
  sockaddr_in sender;
  return Receive(sock, buffer, maxBytes, &sender);
}

int ReceiveTCP(SOCKET sock, char* buffer, int maxBytes)
{
  int bytes = recv(sock, buffer, maxBytes, 0);
  if (bytes == SOCKET_ERROR)
    return -1;
  return bytes;
}


int Bind(SOCKET sock, sockaddr_in* addr)
{
  int size = sizeof(sockaddr_in);
  int result = bind(sock, (sockaddr*)addr, size);
  if (result == SOCKET_ERROR)
    return GetError();

  return 0;
}

void CreateAddress(const char* ip, int port, sockaddr_in *res)
{
  //clear the memory
  memset(res, 0, sizeof(*res));

  res->sin_family = AF_INET;
  res->sin_port = htons(port);

  if (ip == NULL)
    res->sin_addr.s_addr = INADDR_ANY;
  else
  {
#ifdef _WIN32
    res->sin_addr.S_un.S_addr = inet_addr(ip);
#else
    inet_pton(res->sin_family, ip,
      &(res->sin_addr));
#endif
  }
}

sockaddr_in* CreateAddress(const char* ip, int port)
{
  sockaddr_in* result = (sockaddr_in*)malloc(sizeof(*result));

  CreateAddress(ip, port, result);

  return result;
  // Caller will be responsible for free()
}


SOCKET CreateSocket(int protocol)
{
  SOCKET result = INVALID_SOCKET;

  int type = SOCK_DGRAM;
  if (protocol == IPPROTO_TCP)
    type = SOCK_STREAM;

  result = socket(AF_INET, type, protocol);

  return result;
}

int Connect(SOCKET sock, sockaddr_in* address)
{
  if (connect(sock, (sockaddr*)address, sizeof(sockaddr_in)) == SOCKET_ERROR)
    return GetError();
  else
    return 0;
}


int Init()
{
#ifdef _WIN32
  WSADATA wsa;

  int error = WSAStartup(MAKEWORD(2, 2), &wsa);
  return error;
#else
  return 0;
#endif
}

void Deinit()
{
#ifdef _WIN32
  WSACleanup();
#endif
}

int Listen(SOCKET socket, int backlog)
{
  return listen(socket, backlog);
}
SOCKET Accept(SOCKET socket, sockaddr_in* addr)
{
#ifdef _WIN32
  int len = sizeof(*addr);
#else
  unsigned len = sizeof(*addr);
#endif
  return accept(socket,  (sockaddr *)(addr), &len);
}
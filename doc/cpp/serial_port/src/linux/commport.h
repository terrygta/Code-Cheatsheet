#ifndef COMMPORT_H
#define COMMPORT_H

#include <cstdlib>
#include <stdint.h>

class CommPortT
{
public:
  CommPortT();
  ~CommPortT();

  bool Open(const char* deviceName, int baudRate, bool blocking = false);
  bool IsOpen() const;
  void Close();

  int GetBaudRate() const;

  // out stream
  size_t writeData(const void* data, size_t n);
  size_t writeStr(const char* str);
  size_t writeByte(uint8_t data);

  // in stream
  size_t readByte(unsigned char& data);
  size_t readData(unsigned char* data, size_t size);

  size_t GetRxSize() const;
  void FlushReadBuffer();

private:
  int BaudRate;
  bool Opened;
  int PortFd;
};

#endif
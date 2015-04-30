#include "commport.h"

#include <termios.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <cstring>
#include <sys/ioctl.h>
#include <assert.h>

CommPortT::CommPortT()
  : BaudRate(0),
    Opened(false),
    PortFd(0)
{
}


CommPortT::~CommPortT()
{
  if (Opened)
    Close();
}


int CommPortT::GetBaudRate() const
{
  return BaudRate;
}


// blocking: Specifies that this is being used from a thread so that 
//   reading and writing are blocking but the read thread will timeout after
//   1 tenth of a second.
bool CommPortT::Open(const char* deviceName, int baudRate, bool blocking)
{
  if (Opened)
    Close();

  int openFlags = O_RDWR | O_NOCTTY;
  if (!blocking)
  {
    openFlags |= O_NONBLOCK;
  }


  PortFd = open(deviceName, openFlags);

  if (PortFd < 0)
  {
    return false;
  }

  BaudRate = baudRate;

  struct termios options;
  tcgetattr(PortFd, &options);

  // Set the baud rate
  cfsetispeed(&options, BaudRate);
  cfsetospeed(&options, BaudRate);

  // Enable the receiver and set local mode
  options.c_cflag |= (CLOCAL | CREAD);

  // 8 dat bits, no parity bit. 1 stop bit
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;

  // RTS/CTS handshaking off
  options.c_cflag &= ~CRTSCTS;

  // Raw input and output
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | ECHOK);
  options.c_iflag = 0;
  options.c_oflag = 0;

  if (blocking)
  {
    // This is so when we are doing reads in a thread that we have a way to 
    // return from the blocked read call.
    options.c_cc[VTIME] = 1;  // tenths of a second
    options.c_cc[VMIN] = 0;
  }

  tcsetattr(PortFd, TCSANOW, &options);

  Opened = true;

  return true;
}


bool CommPortT::IsOpen() const
{
  return Opened;
}


void CommPortT::Close()
{
  if (!Opened)
    return;

  // Flush the port so that we can close it without blocking.
  tcflush(PortFd, TCOFLUSH);
  close(PortFd);
  PortFd = 0;
  Opened = false;
}


size_t CommPortT::GetRxSize() const
{
  int bytes;
  ioctl(PortFd, FIONREAD, &bytes);
  return bytes;
}


size_t CommPortT::readData(unsigned char* data, size_t bytes)
{
  assert(Opened);

  int status = read(PortFd, data, bytes);

  if (status <= 0)
  {
    return 0;
  }
  else
  {
    return status;
  }
}


void CommPortT::FlushReadBuffer()
{
  assert(Opened);
  tcflush(PortFd, TCIFLUSH);
}


size_t CommPortT::readByte(unsigned char& data)
{
  int status = read(PortFd, &data, 1);
  if (status <= 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//An implementation of busy wait write
size_t CommPortT::writeData(const void *data, size_t n)
{

  int bytesToWrite = n;

  const uint8_t* bytePtr = (const uint8_t*)(data);
  time_t start;
  time(&start);
  size_t totalBytesWritten = 0;

  for (;;)
  {
    int bytesWritten = write(PortFd, bytePtr, bytesToWrite);


    if (bytesWritten == bytesToWrite)
    {
      totalBytesWritten += bytesWritten;
      return totalBytesWritten;
    }

    time_t now;
    time(&now);
    if (now - start > 3)
    {
      //write timeout
      return totalBytesWritten;
    }

    if (bytesWritten > 0)
    {
      bytesToWrite -= bytesWritten;
      bytePtr += bytesWritten;
      totalBytesWritten += bytesWritten;
    }
  }
}


size_t CommPortT::writeStr(const char* str)
{
  return writeData(str, strlen(str));
}


size_t CommPortT::writeByte(uint8_t data)
{
  return writeData(&data, 1);
}
//
// Server.cpp for stephane_plazza in /home/tuxlu/proj/cpp_plazza
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Wed Apr 20 14:21:36 2016 Lucas Parsy
// Last update Fri Jun 17 17:52:32 2016 Lucas Parsy
//

#include <iostream>
#include "Network.hpp"

Network::Network(int Nport, char *Nip) : fd(42),
					       port(Nport),
					       ip(Nip),
					       end(false)
{
  initNetwork();
}

Network::~Network()
{
  mtx.lock();
  send(this->fd, "\04", 1, 0);
  end  = true;
  mtx.unlock();
  readThr.join();
  if (fd != -42)
    close(fd);
}

void Network::myExit(const std::string &str)
{
  std::cerr << str << std::endl;
  exit(1);
}

int Network::write(const std::string &str)
{
  int ret;

  mtx.lock();
  ret = send(this->fd, str.c_str(), str.length(), 0);
  if (ret != -1)
    ret = send(this->fd, "\n", 1, 0);
  mtx.unlock();
  return ret;
}

void	Network::socketRead()
{
  char c;
  int res;
  struct timeval tv;
  fd_set         readfs;
  std::string    line;

  tv.tv_sec = 1;
  tv.tv_usec = 0;

  while (42)
    {
      mtx.lock();
      if (this->end == true)
	{
	  mtx.unlock();
	  break;
	}
      FD_ZERO(&readfs);
      FD_SET(fd, &readfs);
      if (select(fd + 1, &readfs, NULL, NULL, &tv) == -1)
	throw std::runtime_error("error on client Select");

      if (FD_ISSET(fd, &readfs))
	{
	  line = "";
	  c = 42;
	  res = 42;
	  while (res > 0 && c != '\n')
	    {
	      res  = recv(this->fd, &c, 1, 0);
	      if (res == -1)
		throw std::runtime_error("error while reading on socket");
	      if (res != 0 && c != '\n')
		{
		  line += c;
		}
	    }
	  this->lines.push_back(line);
	}
      mtx.unlock();
    }
}

std::string	Network::read()
{
  if (this->lines.empty())
    return "";
  mtx.lock();
  std::string str = this->lines.front();
  mtx.unlock();
  this->lines.pop_front();
  return (str);
}

void	Network::initNetwork()
{
  if (!(pe = getprotobyname("TCP")))
    myExit("couldn't init TCP connection");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    myExit("couldn't obtain file descriptor");

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);

  s_in.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr * )&s_in, sizeof(s_in)) == -1)
    {
      close(fd);
      myExit("couldn't connect to file descriptor");
    }
  this->write("GRAPHIC");
  this->readThr = std::thread(&Network::socketRead, this);
}

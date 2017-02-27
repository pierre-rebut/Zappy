//
// Socket.hpp for stephane_plazza in /home/tuxlu/proj/cpp_plazza
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Tue Apr 19 16:07:20 2016 Lucas Parsy
// Last update Fri Jun 17 17:38:21 2016 Lucas Parsy
//

#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <deque>
#include <thread>
#include <mutex>

#include <string>
#include <stdexcept>

class Network {
private:
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;
  int			port;
  char		  	*ip;

  std::mutex		mtx;
  std::thread		readThr;
  bool			end;

  std::deque<std::string> lines;

  void myExit(const std::string &str);
  void socketRead();
public:
  Network(int Nport, char *Nip);
  ~Network();
  void initNetwork();
  int write(const std::string &str);
  std::string read();
};

#endif /*_NETWORK_HPP_*/

/*
 * Poller.h
 *
 *  Created on: Dec 26, 2017
 *      Author: Daniel Yuan
 */

#ifndef SOCKETOPS_H_
#define SOCKETOPS_H_
#include <arpa/inet.h>

namespace sockets
{
	int createNonblockingOrDie();
	int  accept(int sockfd, struct sockaddr_in* addr);
	int  connect(int sockfd, const struct sockaddr* addr);
	void bindOrDie(int sockfd, const struct sockaddr* addr);
	void listenOrDie(int sockfd);
	ssize_t read(int sockfd, void *buf, size_t count);
	ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
	ssize_t write(int sockfd, const void *buf, size_t count);
	void close(int sockfd);
	void shutdownWrite(int sockfd);
	void shutdownReadWrite(int sockfd);
	void toIpPort(char* buf, size_t size,
	              const struct sockaddr* addr);
	void toIp(char* buf, size_t size,
	          const struct sockaddr* addr);

	void fromIpPort(const char* ip, uint16_t port,
	                struct sockaddr_in* addr);
	void fromIpPort(const char* ip, uint16_t port,
	                struct sockaddr_in6* addr);	
	
	struct sockaddr* sockaddr_cast(struct sockaddr_in *addr);
	const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
	
	struct sockaddr_in getLocalAddr(int sockfd);

	inline uint64_t hostToNetwork64(uint64_t host64)
	{
	  return htobe64(host64);
	}
	
	inline uint32_t hostToNetwork32(uint32_t host32)
	{
	  return htobe32(host32);
	}
	
	inline uint16_t hostToNetwork16(uint16_t host16)
	{
	  return htobe16(host16);
	}
	
	inline uint64_t networkToHost64(uint64_t net64)
	{
	  return be64toh(net64);
	}
	
	inline uint32_t networkToHost32(uint32_t net32)
	{
	  return be32toh(net32);
	}
	
	inline uint16_t networkToHost16(uint16_t net16)
	{
	  return be16toh(net16);
	}

}
#endif


/*
 * Channel.h
 *
 *  Created on: Feb 09, 2018
 *      Author: Daniel Yuan
 */
#ifndef SRC_CHANNEL_H_
#define SRC_CHANNEL_H_

#include "socket.h"
#include <functional>
#include <iostream>
#include "EventLoop.h"

using namespace std;
class EventLoop;

class Channel:public cNonCopyable
{
public:
	typedef std::function<void()> EventCallback;

	Channel(EventLoop* loop,int fd);
	~Channel();
	
	void handleEvent();

	// for Poller
	int index() { return index_; }
	void set_index(int idx) { index_ = idx; }
	
	void setReadCallback(const EventCallback& cb)
	{ readCallback_ = cb; }
	void setWriteCallback(const EventCallback& cb)
	{ writeCallback_ = cb; }
	void setCloseCallback(const EventCallback& cb)
	{ closeCallback_ = cb; }
	void setErrorCallback(const EventCallback& cb)
	{ errorCallback_ = cb; }
	
	void enableReading() { events_ |= kReadEvent; update(); }
	void disableReading() { events_ &= ~kReadEvent; update(); }
	void enableWriting() { events_ |= kWriteEvent; update(); }
	void disableWriting() { events_ &= ~kWriteEvent; update(); }
  	void disableAll() { events_ = kNoneEvent; update(); }

	int fd() const { return fd_; }	
	int events() const { return events_; }
	void set_revents(int revt) { revents_ = revt; } // used by pollers
	bool isNoneEvent() const { return events_ == kNoneEvent; }


	// for debug
	string reventsToString() const;
	string eventsToString() const;

private:
	void update();
	static string eventsToString(int fd, int ev);

	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventLoop* loop_;
	const int  fd_;
	int 	   events_;
	int 	   revents_;
	int 	   index_; // used by Poller.
	bool	   logHup_;

	//boost::weak_ptr<void> tie_;
	bool tied_;
	bool eventHandling_;
	//ReadEventCallback readCallback_;
	EventCallback readCallback_;
	EventCallback writeCallback_;
	EventCallback closeCallback_;
	EventCallback errorCallback_;

protected:
};

#endif

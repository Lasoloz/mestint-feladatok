#ifndef NETPLAY_INCLUDED
#define NETPLAY_INCLUDED

#include <iostream>
#include <tcp/TcpSocket.hpp>
#include <tcp/TcpException.hpp>
#include <tcp/TcpListener.hpp>

void listenForEnemy();
void connectToEnemy();

void startup(TcpSocket &socket);

#endif

#include <game/netPlay.hpp>


void listenForEnemy() {
    TcpListener listener;
    try {
        listener.open(80, TcpListener::M_AF_IPV4);
        TcpSocket socket = listener.acceptConn();

        startup(socket);
    } catch (TcpException &ex) {
        std::cerr << "Failed to open TCP listener: " << ex.what() << '\n';
    }
}

void connectToEnemy() {
    // TcpSocket socket;
    std::cout << "Unimplemented!\n";
}


void startup(TcpSocket &socket) {
    std::cout << "Unimplemented!\n";
}

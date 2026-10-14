
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket < 0) {
        cout << "Socket creation failed!";
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // Input string
    string message;
    cout << "Enter a string: ";
    getline(cin, message);

    // Send string to server
    sendto(clientSocket, message.c_str(), message.length(), 0,
           (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Receive reversed string
    socklen_t serverLen = sizeof(serverAddr);
    int bytes = recvfrom(clientSocket, buffer, sizeof(buffer) - 1,
                         0, (struct sockaddr*)&serverAddr, &serverLen);

    if (bytes >= 0) {
        buffer[bytes] = '\0';
        cout << "Reversed string: " << buffer << endl;
    }

    close(clientSocket);
    return 0;
}

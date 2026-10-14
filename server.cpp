
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    char buffer[1024] = {0};

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket < 0) {
        cout << "Socket creation failed!";
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    // Bind socket
    if (::bind(serverSocket, (struct sockaddr*)&serverAddr,
               sizeof(serverAddr)) < 0) {
        cout << "Bind failed!" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "UDP Server waiting for message..." << endl;

    // Receive message from client
    int bytes = recvfrom(serverSocket, buffer, sizeof(buffer) - 1,
                         0, (struct sockaddr*)&clientAddr, &clientLen);

    if (bytes < 0) {
        cout << "Receive failed!";
        close(serverSocket);
        return 1;
    }

    buffer[bytes] = '\0';
    cout << "Client message: " << buffer << endl;

    // Reverse the string
    string result = buffer;
    for (int i = 0, j = result.length() - 1; i < j; i++, j--) {
        swap(result[i], result[j]);
    }

    // Send reversed string to client
    sendto(serverSocket, result.c_str(), result.length(), 0,
           (struct sockaddr*)&clientAddr, clientLen);

    cout << "Reversed string sent: " << result << endl;

    close(serverSocket);
    return 0;
}

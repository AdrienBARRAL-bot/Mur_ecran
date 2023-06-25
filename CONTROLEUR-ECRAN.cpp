#include <iostream> 
#include <string> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <fstream> 
#include <vector> 
#include <opencv2/opencv.hpp> 

void receiveImage(int socketServeur) { 
// Receive the image size 
int tailleImage; 
if (recv(socketServeur, &tailleImage, sizeof(tailleImage), 0) < 0) { 
std::cerr << "Error receiving image size." << std::endl; 
return; 
} 
std::vector<char> buffer(tailleImage); 
int remainingSize = tailleImage; 
int receivedSize; 
char* currentBuffer = buffer.data(); 
while (remainingSize > 0) { 
receivedSize = recv(socketServeur, currentBuffer, remainingSize, 0); 
if (receivedSize < 0) { 
std::cerr << "Error receiving image content." << std::endl; 
return; 
} 
remainingSize -= receivedSize; 
currentBuffer += receivedSize; 
} 
cv::Mat imageReceived(1, tailleImage, CV_8UC1, buffer.data()); 
cv::Mat imageDecoded = cv::imdecode(imageReceived, cv::IMREAD_COLOR); 
if (imageDecoded.empty()) { 
std::cerr << "Error decoding the image." << std::endl; 
return; 
} 
cv::imshow("Received Image", imageDecoded); 
cv::waitKey(0); 
cv::destroyAllWindows(); 
std::cout << "Image received and displayed." << std::endl; 
} 
int main() { 
int socketClient = socket(AF_INET, SOCK_STREAM, 0); 
if (socketClient < 0) { 
std::cerr << "Error creating the client socket." << std::endl; 
return 1; 
} 
sockaddr_in serverAddress{}; 
serverAddress.sin_family = AF_INET; 
serverAddress.sin_port = htons(8080); 
if (inet_pton(AF_INET, "172.16.8.174", &(serverAddress.sin_addr)) <= 0) { 
std::cerr << "Invalid IP address." << std::endl; 
return 1; 
} 
if (connect(socketClient, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) { std::cerr << "Error connecting to the server." << std::endl; 
return 1; 
} 
std::string message = "image1.jpg"; 
if (send(socketClient, message.c_str(), message.size(), 0) < 0) { 
std::cerr << "Error sending message to the server." << std::endl; 
close(socketClient); 
return 1; 
} 
receiveImage(socketClient); 
close(socketClient); 
return 0; 
}

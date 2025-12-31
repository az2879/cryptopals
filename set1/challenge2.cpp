#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

// Convert a hex string to a byte array
std::vector<unsigned char> hexToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(
            std::stoi(byteString, nullptr, 16)
        );
        bytes.push_back(byte);
    }

    return bytes;
}

// Convert byte array back to hex string
std::string bytesToHex(const std::vector<unsigned char>& bytes) {
    std::ostringstream oss;
    for (unsigned char byte : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte);
    }
    return oss.str();
}

int main() {
    std::cout << "Please provide no spaces hex strings to XOR:" << std::endl;
    std::string hex1, hex2;
    std::cin >> hex1 >> hex2;

    // Decode hex strings
    auto bytes1 = hexToBytes(hex1);
    auto bytes2 = hexToBytes(hex2);

    // XOR the buffers
    std::vector<unsigned char> result;
    for (size_t i = 0; i < bytes1.size(); ++i) {
        result.push_back(bytes1[i] ^ bytes2[i]);
    }

    // Convert result to hex
    std::string output = bytesToHex(result);
    std::cout << output << std::endl;

    return 0;
}
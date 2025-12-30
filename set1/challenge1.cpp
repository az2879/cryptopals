#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdint>

/*
    Converts a hexidecimal string to a byte array.
*/
std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("Hex string must have even length");
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2) {
        uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

/*
    Encodes a byte array to a base64 string.
*/
std::string base64_encode(const std::vector<uint8_t>& data) {
    static const char base64_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string result;
    size_t i = 0;

    while (i < data.size()) {
        uint32_t octet_a = i < data.size() ? data[i++] : 0;
        uint32_t octet_b = i < data.size() ? data[i++] : 0;
        uint32_t octet_c = i < data.size() ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        result.push_back(base64_table[(triple >> 18) & 0x3F]);
        result.push_back(base64_table[(triple >> 12) & 0x3F]);
        result.push_back(i - 2 < data.size() ? base64_table[(triple >> 6) & 0x3F] : '=');
        result.push_back(i - 1 < data.size() ? base64_table[triple & 0x3F] : '=');
    }

    return result;
}

int main() {
    std::string hex;
    std::cout << "Enter hex string: ";
    std::cin >> hex;

    auto bytes = hex_to_bytes(hex);
    std::string base64 = base64_encode(bytes);

    std::cout << "base64: " << base64 << std::endl;
}
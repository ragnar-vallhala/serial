#include <iostream>
#include <string>
#include "serial/serial.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <serial port address> <baudrate>" << endl;
        return 1;
    }

    string port(argv[1]);
    unsigned long baud = std::stoul(argv[2]);

    try {
        // Open the serial port with the specified baud rate and a timeout of 1000ms
        serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

        if (my_serial.isOpen()) {
            cout << "Serial port " << port << " opened at " << baud << " baud." << endl;
        } else {
            cerr << "Failed to open serial port." << endl;
            return 1;
        }

        while (true) {
            // Read available data from the serial port
            string data = my_serial.read(my_serial.available());

            // If data is received, print it
            if (!data.empty()) {
                cout<< data;
            }
        }
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}


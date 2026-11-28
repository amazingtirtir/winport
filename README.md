# ajar

A lightweight TCP port checker written in C++ using Windows Winsock, featuring DNS resolution and interactive port selection.

## Features

- **Fast TCP Port Scanning:** Quickly check whether specific TCP ports are open or closed.
- **DNS Resolution:** Enter hostnames (e.g., `example.com`) or raw IPv4 addresses.
- **Interactive Port Selection:** Easily choose common ports or input custom port numbers directly in the console.
- **Zero External Dependencies:** Built purely with standard C++ and native Windows Winsock (`ws2_32`).

## Requirements

- Windows OS
- A C++ compiler (MinGW/g++ or MSVC)

## Building from Source

### Using g++ (MinGW)
```bash
g++ main.cpp dns.cpp "port checker.cpp" -I. -o ajar.exe -lws2_32
```

### Using MSVC (Developer Command Prompt)
```cmd
cl main.cpp dns.cpp "port checker.cpp" /I. /Fe:ajar.exe ws2_32.lib
```

## Usage

Run the compiled executable from your terminal or double-click `ajar.exe`:

```cmd
ajar.exe
```

Follow the on-screen prompts to enter your target hostname/IP address and select the port(s) you wish to check.

## Disclaimer

This tool is intended for network diagnostics, troubleshooting, and educational purposes only. **Only scan networks, servers, or devices that you own or have explicit permission to test.** The author is not responsible for any misuse or damage caused by this software.

## License

This project is licensed under the [MIT License](LICENSE).

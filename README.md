# Minitalk

## Introduction
Minitalk is a communication program that uses UNIX signals for data transmission between a client and server. The project demonstrates the use of signals for inter-process communication (IPC) in UNIX-based systems.

The implementation adheres to specific constraints:
- Communication is done using only UNIX signals: SIGUSR1 and SIGUSR2
- The server must display strings quickly
- Error handling is thorough with no unexpected quits
- No memory leaks
- Limited to specific allowed functions: write, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, exit

## Project Structure

### Mandatory Part
- **server**: 
  - Must be started first and print its PID at launch
  - Receives and displays strings from clients
  - Must display strings quickly
  - Characters are stored in a buffer
  - Complete message is displayed only when the null terminator is received
  - Must be able to receive strings from several clients without needing to restart
- **client**: 
  - Takes two parameters: server PID and string to send
  - Sends the string to the server
  - No acknowledgment signals from server
- Communication must be done only using UNIX signals: SIGUSR1 and SIGUSR2

### Bonus Part
- Adds support for Unicode characters
- Implements acknowledgment signals from server to client
- Buffer-based approach for improved message handling

## How It Works

### Signal-Based Communication Scheme

1. **Binary Data Transmission**:
   - Characters are converted to binary (8 bits)
   - SIGUSR1 represents bit value '0'
   - SIGUSR2 represents bit value '1'

2. **Server Operation**:
   - Starts and displays its PID
   - Sets up signal handlers for SIGUSR1 and SIGUSR2
   - Waits for signals using pause()
   - Reconstructs characters bit-by-bit from received signals
   - Outputs complete messages to terminal

3. **Client Operation**:
   - Takes server PID as input
   - Converts each character of the message to binary
   - Sends SIGUSR1 or SIGUSR2 for each bit
   - Waits briefly between signals to prevent signal loss
   - In bonus version, waits for acknowledgment signals

### Bit-by-Bit Transmission Process

1. For each character in the message:
   - Convert to its 8-bit binary representation
   - For each bit: 
     - If bit is 0: send SIGUSR1
     - If bit is 1: send SIGUSR2
   - Wait for acknowledgment (bonus part)

2. At the server:
   - For each received signal:
     - Update the current bit in the character being assembled
     - Increment bit counter
     - When 8 bits are received, process the complete character
     - Send acknowledgment (bonus part)

### Buffer Implementation

In the standard version:
- Characters are stored in a buffer
- Complete message is displayed only when the null terminator is received

In the bonus version:
- Characters are stored in a buffer
- Complete message is displayed only when the null terminator is received
- Supports Unicode characters by handling raw bytes

### Acknowledgment System (Bonus)

The standard version does not implement any acknowledgment system. The client sends all signals and assumes successful delivery.

In the bonus version:

1. **Bit-by-Bit Acknowledgment**:
   - Server sends SIGUSR2 after receiving each bit
   - Client waits for this signal before sending the next bit

2. **Message Completion Acknowledgment**:
   - Server sends SIGUSR1 after receiving the null terminator
   - Client confirms message delivery to the user

## Compilation

```bash
# Compile mandatory part
make

# Compile bonus part
make bonus

# Clean object files
make clean

# Clean everything
make fclean

# Rebuild
make re
```

## Usage

```bash
# Start the server
./server

# Send a message (using the displayed PID from server)
./client <server_pid> "Your message here"

# For bonus features
./server_bonus
./client_bonus <server_pid> "Your message here"
```

## Implementation Details

### Signal Handling
- Uses `sigaction` with SA_SIGINFO flag for enhanced signal handling
- Retrieves sender PID from signal information

### Timing Considerations
- Includes delays between signals to prevent signal loss
- Adjusts timeouts based on system responsiveness

### Error Handling
- Checks for invalid PIDs
- Implements timeout mechanisms for unresponsive servers
- Provides user feedback on transmission status

### Global Variables
- The project uses global variables sparingly as allowed by the subject.
- In the bonus version:
  - Client: Uses a global variable `g_signal_received` to handle signal acknowledgments between handler functions and main code.
  - Server: Uses a global variable `g_client_pid` to store the sender's PID across signal handling calls.
- These globals are necessary because signal handlers need to share state with the main program execution.

## Useful Commands

### Signal Monitoring
```bash
# Watch for signals sent to a process
watch -n 0.1 "ps -p <PID> -o pid,cmd,sig"

# Trace signals with strace
strace -e signal -p <PID>

# Monitor system calls including signals
strace -f ./server
```

### Process Management
```bash
# List all processes with PIDs
ps aux

# Kill a specific process
kill <PID>

# Send specific signals
kill -SIGUSR1 <PID>
kill -SIGUSR2 <PID>
```

### Debugging
```bash
# Check for memory leaks
valgrind --leak-check=full ./server

# Run with gdb
gdb ./server
```

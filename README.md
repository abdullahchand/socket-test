# Socket Performance Test

A performance comparison project that implements echo servers and clients in three different programming languages: C++, Python, and Rust. This project demonstrates socket programming and concurrent connection handling across different languages and runtime environments.

## Project Overview

This project tests the performance of TCP socket communication by creating echo servers that simply return any data they receive. Each implementation spawns 10,000 concurrent client connections to measure throughput and latency.

## Project Structure

```
socket_test/
├── c++/
│   ├── CMakeLists.txt
│   ├── server.cpp
│   ├── client.cpp
│   └── build/
├── python/
│   ├── server.py
│   └── client.py
├── rust/
│   ├── Cargo.toml
│   ├── src/
│   │   ├── main.rs (server)
│   │   └── client.rs
│   └── target/
└── README.md
```

## Language Implementations

### C++ Implementation
- **Server Port**: 8080
- **Concurrency**: Multi-threaded using `std::thread`
- **Features**: Uses POSIX sockets with thread-per-connection model
- **Build System**: CMake

### Python Implementation
- **Server Port**: 6999
- **Concurrency**: Async/await using `asyncio`
- **Features**: Single-threaded async I/O
- **Runtime**: Python 3.7+

### Rust Implementation
- **Server Port**: 8080
- **Concurrency**: Async using Tokio runtime
- **Features**: Memory-safe async I/O with zero-cost abstractions
- **Runtime**: Tokio async runtime

## Prerequisites

### C++
- CMake 3.10+
- C++11 compatible compiler (GCC, Clang)
- POSIX-compliant system (Linux, macOS)

### Python
- Python 3.7+
- No additional dependencies (uses standard library)

### Rust
- Rust 1.75+ (2024 edition)
- Tokio 1.45.1 (specified in Cargo.toml)

## Building and Running

### C++

1. **Build the project:**
   ```bash
   cd c++
   mkdir -p build
   cd build
   cmake ..
   make
   ```

2. **Run the server:**
   ```bash
   ./server
   ```

3. **Run the client (in another terminal):**
   ```bash
   ./client
   ```

### Python

1. **Run the server:**
   ```bash
   cd python
   python server.py
   ```

2. **Run the client (in another terminal):**
   ```bash
   python client.py
   ```

### Rust

1. **Run the server:**
   ```bash
   cd rust
   cargo run --bin server
   ```

2. **Run the client (in another terminal):**
   ```bash
   cargo run --bin client
   ```

## Performance Testing

Each client implementation creates **10,000 concurrent connections** and measures:
- Total execution time
- Average latency per connection
- Throughput characteristics

### Test Protocol
1. Client sends 100 bytes of data
2. Server echoes the data back
3. Client receives the echoed data
4. Connection is closed
5. Timing metrics are calculated and displayed

## Expected Output Format

- **C++**: `C++: 10000 clients, total time = X ms, avg = Y μs`
- **Python**: `Python: 10000 clients, total time = X.XX ms, avg latency = Y.YYYY ms/client`
- **Rust**: `Rust: 10000 clients, total time = Xs, avg = Yμs`

## Performance Characteristics

### C++
- **Concurrency Model**: Thread-per-connection
- **Memory Usage**: Higher due to thread overhead
- **CPU Usage**: Can utilize multiple cores effectively
- **Typical Performance**: Fast, but limited by thread creation overhead

### Python
- **Concurrency Model**: Single-threaded async I/O
- **Memory Usage**: Lower memory footprint
- **CPU Usage**: Single-core bound
- **Typical Performance**: Good for I/O-bound workloads

### Rust
- **Concurrency Model**: Async tasks with work-stealing scheduler
- **Memory Usage**: Minimal overhead, zero-cost abstractions
- **CPU Usage**: Efficient multi-core utilization
- **Typical Performance**: Generally fastest with lowest resource usage

## Notes

- **Port Configuration**: Make sure the ports (8080 for C++/Rust, 6999 for Python) are available
- **System Limits**: You may need to increase system limits for file descriptors:
  ```bash
  ulimit -n 65536
  ```
- **Concurrent Connections**: The test creates 10,000 simultaneous connections, which may require system tuning for optimal performance

## Troubleshooting

### Common Issues

1. **"Address already in use" error**
   - Wait a few seconds for the socket to be released
   - Or use `SO_REUSEADDR` socket option

2. **"Too many open files" error**
   - Increase file descriptor limit: `ulimit -n 65536`

3. **Connection refused**
   - Ensure the server is running before starting the client
   - Check if the correct port is being used

## Contributing

Feel free to contribute additional language implementations or performance optimizations. Some ideas:
- Go implementation
- Node.js implementation
- Java implementation
- Performance profiling tools
- Benchmark result visualization

## License

This project is provided as-is for educational and benchmarking purposes.


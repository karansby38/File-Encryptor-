"# File-Encryptor-" 
# 🔐 Parallel File Encryptor

A high-performance file encryption tool built using **C++**, **POSIX processes**, and **shared memory**, designed to leverage parallelism for significantly faster encryption and decryption of large files.

## 🚀 Features

- 🔄 **Parallel Processing** using `fork()` for concurrent encryption of file chunks
- 🧠 **Shared Memory (shm_open, mmap)** to enable inter-process communication
- 🔄 **Circular Queue Implementation** in shared memory
- ⛓️ **POSIX Semaphores (sem_t)** for synchronization between producer and consumer processes
- 📊 **Performance Boost**: Achieved 10x+ speedup compared to sequential processing

---

## 🛠️ Tech Stack

- **Language**: C++
- **System APIs**: POSIX (`fork()`, `shm_open`, `mmap`, `sem_open`)
- **OS Concepts**: Process synchronization, shared memory, semaphores

---

---

## ⚙️ How It Works

1. **Parent Process**:
   - Splits the file into chunks
   - Produces data into a circular queue in shared memory

2. **Child Processes**:
   - Consume data from the queue
   - Perform encryption using a basic cipher (can be extended)
   - Write encrypted data to an output file

3. **Synchronization**:
   - Circular queue access controlled by `sem_t` semaphores
   - Prevents race conditions and ensures correct operation order

---

## 🧪 Performance

| Metric        | Sequential | Parallel |
|---------------|------------|----------|
| Time Taken    | 35.1 sec   | 3.2 sec  |
| Speedup       | –          | **10x+** |

---

## 📦 Installation

```bash
git clone https://github.com/karansby38/File-Encryptor-.git
cd File-Encryptor-
make



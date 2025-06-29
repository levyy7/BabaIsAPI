# BabaIsAPI

BabaIsAPI is a C++ re-implementation of the popular puzzle game Baba. Its main characteristic is that it exposes a REST API, allowing you to both play the game and retrieve real-time game data via HTTP requests. Whether you want to control the game interactively or integrate it into another system, BabaIsAPI gives you the flexibility to do so.

---

## Features

- **Multiple Modes of Play**  
  - **API Mode**: Run the game as a REST API server to issue commands and retrieve game state.
  - **Keyboard Mode**: Play interactively using keyboard input with a graphical window.
  - **NoWindow Mode**: Run the game headless (no window) for automated testing or server-side simulations.

- **REST API**  
  Expose endpoints to query the current game state, send move commands, and stream game events.

- **Cross-Platform Build**  
  Build the project using CMake. Full support for Visual Studio 2022 is provided.

---


## 🚀 Docker Image (Recommended)

The recommended way to use BabaIsAPI in headless API mode is via Docker. A prebuilt image is available on Docker Hub:

- **Image**: [`levyy7/babaisapi`](https://hub.docker.com/r/levyy7/babaisapi)

### Example Usage

```bash
docker run -p 8080:8080 levyy7/babaisapi
```

## Manual Installation

### Prerequisites

- **C++ Compiler**: A C++20-compliant compiler.
- **CMake**: Version 3.15 or later.
- **Visual Studio 2022** (optional): For building on Windows.

### Cloning the Repository

```bash
git clone https://github.com/yourusername/BabaIsAPI.git
cd BabaIsAPI
```

---

## Building the Project

### Using CMake (Cross-Platform)

1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

2. Configure the project:
   ```bash
   cmake ..
   ```

3. Build the executable:
   ```bash
   cmake --build .
   ```

### Using Visual Studio 2022

1. Open the project folder in Visual Studio 2022.
2. Visual Studio will detect the `CMakeLists.txt` file and configure the project.
3. Build the project directly from the IDE.

---

## Usage

The executable accepts command-line arguments to determine the mode of operation:

- `-mode {api, keyboard, nowindow}`  
  Select the mode in which to run the game:
  - **api**: Run in REST API mode.
  - **keyboard**: Run in interactive mode using keyboard input with a window.
  - **nowindow**: Run headless (no window).

- `-port [numport]` (Optional)  
  Specify the port number for the REST API server. Defaults to `8080` if not provided.

### Example Commands

- **Run in API Mode on Default Port (8080):**
  ```bash
  BabaIsAPI -mode api
  ```

- **Run in API Mode on a Custom Port (e.g., 3000):**
  ```bash
  BabaIsAPI -mode api -port 3000
  ```

- **Run in Keyboard Mode:**
  ```bash
  BabaIsAPI -mode keyboard
  ```

- **Run in Headless Mode (No Window):**
  ```bash
  BabaIsAPI -mode nowindow
  ```

---

## REST API Overview

When running in API mode, BabaIsAPI starts an HTTP server that exposes the following endpoints:

### **Retrieve Game State**
- **GET /state**
  - Returns the current state of the game, including level info, board layout, and active rules.

### **Move Commands**
- **POST /move/{direction}**
  - Sends a move command to the game.
  - Directions: up | down | left | right | still

### **Level Commands**
- **POST /level**
  - Sets the active level of the game.
  - You can select the level either by de level name or level id.

*Note*: For full details on API endpoints and request/response formats, refer to the API documentation.

---

## Contributing

Contributions are welcome! If you’d like to improve or add new features, please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.


---

## Acknowledgements

- Thanks to Arvi Teikari for making the incredible game of Baba Is You

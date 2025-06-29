FROM ubuntu:22.04

# Set build-time port (can be overridden during build)
ARG PORT=8080
ENV PORT=${PORT}

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    zip \
    unzip \
    git \
    ninja-build \
    pkg-config \
    cmake

RUN apt-get update && apt-get install -y \
    libx11-dev \
    libxi-dev \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libgl1-mesa-dev

# Set working directory
WORKDIR /app

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh

# Copy source code
COPY . .

# Install dependencies using vcpkg.json
RUN ./vcpkg/vcpkg install

# Build the app
RUN cmake -B build -S . \
    -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release

# Expose the port
EXPOSE ${PORT}

# Default command; can be overridden with `docker run`
CMD ["sh", "-c", "./build/src/BabaIsAPI -headless -port $PORT"]

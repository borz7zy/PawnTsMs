FROM ubuntu:18.04

RUN dpkg --add-architecture i386 && \
	apt-get update && \
	apt-get install -y \
	build-essential \
	libssl-dev \
	gcc \
	g++ \
	make \
	wget \
	gcc-multilib \
	g++-multilib \
	lib32gcc1 \
	libicu-dev:i386 \
	libbz2-dev:i386 \
	zlib1g-dev:i386 \
	libc6-dev-i386 \
	clang-10 \
	libc6:i386 \
	libstdc++6:i386 && \
	apt-get clean && \
	rm -rf /var/lib/apt/lists/*

ENV CC=/usr/bin/clang-10 \
	CXX=/usr/bin/clang++-10 \
	PATH=~/.local/bin:${PATH}

WORKDIR /cmake_build
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.8/cmake-3.19.8.tar.gz
RUN tar -xzf cmake-3.19.8.tar.gz && cd cmake-3.19.8 && \
	./bootstrap -- -DCMAKE_USE_OPENSSL=OFF && \
	make -j$(nproc) && \
	make install

WORKDIR /project
COPY . .

RUN mkdir build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-m32 -w -fPIC -static-libgcc -static-libstdc++" && \
	cmake --build .

RUN file build/pawn_ts_ms.so

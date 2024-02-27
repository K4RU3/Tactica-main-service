FROM gcc:latest

# 必要なパッケージのインストール
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    build-essential \
    libssl-dev \
    gfortran \
    libcoarrays-dev:amd64 \
    libcoarrays-openmpi-dev:amd64 \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN gcc app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -I./app/lib -lboost_system

CMD ["./main"]

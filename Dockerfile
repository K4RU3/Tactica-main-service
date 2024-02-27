FROM gcc:latest

# 必要なパッケージのインストール
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    build-essential \
    libssl-dev \
    gfortran \   # 追加
    libcoarrays-dev:amd64 \   # 追加
    libcoarrays-openmpi-dev:amd64 \   # 追加
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN gcc app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -I./app/lib -lboost_system

CMD ["./main"]

FROM debian:latest

# 必要なパッケージのインストール
RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y \
    g++ \
    libssl-dev \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN g++ app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -I./app/lib -lboost_system

CMD ["./main"]

FROM gcc:latest

# 必要なパッケージのインストール
RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y \
    libssl-dev \
    gfortran \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get install -y libboost-all-dev

COPY . .

RUN gcc app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -I./app/lib -lboost_system

CMD ["./main"]

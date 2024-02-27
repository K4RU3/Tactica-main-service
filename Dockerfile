FROM gcc:latest

# boost
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN apt-get update && apt-get install -y libssl-dev

RUN gcc app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -I./app/lib -lboost_system

CMD ["./main"]

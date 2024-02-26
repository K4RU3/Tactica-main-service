FROM gcc:latest

COPY . .

RUN apt-get update && apt-get install -y libssl-dev

RUN gcc app/main.cpp -o main -lstdc++ -std=c++20 -mavx2 -L./app/lib

CMD ["./main"]
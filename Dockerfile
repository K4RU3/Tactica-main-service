FROM gcr.io/cloudrun/debian:11

RUN apt-get update && apt-get install -y build-essential

COPY . /app

RUN cd /app && g++ main.cpp -o server -std=c++17 -lboost_system -lboost_thread -lboost_asio -lboost_beast

CMD ["./server"]
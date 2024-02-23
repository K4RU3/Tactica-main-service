FROM gcc:latest

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y libssl-dev

RUN gcc main.cpp -o main -lstdc++

CMD ["./main"]
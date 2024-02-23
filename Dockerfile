FROM gcc:latest

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y libssl-dev

RUN gcc app/main.cpp -o main -lstdc++

CMD ["./main"]
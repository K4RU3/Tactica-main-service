FROM gcr.io/cloudrun/debian:11

RUN apt-get update && apt-get install -y build-essential

COPY . /app

RUN cd /app && g++ ./app/main.cpp -o main -lstdc++

CMD ["./main"]
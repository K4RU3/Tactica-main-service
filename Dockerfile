FROM gcc:latest

COPY package*.json ./

COPY . ./

RUN g++ -o main main.cpp

CMD [ "./main" ]
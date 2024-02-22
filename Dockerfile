FROM node:lts-slim

ENV PORT 8080

COPY package*.json ./

RUN npm install --only=production

COPY . ./

CMD [ "npm", "start" ]
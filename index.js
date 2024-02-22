import express from "express"
const app = express();

app.get('/', (req, res) => {
  res.send("hello world")
});

const port = parseInt(process.env.PORT) || 8080;
app.listen(port, () => {
  console.log(`helloworld: listening on port ${port}`);
});
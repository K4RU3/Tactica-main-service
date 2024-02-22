import express from "express"
const app = express();

app.get('/', (req, res) => {
  res.send("盛者必衰の理を表す")
});

const port = parseInt(process.env.PORT) || 8080;
app.listen(port, () => {
  console.log(`helloworld: listening on port ${port}`);
});
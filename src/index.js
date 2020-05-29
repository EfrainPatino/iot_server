const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const routesV1 = require('./routes/index');
const cors = require('cors');
const fs = require('fs');

const quantity_nodes = 3;

const PORT = 5000;

for (i=1; i <= quantity_nodes; i++ ) {
let rawdata = fs.readFileSync(`secretID_${i}.json`);
let status = JSON.parse(rawdata);
console.log(status);
}

const app = express();
app.use(cors()); 

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json())

routesV1(app);

app.listen(PORT, () => {
    console.log(`Running on: ${PORT}`)
});

app.get('/', function(req, res) { //Ruta que envia el HTML
    res.sendFile(path.join(__dirname + '/Public/index.html'));    
});



 





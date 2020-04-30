const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const routesV1 = require('./routes/index');
const cors = require('cors');

const PORT = 4000;

const app = express();
app.use(cors()); 

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json())

routesV1(app);

app.listen(PORT, () => {
    console.log(`corriendo en: ${PORT}`)
});

 app.get('/', function(req, res) { //Ruta que envia el HTML
         res.sendFile(path.join(__dirname + '/index.html'));
     });



const {DbWrite} = require('../middlewares/DB') 
const fs = require('fs');
var state = '';

const TurnOn = (req, res) => {
  state = req.body
  console.log(state);
  try {
    res.send({status: 'OK', data: 'on', message: 'TurnOn'});
    DbWrite(state)
  } catch (e) {
    console.log(e)
    res.status(500).send({status: 'ERROR SENDING DATA', message: e.message});
  }
};

const TurnOff = (req, res) => {
  state = req.body
  console.log(state);
  try {
    res.send({status: 'OK', data: 'off', message: 'TurnOff'});
    DbWrite(state)
  } catch (e) {
    console.log(e)
    res.status(500).send({status: 'ERROR SENDING DATA', message: e.message});
  }
};

const Refresh = (req,res) => {
  espID = req.body.espID
  let rawdata = fs.readFileSync(`${espID}.json`);
  let status = JSON.parse(rawdata);
  res.send(status);
  console.log(req.body)
}

module.exports = {
  TurnOn,
  TurnOff,
  Refresh
};

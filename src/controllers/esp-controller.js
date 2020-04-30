var espState = false;

const TurnOn = (req, res) => {
  const {espID} = req.body;
  console.log(req.body);
  if ( espID == 'secretID') {
    try {
      res.send({status: 'OK', data: 'on', message: 'TurnOn'});
      espState = true;
      console.log(espState);
    } catch (e) {
      res.status(500).send({status: 'ERROR SENDING DATA', message: e.message});
    }
  } else {
    res.status(500).send({status: 'ERROR', message: 'Invalid secretID'});
  }
};

const TurnOff = (req, res) => {
  const {espID} = req.body;
  console.log(req.body);
  if ( espID == 'secretID') {
    try {
      res.send({status: 'OK', data: 'off', message: 'TurnOff'});
      espState = false;
      console.log(espState);
    } catch (e) {
      console.log(e)
      res.status(500).send({status: 'ERROR SENDING DATA', message: e.message});
    }
  } else {
    res.status(500).send({status: 'ERROR', message: 'Invalid secretID'});
  }
};

const Refresh = (req,res) => {
  const {espID, state} = req.body;
  res.send({status: 'OK', esp_01: espState, esp_02: 'true', esp_03: 'true'});
  console.log(espState);
}


module.exports = {
  TurnOn,
  TurnOff,
  Refresh
};

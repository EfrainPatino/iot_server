const express = require('express');
const esp_controller = require('../controllers/esp-controller');
const { isAuth } = require('../middlewares/auth');
const router = express.Router();

router.post('/turnon', isAuth, esp_controller.TurnOn);
router.post('/turnoff', isAuth, esp_controller.TurnOff);
router.post('/refresh', isAuth, esp_controller.Refresh);

module.exports = router;

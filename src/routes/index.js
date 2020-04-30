const esp_routes = require('./esp-routes');

module.exports = app => {
  app.use('/api/esp', esp_routes);
  
};

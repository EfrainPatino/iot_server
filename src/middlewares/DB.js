var fs = require('fs')

const DbWrite = (inputStatus) => {
  var status = JSON.stringify(inputStatus);
  
  fs.writeFile(`../data/${inputStatus.espID}.json`, status, 'utf8', function (err) {
      if (err) {
          console.log("An error occured while writing JSON Object to File.");
          return console.log(err);
      }
      console.log("JSON file has been saved.");
  });
  }

module.exports = { DbWrite };
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://elidow:Crosscountry5@cluster0-16lug.mongodb.net/test?retryWrites=true&w=majority";

MongoClient.connect(url, function(err, db) {

  if (err) throw err;
  var dbo = db.db("MongoHW");

  var readline = require('readline');
  var fs = require('fs');

  var myInterface = readline.createInterface({
  input: fs.createReadStream("companies.csv")
  });

  var comma = 0;

  var str = "";

  myInterface.on('line', function (line) {
      for(var i = 0; i < line.length; i++)
            if(line[i] == ",")
                comma = i;
  
        str += '{ "title": "' + line.substring(0,comma)
             + '", "user": "' + line.substring(comma+1) + '"}';
        var obj = JSON.parse(str);
        dbo.collection("companies").insertOne(obj, function(err, res) {
              if (err) throw err;
              console.log("1 doc inserted");
              db.close();
            });
        str = "";
  });
    
});
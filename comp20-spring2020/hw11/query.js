var http = require('http');
var url = require('url');

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});

    var qobj = url.parse(req.url, true).query;
    var type = qobj.type;
    var input = qobj.input;
    
    var MongoClient = require('mongodb').MongoClient;
    var url2 = "mongodb+srv://elidow:Crosscountry5@cluster0-16lug.mongodb.net/test?retryWrites=true&w=majority";

    MongoClient.connect(url2, function(err, db) {
        if (err) throw err;
        var dbo = db.db("MongoHW");

        if(type == "ticker")
        {
            var query = { ticker: input };
            dbo.collection("companies").find(query).toArray(function(err, result) {
            if (err) throw err;
            if(result.length == 0) {
                res.write("Ticker Not Found");
            }
            else {
                var comp = "The company of ticker " + input + " is: " + result[0].company;
                res.write(comp);
            }
            //res.write("here: " + JSON.stringify(result));
            res.end();
            db.close();
            });
        }
        else if (type == "company")
        {
            var query = { company : input };
            dbo.collection("companies").find(query).toArray(function(err, result) {
            if (err) throw err;
            if(result.length == 0) {
                res.write("Company Not Found");
            }
            else {
                var ticker = "The ticker of company " + input + " is: " + result[0].ticker;
                res.write(ticker);
            }

            res.end();
            db.close();
            });
        }
      });

}).listen(8080);
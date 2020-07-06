var http = require('http');
var fs = require('fs');

http.createServer(function(req, res) {
	res.writeHead(200, { 'Content-Type': 'text/html' });
	// your code here
	fs.readFile('part4.html', function(err, data){
		res.write(data);	
	  	res.end();
	});
}).listen(3000);

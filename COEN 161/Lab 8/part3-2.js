var http = require('http');

http.createServer(function(req, res) {
	const MAX = 6;
	res.writeHead(200, { 'Content-Type': 'text/html' });

	res.write('<table border="1">');	
	// your code here
	for(var i = 1; i<= MAX; i++){
		res.write('<tr>');
		for(var j=1; j<= MAX; j++){
			res.write('<td>' + i + " * " + j + " = " + (i*j) + '</td>');
		}
		res.write('</tr>');
	}
	res.write('</table>');	
  res.end();
}).listen(3000);

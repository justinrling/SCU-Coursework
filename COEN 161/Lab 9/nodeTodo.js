const fs = require('fs');

exports.handleTodoList = function(req, res, session) {
  switch(req.method) {
    case "GET":
      //get current todoList (from session object)
        var todoList = [];

        fs.readFile('./sessions/' + session.id, function(err, data){
          if(err){
            res.writeHead(500, {'Content-Type': 'text/html'});
            return res.end("500 Internal Server Error");
          }

          session = JSON.parse(data);

          for(var i=0;i<session.todoList.length; i++){
            todoList.push({id: i, description: session.todoList[i]});
          }
          
          res.writeHead(200, {'Content-Type': 'application/json'});

          
          //In addition to using JSON.stringify,
          //format JSON using .map() function on todoList
          res.end(JSON.stringify(todoList));
        });

      break;
    case "POST":
      //check if session already has a todoList, if not create it
      if(!session.todoList){
        session.todoList = new Array();
      }
      //call convert request to get data
      convertRequest(req, function(data){
        session.todoList.push(data.todo);
        console.log(session.todoList);
        fs.writeFile('./sessions/' + session.id, JSON.stringify(session), function(err){
          if(err){
            res.writeHead(500, {'Content-Type': 'text/html'});
            return res.end("500 Internal Server Error");
          }
          res.writeHead(200, 'OK');
          res.end();
        });
      });

      break;
    default:
      res.writeHead(405, {'Allow': 'GET, POST'});
      res.end("Not Allowed");
  }
};

/*
  converts the HTTP POST request body into a JSON object
*/
function convertRequest(req, callback) {
  let data = "";
  req.on('data', chunk => {
    data += chunk.toString();
  });
  req.on('end', () => {
    callback(JSON.parse(data));
  });
}
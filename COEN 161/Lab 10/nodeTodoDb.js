const mysql = require('mysql');

// fill in your db credentials
const config = {
  host: "dbserver.engr.scu.edu",
  user: "",
  password: "",
  database: ""
};

exports.addTodo = function (sessionId, todo, callback) {
  const con = mysql.createConnection(config);
  // call con.connect();
  con.connect(function(err){
    if(err) return callback(err);
    console.long("Connected!");

    var sql = "INSERT INTO Todos (sessionId, description) VALUES (?,?);";
    con.query(sql, [sessionId, todo], function(err, result){
      console.log("1 record inserted");
      return callback(err);
  });
  con.end();
});
}

exports.getTodos = function (sessionId, callback) {
  const con = mysql.createConnection(config);
  // call con.connect();  

  con.connect(function(err){
    if(err){return callback(err)};
    console.log("Connected");
    var sql = "SELECT * FROM Todos WHERE sessionId = ?;";
    con.query(sql, [sessionId], function(err, result){
      if(err){return callback(err)};
      return callback(err, result);
    });
    con.end();
  });
};
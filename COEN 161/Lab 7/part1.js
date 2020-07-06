(function () {
	var resources = "http://students.engr.scu.edu/~adiaztos/resources/";
	
	// Create an XMLHttpRequest object
	var request1 = new XMLHttpRequest();
	// Handle succesful responses
	request1.onreadystatechange = function(){
		if(this.readyState == 4 && this.status == 200){
			document.getElementById("sample1").innerHTML = this.responseText;
		}
	};

	// Get sample1.php
	request1.open("GET", "http://students.engr.scu.edu/~adiaztos/resources/sample1.php", true);
	request1.send();

	// Create an XMLHttpRequest object
	var request2 = new XMLHttpRequest();
	
	// Handle succesful responses
	request2.onreadystatechange = function(){
		if(this.readyState == 4 && this.status == 200){
			document.getElementById("sample2").innerHTML = this.responseText;
		}
	};

	// Get sample2.php
	request2.open("GET", "http://students.engr.scu.edu/~adiaztos/resources/sample2.php", true);
	request2.send();

	// Create an XMLHttpRequest object
	var request3 = new XMLHttpRequest();

	// Handle succesful responses
	request3.onreadystatechange = function(){
		if(this.readyState == 4 && this.status == 200){
			var response = JSON.parse(this.responseText);
			response = response.friends;
			var ul = document.createElement("UL");
			for(var i=0; i<response.length; i++){
				var li = document.createElement("LI");
				var txt = document.createTextNode(response[i].name);
				li.appendChild(txt);
				ul.appendChild(li);
			}
			document.getElementById("sample3").appendChild(ul);
		}
	}

	// Get sample3.php
	request3.open("GET", "http://students.engr.scu.edu/~adiaztos/resources/sample3.php", true);
	request3.send();

})();
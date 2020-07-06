(function () {
	var template = document.getElementById("template");

	// remove template from the page, since it is only a template
	var parent = template.parentNode;
	parent.removeChild(template);

	// Create an XMLHttpRequest object
	var request = new XMLHttpRequest();

	// Set onreadystatechange
	request.onreadystatechange = function(){
		if(this.readyState == 4 && this.status == 200){
			var response = JSON.parse(this.responseText);
			populateContacts(response);
		}
	}

	// Open and send requests
	request.open("GET", "http://students.engr.scu.edu/~adiaztos/resources/contacts.php", true);
	request.send();

	// This function takes the list of contacts and clones a new element from the template with the value of each contact
	function populateContacts(contacts) {
		for(var i=0; i<contacts.length; i++){
			var node = template.cloneNode(true);
			node.id = contacts[i].id;
			node.querySelector("#index").innerHTML = i+1;
			node.querySelector("#index").setAttribute("id", node.id + (i+1));
			node.querySelector("input[name='name']").value = contacts[i].name;
			node.querySelector("input[name='email']").value = contacts[i].email;
			parent.appendChild(node);
		}	
	}

	// submits a request with the search query for the filtered list of contacts
	function search() {
		// clear the current contacts list
		while (parent.lastChild)
			parent.removeChild(parent.lastChild);
		
		var search = document.getElementById("searchField").value;
		request.open("POST", "http://students.engr.scu.edu/~adiaztos/resources/contacts.php?query=" + search, true);
		request.send();
	}

	// assign the search function as the click handler for search button
	document.getElementById("searchBtn").addEventListener("click", search);
})();
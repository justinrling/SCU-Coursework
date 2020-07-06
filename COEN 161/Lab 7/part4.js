(function () {
	var resources = "http://students.engr.scu.edu/~adiaztos/resources/";

	// Load sample1.php
	$("#sample1").load(resources+"sample1.php");
	// Load sample2.php
	$("#sample2").load(resources+"sample2.php");
	// Get sample3.php
	$.get(resources+"sample3.php", function(data){
		var list = $("<ul></ul>");
		response = JSON.parse(data);
		response = response.friends;

		for(var i=0; i<response.length; i++){
			var li = $("<li></li>").text(response[i].name);
			list.append(li); 
		}
		$("#sample3").append(list);
	})

})();
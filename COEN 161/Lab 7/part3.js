(function () {
	// Add the click handler for the button
	$("button").click(function(){
		var text = $("#myInput").val();

		$("#allUpper").text(text.toUpperCase());
		$("#allLower").text(text.toLowerCase());
		$("#redText").text(text).css("color", "red");
		$("#flashyText").text(text).addClass("flashy");
	})
})();
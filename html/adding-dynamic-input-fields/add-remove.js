$(document).ready(function() {
	$('#add').click(function() {
		var inp = $('#box');
		var i = $('input').size() + 1;
		$('<div id="box' + i +'"><input type="text" id="name" class="name" name="name' + i +'" placeholder="Input '+i+'"/><a class="add" id="remove">Remove</a> </div>').appendTo(inp);
		i++;
	});

	$('body').on('click', '#remove', function() {
		$(this).parent('div').remove();
	});
});

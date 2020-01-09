// JavaScript Document

$(document).ready(function(){
/*setTimeout(function(){
	$('#cboxOverlay').css('display', 'none');
	$('#cboxOverlay').hide();
	}, 3000);*/
	
	$('.category-menu').click(function(){
        var id = $(this).attr('id');
		if ($(this).hasClass('active')) {
			$('.'+id).hide();
			$(this).removeClass('active');
		} else {
			$('.'+id).show();
			$(this).addClass('active');
		}
    });
	
	$('.category-menu').each(function(){
		if (!$(this).hasClass('active')) {
			var id = $(this).attr('id');
			$('.'+id).hide();
		}
	});
});


var d = document;
var winIE = (navigator.userAgent.indexOf("Opera")==-1 && (d.getElementById && d.documentElement.behaviorUrns)) ? true : false;
function bodySize()
{
	if(winIE && d.documentElement.clientWidth) 
	{
		sObj = d.getElementsByTagName("body")[0].style;
		sObj.width = (d.documentElement.clientWidth<1000) ? "1000px" : "auto";
		
	}
 }

 function init()
 {
	if(winIE) { bodySize(); }
 }
 onload = init;
 if(winIE) { onresize = bodySize; }
 
 
 
function AdvShower(divId) {
var id = document.getElementById(divId);
if (id.style.display == "none") {
eval("id.style.display = 'block'");
$('#'+divId).parent().addClass('activ');
} else {
eval("id.style.display = 'none'");
$('#'+divId).parent().removeClass('activ');
}


}

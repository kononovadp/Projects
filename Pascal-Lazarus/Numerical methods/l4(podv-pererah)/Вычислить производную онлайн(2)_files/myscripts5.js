jQuery.noConflict();
(function($) { 
$(document).ready(function() {

/*Определение браузера*/
function getNameBrouser() {
 var ua = navigator.userAgent.toLowerCase();
 // Определим Internet Explorer
 if (ua.indexOf("msie") != -1 && ua.indexOf("opera") == -1 && ua.indexOf("webtv") == -1) {
   return "msie"
 }
 // Opera
 if (ua.indexOf("opera") != -1) {
   return "opera"
 }
 // Gecko = Mozilla + Firefox + Netscape
 if (ua.indexOf("gecko") != -1) {
   return "gecko";
 }
 // Safari, используется в MAC OS
 if (ua.indexOf("safari") != -1) {
   return "safari";
 }
 // Konqueror, используется в UNIX-системах
 if (ua.indexOf("konqueror") != -1) {
   return "konqueror";
 }
 return "unknown";
} 

/*Модуль авторизации*/
$("#modlgn_username").blur(function(){
	if ($("#modlgn_password").val()!='*******') $("#modlgn_password").css('color','#333333');
});

/*Стили формы class modern*/
$start_url="/templates/it_thestore3/css/form_modern/";

/*Поле select*/
$soderz=$("form.modern select");
$soderz.css('opacity','0');
$soderz.each(function(){
	$shirina_def=258;
	$shir=$shirina_def+"px";
	$input_content="- Выберите из списка -"; /*Для страховки*/
	$(this).children().each(function () {if(this.selected) $input_content= $(this).html()});
	$style=$(this).css("width");
	per=/(\d+)px/;
	$poisk=$style.match(per);
	if ($poisk!=null) {$poisk_num=parseInt($poisk[1],10); $width=($poisk_num+2)+'px';$width_div=($poisk_num+2-29)+'px'} else {$(this).css("width",$shir);$width=$shir;$width_div=($shirina_def-29)+'px'};/*Где 2-ширина border в css для select, 29 - ширина картинок*/

	$(this).before('<div id="arrow_picture" style="position:absolute;display:inline;height:21px;z-index:0;background:url('+$start_url+'select4.gif) no-repeat right;padding:0;margin:0;width:'+$width+'"><div style="position: absolute;height:21px;background:url('+$start_url+'select2.gif) no-repeat left;padding:0;margin:0;width:'+$width+'"><div style="position: absolute;height:21px;background:url('+$start_url+'select3.gif) repeat-x;padding:0;margin:0;margin-left:8px;overflow:hidden;white-space:nowrap;width:'+$width_div+'" id="iput_modern">'+$input_content+'</div></div></div>');	
});




$soderz.change(function () {
chek_option(this);
});

function chek_option (item) {
$(item.children).each(function () {
if(this.selected) {
	$input_content= $(this).html();
	$parent_div=$(this).parent().parent();
	$child_div=$parent_div.children("div").children("div").children("div#iput_modern");
	$child_div.html($input_content);}
}); 
}

$soderz.hover(function(){$(this).parent().children('div#arrow_picture').css('background','url('+$start_url+'select4_hover.gif) no-repeat right')}, function(){$(this).parent().children('div#arrow_picture').css('background','url('+$start_url+'select4.gif) no-repeat right')});


/*Для поля input типа "file"*/
$shirina2_def=200;
$soderz2=$("form.modern input[type='file']");
$soderz2.css({'opacity':'0','position':'absolute','right':'0px','height':'21px','cursor':'default',
'font-size':'25px'}); /*Шрифт для того чтобы кнопка была большая!*/
$soderz2.each(function(){
	if ($(this).is('input[shirina*="px"]')) {
		per2=/(\d+)px/;;
		$poisk2=$(this).attr('shirina').match(per2);
		if ($poisk2 !=null) {$shir2=$poisk2[1]+"px";$width2=(parseInt($poisk2[1],10)+72)+"px"} else
							{$shir2=$shirina2_def+"px";$width2=($shirina2_def+72)+"px";}
		
		} else {$shir2=$shirina2_def+"px";$width2=($shirina2_def+72)+"px";};
	$(this).wrap('<div style="position:relative;overflow:hidden;white-space: nowrap;width:'+$width2+';height:21px;"></div>');
	$(this).before('<div id="obzor_but" style="text-align:center;color:#fff;font-weight:bold;width:72px;height:21px;background:url('+$start_url+'obzor.gif) no-repeat right;position:absolute;z-index:0;right:0px">Обзор...</div><div style="right:72px;height:21px;width:20px;position:absolute;z-index:3;background:url('+$start_url+'proz.png) left no-repeat"></div><div style="text-align:center;right:72px;height:21px;width:'+$shir2+';position:absolute;z-index:2;overflow:hidden;white-space:nowrap;font-weight:bold;font-size:11px;padding-top:2px;" id="file_input">файл не выбран</div>');
	
});
	

$soderz2.change(function () {
	$input_content2=$(this).val();
	reWin = /.*\\(.*)/;
	$input_content2 = $input_content2.replace(reWin, "$1"); //выдираем название файла для windows
    reUnix = /.*\/(.*)/;
    $input_content2 = $input_content2.replace(reUnix, "$1"); //выдираем название файл для unix
	$file_div=$(this).parent().children('div#file_input');
	$file_div.html($input_content2);
	RegExExt =/.*\.(.*)/;
	var ext = $input_content2.replace(RegExExt, "$1");//определяем расширение
	if (ext){
				var icon;
                switch (ext.toLowerCase())
                {
                    case 'doc': icon = 'doc.png'; break;
					case 'docx': icon = 'docx.png'; break;
					case 'app': icon = 'app.png'; break;
                    case 'bmp': icon = 'bmp.png'; break;  
					case 'cr2': icon = 'cr2.png'; break;  
					case 'eps': icon = 'eps.png'; break;    
					case 'img': icon = 'img.png'; break;   
					case 'inf': icon = 'inf.png'; break;  
					case 'iso': icon = 'iso.png'; break;     
					case 'isz': icon = 'isz.png'; break;     
					case 'jfif': icon = 'jpe-jpeg-jpg.png'; break;
                    case 'jpg': icon = 'jpe-jpeg-jpg.png'; break;
                    case 'jpeg': icon = 'jpe-jpeg-jpg.png'; break;
					case 'jpe': icon = 'jpe-jpeg-jpg.png'; break;
					case 'mdf': icon = 'mdf.png'; break;
					case 'mds': icon = 'mds.png'; break;
					case 'mid': icon = 'mid-midi-rmi.png'; break;
					case 'midi': icon = 'mid-midi-rmi.png'; break;
					case 'rmi': icon = 'mid-midi-rmi.png'; break;
                    case 'png': icon = 'png.png'; break;
                    case 'gif': icon = 'gif.png'; break;
                    case 'pdf': icon = 'pdf.png'; break;
					case 'sys': icon = 'sys.png'; break;
                    case 'wav': icon = 'm4a-mp2-wav.png'; break;
					case 'mp2': icon = 'm4a-mp2-wav.png'; break;
                    case 'm4a': icon = 'm4a-mp2-wav.png'; break;
                    case 'xls': icon = 'xls.png'; break;
					case 'xlsx': icon = 'xlsx.png'; break;
                    case 'avi': icon = 'avi.png'; break;
                    case 'wmv': icon = 'avi.png'; break;
                    case 'mp4': icon = 'mp4.png'; break;
                    case 'xml': icon = 'xml.png'; break;
                    case 'exe': icon = 'exe.ico'; break;
                    case 'txt': icon = 'txt.png'; break;
					case 'js': icon = 'js.ico'; break;
					case 'css': icon = 'css.ico'; break;
					case 'php': icon = 'js.ico'; break;
					case 'rar': icon = 'rar.ico'; break;
					case 'gz': icon = 'rar.ico'; break;
					case 'tar.gz': icon = 'rar.ico'; break;
					case 'zip': icon = 'rar.ico'; break;
					case 'flv': icon = 'flv.ico'; break;
					case 'aac': icon = 'aac.ico'; break;
					case 'wma': icon = 'wma.ico'; break;
					case 'mp3': icon = 'mp3.ico'; break;
					case 'psd': icon = 'psd.ico'; break;
					case 'htm': icon = 'html.ico'; break;
					case 'html': icon = 'html.ico'; break;
					case 'djvu': icon = 'djvu.ico'; break;
                    default: icon = 'default.ico'; break;
                };
				$file_div.html('<img style="vertical-align: top;" src="'+$start_url+'icons/'+icon+'"></img> '+$input_content2);
  
            };
});


$soderz2.hover(function(){$(this).parent().children('div#obzor_but').css('background','url('+$start_url+'obzor_hover.gif) no-repeat right')}, function(){$(this).parent().children('div#obzor_but').css('background','url('+$start_url+'obzor.gif) no-repeat right')});

/*Submit modern*/
$soderz3=$("form.modern input[type='submit']");
$soderz3.css({'height':'21px','position':'relative','z-index':'2','font-size':'21px','opacity':'0'});
$soderz3.each(function(){	

	$(this).wrap('<div style="position: relative;display:inline-block;height:21px;min-width:32px"></div>');
	$(this).before('<div style="width:16px;height:21px;position:absolute;left:0px;display:inline-block;background:url('+$start_url+'left.gif) no-repeat left" id="block1"><div style="position:absolute;white-space:nowrap;left:16px;min-width:10px;height:21px;background:url('+$start_url+'fon.gif) repeat-x;color:#ffffff;font-weight:bold;" id="submit_but"><div style="position:absolute;right:-16px;width:16px;height:21px;background:url('+$start_url+'right.gif) no-repeat right" id="block2"></div>'+$(this).val()+'</div></div>');	
	$popravka=$(this).parent().children().children("div#submit_but");
	$sa=$popravka.css('width');
	per3=/(\d+)px/;
	$poisk=$sa.match(per3);
	if ($poisk!=null) {$poisk_num=parseInt($poisk[1],10);$popravka1=($poisk_num+32)+'px';};
	$(this).css('width',$popravka1);
});

$soderz3.hover(function(){
	$(this).parent().children().children("div#submit_but").css('background','url('+$start_url+'fon_hover.gif) repeat-x');
	$(this).parent().children().children().children("div#block2").css('background','url('+$start_url+'right_hover.gif) no-repeat right');
	$(this).parent().children("div#block1").css('background','url('+$start_url+'left_hover.gif) no-repeat left')}, 
	function(){
	$(this).parent().children().children("div#submit_but").css('background','url('+$start_url+'fon.gif)');
	$(this).parent().children().children().children("div#block2").css('background','url('+$start_url+'right.gif) no-repeat right');
	$(this).parent().children("div#block1").css('background','url('+$start_url+'left.gif) no-repeat left')});
	
/*JS Calendar*/
$soderz4=$('form.modern input#calendar_input');
$soderz4.css({'width':'105px','cursor':'default','padding-right':'20px','background':'url('+$start_url+'calendar1.gif) no-repeat right 1px'});
$soderz4.each(function(){
	$(this).after('<script type="text/javascript"> Calendar.setup({inputField : "calendar_input",trigger : "calendar_input",onSelect : function() { this.hide() },showTime : 24,dateFormat : "%d/%m/%Y   %H:%M"}); </script>');
});
$soderz4.hover(
	function(){
		$(this).css({'background':'url('+$start_url+'calendar2.gif) no-repeat right 1px'})},
	function(){
		$(this).css({'background':'url('+$start_url+'calendar1.gif) no-repeat right 1px'})}
);
/*ClickToShow*/
	$(".ClickShown").hide();
$(".ClickShown[hide='no']").show();
$(".ClickToShow").toggle(function() {father_id=$(this).attr('id');$(".ClickShown[id='"+father_id+"']").show();},
						 function() {father_id=$(this).attr('id');$(".ClickShown[id='"+father_id+"']").hide();});
		
/*pay_method*/
//$("#moneybookers_tr").hide();
function chek_option2 (item) {
	$(item.children).each(function () {
		if(this.selected) {
			$a=$(this).val();
		}
	});
	return $a;
}; 
$("select[name='pay_method']").each(function() {
	if (chek_option2(this)=="webmoney") {$("#moneybookers_tr").hide();$(this).parent().css({'background':'url(/images/css/main/webmoney.gif) no-repeat 60% 7px'});};
	if (chek_option2(this)=="moneybookers") {$("#webmoney_tr").hide();$(this).parent().css({'background':'url(/images/css/main/moneybookers.gif) no-repeat 60% 7px'});};
});
$("select[name='pay_method']").change(function() {
	if (chek_option2(this)=="webmoney") {$("#moneybookers_tr").hide();$("#webmoney_tr").show();$("#moneybookers_tr").hide();$(this).parent().css({'background':'url(/images/css/main/webmoney.gif) no-repeat 60% 7px'});};
	if (chek_option2(this)=="moneybookers") {$("#webmoney_tr").hide();$("#moneybookers_tr").show();$(this).parent().css({'background':'url(/images/css/main/moneybookers.gif) no-repeat 60% 7px'});};
});
$("select[name='webmoney_type']").each(function() {
	if (chek_option2(this)=="wmr") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'R.gif) 0 0 no-repeat'})};
	if (chek_option2(this)=="wmz") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'Z.gif) 0 0 no-repeat'})};
	if (chek_option2(this)=="wmb") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'B.gif) 0 0 no-repeat'})};
});
$("select[name='webmoney_type']").change(function() {
	if (chek_option2(this)=="wmr") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'R.gif) 0 0 no-repeat'})};
	if (chek_option2(this)=="wmz") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'Z.gif) 0 0 no-repeat'})};
	if (chek_option2(this)=="wmb") {$("input[name='webmoney_number']").css({'background':'url('+$start_url+'B.gif) 0 0 no-repeat'})};
});

/*Спрятать фон*/
function hidefon() {$('#fon_loading').hide()};
hidefon();
$('#loading').click(function() {$('#result_formula').hide();$('#fon_loading').show()}); 
/*Поменять порядок производной*/
switch ($('#dif_por').val()) {
	case '1': $('.dif_por_div').css({'background':'url(/images/css/math_dif1.gif) no-repeat'}); break;
	case '2': $('.dif_por_div').css({'background':'url(/images/css/math_dif2.gif) no-repeat'}); break;
	case '3': $('.dif_por_div').css({'background':'url(/images/css/math_dif3.gif) no-repeat'}); break;
	case '4': $('.dif_por_div').css({'background':'url(/images/css/math_dif4.gif) no-repeat'}); break;
	case '5': $('.dif_por_div').css({'background':'url(/images/css/math_dif5.gif) no-repeat'}); break;
	case '6': $('.dif_por_div').css({'background':'url(/images/css/math_dif6.gif) no-repeat'}); break;
	case '7': $('.dif_por_div').css({'background':'url(/images/css/math_dif7.gif) no-repeat'}); break;
	case '8': $('.dif_por_div').css({'background':'url(/images/css/math_dif8.gif) no-repeat'}); break;
	case '9': $('.dif_por_div').css({'background':'url(/images/css/math_dif9.gif) no-repeat'}); break;
};
$('#dif_por').bind("input", function() {
            switch ($(this).val()) {
				case '1': $('.dif_por_div').css({'background':'url(/images/css/math_dif1.gif) no-repeat'}); break;
				case '2': $('.dif_por_div').css({'background':'url(/images/css/math_dif2.gif) no-repeat'}); break;
				case '3': $('.dif_por_div').css({'background':'url(/images/css/math_dif3.gif) no-repeat'}); break;
				case '4': $('.dif_por_div').css({'background':'url(/images/css/math_dif4.gif) no-repeat'}); break;
				case '5': $('.dif_por_div').css({'background':'url(/images/css/math_dif5.gif) no-repeat'}); break;
				case '6': $('.dif_por_div').css({'background':'url(/images/css/math_dif6.gif) no-repeat'}); break;
				case '7': $('.dif_por_div').css({'background':'url(/images/css/math_dif7.gif) no-repeat'}); break;
				case '8': $('.dif_por_div').css({'background':'url(/images/css/math_dif8.gif) no-repeat'}); break;
				case '9': $('.dif_por_div').css({'background':'url(/images/css/math_dif9.gif) no-repeat'}); break;
			}
});


/*Поменять предел переменную*/
$('#lim_perem').change(function () {
chek_option_lim(this);
});

function chek_option_lim (item) {
$(item.children).each(function () {
if(this.selected) {
	switch ($(this).val()) {
				case 'x': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_x.gif) no-repeat'}); break;
				case 'y': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_y.gif) no-repeat'}); break;
				case 'z': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_z.gif) no-repeat'}); break;
				case 'k': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_k.gif) no-repeat'}); break;
				case 'm': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_m.gif) no-repeat'}); break;
				case 'n': $('#div_perem, #div_perem_modern').css({'background':'url(/images/css/perem_n.gif) no-repeat'}); break;
	}
}}); 
}
/*Поменять предел лимита*/
$('#lim_lim').change(function () {
chek_option_lim2(this);
});

function chek_option_lim2 (item) {
$(item.children).each(function () {
if(this.selected) {
	switch ($(this).val()) {
				case 'own': 
				$('#div_lim').html('<input name="limit_input" type="text" style="width:40px;height:13px;font-size:12px;border: 1px solid #7F7F52" value="">'); 
				$('#div_lim_modern2').hide(); $('#div_lim_modern').show();
				break;
				case '+infinity': 
				$('#div_lim, #div_lim_modern2').html('<img src="/images/css/plus_infinity.gif" /><input name="limit_input" type="hidden" value="+infinity">'); 
				$('#div_lim_modern').hide(); $('#div_lim_modern2').show();
				break;
				case '-infinity': 
				$('#div_lim, #div_lim_modern2').html('<img src="/images/css/minus_infinity.gif" /><input name="limit_input" type="hidden" value="-infinity">'); 
				$('#div_lim_modern').hide(); $('#div_lim_modern2').show();
				break;
				case '0': 
				$('#div_lim, #div_lim_modern2').html('<img src="/images/css/zero.gif" /><input name="limit_input" type="hidden" value="0">'); 
				$('#div_lim_modern').hide(); $('#div_lim_modern2').show();
				break;
	}
}}); 
}
/*Поменять сумма переменную*/
$('#sum_perem').change(function () {
chek_option_sum(this);
});

function chek_option_sum (item) {
$(item.children).each(function () {
if(this.selected) {
	switch ($(this).val()) {
				case 'x': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_x.gif) no-repeat 0 2px'}); 
					break;
				case 'y': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_y.gif) no-repeat 0 2px'}); 
					break;
				case 'z': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_z.gif) no-repeat 0 2px'}); 
					break;
				case 'k': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_k.gif) no-repeat 0 2px'}); 
					break;
				case 'm': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_m.gif) no-repeat 0 2px'});
					break;
				case 'n': 
					$('#div_perem, #div_perem2').css({'background':'url(/images/css/ravno_n.gif) no-repeat 0 2px'}); 
					break;
	}
}}); 
}
/*Поменять предел суммы*/
$('#sum_bottom').change(function () {
chek_option_sum_bottom(this);
});

function chek_option_sum_bottom (item) {
$(item.children).each(function () {
if(this.selected) {
	switch ($(this).val()) {
				case 'own': 
				$('#div_bottom').html('<input name="bottom_input" type="text" style="width:30px;height:13px;font-size:12px;border: 1px solid #7F7F52" value="">'); 
				$('#div_bottom_modern2').hide(); $('#div_bottom_modern').show();
				break;
				case '+infinity': 
				$('#div_bottom,#div_bottom_modern2').html('<img src="/images/css/plus_infinity.gif" style="margin-top:2px" /><input name="bottom_input" type="hidden" value="+infinity">'); 
				$('#div_bottom_modern').hide(); $('#div_bottom_modern2').show();
				break;
				case '-infinity': 
				$('#div_bottom,#div_bottom_modern2').html('<img src="/images/css/minus_infinity.gif" style="margin-top:2px" /><input name="bottom_input" type="hidden" value="-infinity">'); 
				$('#div_bottom_modern').hide(); $('#div_bottom_modern2').show();
				break;
				case '0': 
				$('#div_bottom,#div_bottom_modern2').html('<img src="/images/css/zero.gif" style="margin-top:2px" /><input name="bottom_input" type="hidden" value="0">'); 
				$('#div_bottom_modern').hide(); $('#div_bottom_modern2').show();
				break;
	}
}}); 
}
$('#sum_top').change(function () {
chek_option_sum_top(this);
});

function chek_option_sum_top (item) {
$(item.children).each(function () {
if(this.selected) {
	switch ($(this).val()) {
				case 'own': 
				$('#div_top').html('<input name="top_input" type="text" style="width:30px;height:13px;font-size:12px;border: 1px solid #7F7F52" value="">');
				$('#div_top_modern2').hide(); $('#div_top_modern').show();
				break;
				case '+infinity': 
				$('#div_top,#div_top_modern2').html('<img src="/images/css/plus_infinity.gif" style="margin-top:2px" /><input name="top_input" type="hidden" value="+infinity">'); 
				$('#div_top_modern').hide();$('#div_top_modern2').show();
				break;
				case '-infinity': 
				$('#div_top,#div_top_modern2').html('<img src="/images/css/minus_infinity.gif" style="margin-top:2px" /><input name="top_input" type="hidden" value="-infinity">'); 
				$('#div_top_modern').hide();$('#div_top_modern2').show();
				break;
				case '0': $('#div_top,#div_top_modern2').html('<img src="/images/css/zero.gif" style="margin-top:2px;margin-left:7px" /><input name="top_input" type="hidden" value="0">'); 
				$('#div_top_modern').hide();$('#div_top_modern2').show();
				break;
	}
}}); 
}
/*Поменять определенный интеграл*/
$('#int_bottom').change(function () {
chek_option_sum_bottom(this);$('#div_bottom img').css({'margin-top':'0px'});
});

$('#int_top').change(function () {
chek_option_sum_top(this);
});

$('#int_perem').bind("input", function() {
if ($(this).val().match(/^[a-z]{0,1}$/)) {$cont2='d'+$(this).val();} else {$cont2='dx';$(this).attr('value','x')};
$('div#dx, div#dx2').html($cont2);
});

/*Форма обратной связи*/
per4=$('form.simpleForm input[type="submit"]').attr('id');
$('form.simpleForm input[type="submit"]').before('<div style="margin-top:10px;margin-left:10px"><button type="submit" id="'+per4+'"><span class="round"><span>Отправить</span></span></button></div>');
$('form.simpleForm input[type="submit"]').hide();

/*Оплата webmoney*/

$("#show_wm").click(function () {
$("#wm").css({'position':'relative','top':'0px','left':'0px'});$(this).hide();});

$('select#wm_type').change(function () {
chek_option3(this);
});
function chek_option3 (item) {
$(item.children).each(function () {
if(this.selected) {
	if ($(this).html()=='WMR') {$('input#wm_summ').attr('value',$wmr);$('div#wm_summ').html($wmr)};
	if ($(this).html()=='WMZ') {$('input#wm_summ').attr('value',$wmz);$('div#wm_summ').html($wmz)};
	if ($(this).html()=='WMB') {$('input#wm_summ').attr('value',$wmb);$('div#wm_summ').html($wmb)};
	}
}); 
};

$wm_desc_def=$('input#wm_desc').attr('value');

if (typeof $wm_variant!="undefined" && $wm_variant!='nill') {$wm_variant_def=$wm_desc_def+' var'+$wm_variant;$('input#wm_desc').attr('value',$wm_variant_def);};
$('select#wm_variant').change(function () {
chek_option4(this);
});
function chek_option4 (item) {
$(item.children).each(function () {
if(this.selected) {
	$desca=$(this).attr('value');
	$desca=$wm_desc_def+' var'+$desca;
	$('input#wm_desc').attr('value',$desca);
	}
}); 
}
/*Редактирование меню*/
$('ul#default_60_28_lvl_2').parent('li').children('div').children('a').children('span.icemenu_haschild').remove();
$('ul#default_60_28_lvl_2').remove();
$('ul#default_59_28_lvl_2').parent('li').children('div').children('a').children('span.accArrow').remove();
$('ul#default_59_28_lvl_2').parent('li.parent').children('div').children('a').children('span.title').css({'font-weight':'bold'});
$('ul#default_59_28_lvl_2').hide();
/*Операции с матрицами*/
$('select[name="rows"]').change(function () {
change_matrix_rows(this);
});
function change_matrix_rows (item) {
 $(item.children).each(function () {
	if(this.selected) {
		$selected_val=$(this).val();
		$('input#matrix_element').each(function() {
		$per=/a(\d+)_(\d+)/;
		$index=$(this).attr('name').match($per);
		if ($index[1]<=$selected_val && $index[2]<=$selected_val) {$(this).css('display','inline')} else {$(this).css('display','none')}
		});
	};
 })
};
$('button[name="clear_matrix"]').click(function() {
	$('input#matrix_element').each(function() {$(this).attr('value','');});
});
$('img.service_button').hover(
function() {src_was=$(this).attr('src');if (src_was.slice(-6)!='-1.png') $(this).attr('src',src_was.slice(0, -4)+'-1.png');},
function() {$(this).attr('src',src_was);}
);
/*To show reklama*/
$(".show_reklama").click(function(){$("#reklama").css('display','block');});
$("div#nav_up").html($("div.pagenavbar").html());
$("div#nav_up").addClass('pagenavbar');
$("div.pagenavbar:not('#nav_up')").remove();
/*Otklu4it reklamu*/
$("#reklama_close").click(function(){
$("div#top_reklama").remove();
$("div#rekl_inside").remove();
$("#reklama_need").remove();
$("div#rekl.rektext").html('<p><b>Для включения рекламы перезагрузите страницу</b></p>');
$("div#rekl.rektext").attr('id','rektext');
$("div#rekl").remove();
$("#reklama_close").remove();
$("input[name='rekl']").attr('value','off');
return false;
})
$("a#reklama_need").click(function(){
alert("Благодаря средствам, вырученным за счет рекламы, мы способны поддерживать высокую скорость работы сайта и обеспечивать предельные нагрузки до 30 000 человек в сутки. Это достигается путем аренды мощного выделенного сервера. Оставшиеся средства идут на развитие проекта: разработку новых онлайн-калькуляторов, совершенствование существующих; в перспективе мы хотели бы перейти на полностью бесплатное решение контрольных на заказ, создать форум в помощь нашим пользователям и т.д. Пока что на реализацию всех наших идей денег абсолютно не хватает: количество переходов по рекламе от общего числа посетителей составляет всего 0,5%, а именно эти переходы приносят деньги. Но даже сейчас медленно, но уверенно, мы движемся к прогрессу! Во многом благодаря вам, наши посетители!");
return false;
});
$view='classic';
/*
	src_was1=$('#img1').attr('src');
	src_was2=$('#img2').attr('src');
	if ($view == 'modern') {
		$('#img1').attr('src',src_was1.slice(0, -6)+'of.gif');
		$('#img2').attr('src',src_was2.slice(0, -6)+'on.gif');
	}
	if ($view == 'classic') {
		$('#img1').attr('src',src_was1.slice(0, -6)+'on.gif');
		$('#img2').attr('src',src_was2.slice(0, -6)+'of.gif');
	}
*/
$('#img1').click(function(){
	src_was1=$(this).attr('src');
	src_was2=$('#img2').attr('src');
	$('#img2').attr('src',src_was2.slice(0, -6)+'of.gif');
	$(this).attr('src',src_was1.slice(0, -6)+'on.gif');
	$('.modern-view').hide();
	$('#classic-view').show();
	$view='classic';
	
});
$('#img2').click(function(){
	src_was2=$(this).attr('src');
	src_was1=$('#img1').attr('src');
	$('#img1').attr('src',src_was1.slice(0, -6)+'of.gif');
	$(this).attr('src',src_was2.slice(0, -6)+'on.gif');
	$('#classic-view').hide();
	$('.modern-view').show();
	$view='modern';
});
$('#img3').click(function(){
	src_was=$(this).attr('src');
	if (src_was.slice(-15)=='close-panel.gif') 
	{$(this).attr('src',src_was.slice(0, -15)+'show-panel.gif');$('div#panel').hide();} else
		{$(this).attr('src',src_was.slice(0, -14)+'close-panel.gif');$('div#panel').show();}
});
$('#ch-panel1').click(function(){
	$('#table-panel1').hide();
	$('#table-panel2').show();
});
$('#ch-panel2').click(function(){
	$('#table-panel2').hide();
	$('#table-panel1').show();
});

}); //Конец ready!
})(jQuery);


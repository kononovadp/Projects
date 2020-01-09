



function fCloseBlock(){
	
					  if(typeof(giNumberZadToLook) !== 'undefined'){
						  f_close_widow_zadachi_stat();
					  }else{
						 $('#dialog_resh_zad').dialog("close");
					  }
		}




function fNextBlock(){

			if(typeof(giNumberZadToLook) !== 'undefined'){
								  f_send_for_next_zadachi_stat();
							  }else{
								  f_send_for_next_zadachi();
							  }
}

function fNextAnswer(iStep, iAns, ell, iNumZad){
	
			if(gi_Answer_send != 11111 && gi_Answer_send !== g_iOpenZad){
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
    
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
		//$('#idanswerResult' + iNumberZad).val('');
		//$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		//$('#idanswerResult' + iNumberZad).css('color', '#f00');
	
			g_iSendZad = iNumZad;
	
	
	if(iStep === 0){var iAns1 = "_1"}//11aa
	else{iAns1 = iAns}
		
	ell = $(ell);ell.parent().hide("slow");

	var idStrOpen = "#idNextAns"+iAns+"_"+iNumZad;
	$("#idIdIsOpen_"+iNumZad).val(idStrOpen);
	if(/Нeвeрнo/gi.test($(idStrOpen).html())){
		$(idStrOpen).html($(idStrOpen).html().replace("Нeвeрнo", "Верно"));

		$("#idzadanie_"+iNumZad).html("")
			g_answerResult = 'верно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", 300);
		
		
	}
	$(idStrOpen).show("slow");
	
	if(/Неверно/gi.test($(idStrOpen).html())){$("#idPrevBut_"+iNumZad).show();
	$("#idzadanie_"+iNumZad).html("")
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", 300);	
	}else{
		$("#idPrevBut_"+iNumZad+"").hide();
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/восьмого/gi, "девятого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/седьмого/gi, "восьмого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/шестого/gi, "седьмого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/пятого/gi, "шестого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/четвертого/gi, "пятого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/третьего/gi, "четвертого"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/второго/gi, "третьего"));
		$("#idzadanie_"+iNumZad).html($("#idzadanie_"+iNumZad).html().replace(/первого/gi, "второго"));	
		
		
		var rE = new RegExp("iii_\\d","gi");

		var el2 = ell.parent().parent().children("img").eq(0);
		
				if(el2.length){
					var s = el2.attr("src");
				  if( rE.test( s )  ){
						  s = s.replace("iii_8", "iii_9");
						  s = s.replace("iii_7", "iii_8");
						  s = s.replace("iii_6", "iii_7");
						  s = s.replace("iii_5", "iii_6");
						  s = s.replace("iii_4", "iii_5");
						  s = s.replace("iii_3", "iii_4");
						  s = s.replace("iii_2", "iii_3");
						  s = s.replace("iii_1", "iii_2"); 
		  
						// el2.animate({opacity: 0.0},330);
							 el2.attr({src:s});					 
						//el2.animate({opacity: 1},330);		  
				  }
				}
	}
}
/////////////////////////////////////////////
function fBackAns(iNumZad){
	var el2 = $("#idzadanie_"+iNumZad).parent().children("img").eq(0);
	
	if(el2.length){var s = el2.attr("src"); el2.attr({src:s.replace(/iii_\d/gi, "iii_1")})}
	
	
	$("#idzadanie_"+iNumZad).html("Выберите вариант первого действия");
	$($("#idIdIsOpen_"+iNumZad).val()).hide("slow");
	
	$("#idNextAns_"+iNumZad+"").show("slow");
	$("#idPrevBut_"+iNumZad).hide();
}
///////////////////////////////////////////////
function f_check_answer_222(iNumberZad){
    var str = $("#idtrueanswerzad_"+iNumberZad).val();
	var arAns = str.split(":#:#:#:");
	
	var arAnsCl = new Array();	var arAnsCl_2 = new Array();
		var arAns1 = arAns[0].split(":#:");
		arAnsClK= new Array(new Array(),new Array(),new Array(),new Array()); var k = 0;
		arAnsClKCount= new Array(0,0,0,0);
		for(i = 0; i < arAns1.length; i++){	
			if((arAnsCl[i] = removeSpaces($("#idanswerzad_"+iNumberZad+"_"+i).val())) === ""){f_check_answer_22(iNumberZad);return;}
			if($("#idanswerzad_"+iNumberZad+"_"+i).hasClass("k1")){arAnsClK[0][arAnsClKCount[0]] = i;arAnsClKCount[0]++;}
			if($("#idanswerzad_"+iNumberZad+"_"+i).hasClass("k2")){arAnsClK[1][arAnsClKCount[1]] = i;arAnsClKCount[1]++;}
			if($("#idanswerzad_"+iNumberZad+"_"+i).hasClass("k3")){arAnsClK[2][arAnsClKCount[2]] = i;arAnsClKCount[2]++;}
			if($("#idanswerzad_"+iNumberZad+"_"+i).hasClass("k4")){arAnsClK[3][arAnsClKCount[3]] = i;arAnsClKCount[3]++;}
		}
		for(k = 0; k < 4; k++){
			for(i = 0; i < arAnsClK[k].length; i++){
				for( n = i+1; n < arAnsClK[k].length; n++){
					var value = parseFloat("554,20".replace(",", "."));
					 if(parseFloat(arAnsCl[arAnsClK[k][i]].replace(",", ".")) > parseFloat(arAnsCl[arAnsClK[k][n]].replace(",", "."))){
						 
						 var sss = arAnsCl[arAnsClK[k][i]]; 
						 arAnsCl[arAnsClK[k][i]] = arAnsCl[arAnsClK[k][n]]; 
						 arAnsCl[arAnsClK[k][n]] = sss;
						 
						 $("#idanswerzad_"+iNumberZad+"_"+arAnsClK[k][i]).val(arAnsCl[arAnsClK[k][i]]);
						 $("#idanswerzad_"+iNumberZad+"_"+arAnsClK[k][n]).val(arAnsCl[arAnsClK[k][n]]);
						 }
						 var s1 = arAnsCl[arAnsClK[k][i]];
						 var s2 = arAnsCl[arAnsClK[k][n]];
					 var sssss = $("#idanswerzad_"+iNumberZad+"_"+i).val();
					 var dd = 1;
				  }
			}
		}
		f_check_answer_22(iNumberZad);
}
function f_check_answer_22(iNumberZad){
	var str = $("#idtrueanswerzad_"+iNumberZad).val();
	var arAns = str.split(":#:#:#:");
	var bAnsType1 = false;var bAnsType2 = false;var bAnsType3 = false;var bAnsTypeSomeAns = false;
	
var tt = str.indexOf(":#:#:#:");
	if(str.indexOf(":#:#:#:") !== 0){bAnsType1 = true}
	if(typeof(arAns[1]) !== "undefined" && arAns[1] !== "" ){bAnsType2 = true}
	if(typeof(arAns[2]) !== "undefined" && arAns[2] !== "" ){bAnsType3 = true}
	if(typeof(arAns[3]) !== "undefined" && arAns[3] !== "" ){bAnsTypeSomeAns = true}
	
	 if( !f_check_answer_begin_22(iNumberZad) ){
		 return false;
		 }
	var arAnsRes = new Array();
	var ansCl, ansCl1, ansCl2, ansCl3, i, j, k;
	if(bAnsType1){
		var arAns1 = arAns[0].split(":#:");
		for(i = 0; i < arAns1.length; i++){	
			if((ansCl = removeSpaces($("#idanswerzad_"+iNumberZad+"_"+i).val())) === ""){f_Empty_22();return;}
			if(!(arAnsRes[i] = f_check_answer_22_1(iNumberZad, arAns1[i], ansCl))){return false;}
		}
	}//if(bAnsType1){
		if(bAnsType2){
			var arAns2 = arAns[1].split(":#:");
			for(j = 0; j < arAns2.length; j++){	
				if((ansCl1 = removeSpaces($("#idanswerzad1_"+iNumberZad+"_"+j).val())) === ""){f_Empty_22();return;}
				if((ansCl2 = removeSpaces($("#idanswerzad2_"+iNumberZad+"_"+j).val())) === ""){f_Empty_22();return;}
				if(!(arAnsRes[i+j] = f_check_answer_22_2(iNumberZad, arAns2[j], ansCl1, ansCl2))){return false;}
			}
		}//if(bAnsType2){
		  if(bAnsType3){
			  var arAns3 = arAns[2].split(":#:");
			  for(k = 0; k < arAns3.length; k++){	
				  if((ansCl1 = removeSpaces($("#idanswerzad00_"+iNumberZad+"_"+k).val())) === ""){f_Empty_22();return;}
				  if((ansCl2 = removeSpaces($("#idanswerzad01_"+iNumberZad+"_"+k).val())) === ""){f_Empty_22();return;}
				  if((ansCl3 = removeSpaces($("#idanswerzad02_"+iNumberZad+"_"+k).val())) === ""){f_Empty_22();return;}
				  if(!(arAnsRes[i+j+k] = f_check_answer_22_3(iNumberZad, arAns3[k], ansCl1, ansCl2, ansCl3))){return false;}
			  }
		  }//if(bAnsType3){
		if(bAnsTypeSomeAns){
			var ss = $("#idChooseSomeAns_"+iNumberZad) || 222;
			 	var clTrueChooseAns = fCodeAnswSelWord(ss);
				  if(!/3/gi.test(clTrueChooseAns)){f_Empty_ChooseAns_22();return;}
				  var sss33 = calcMD5(clTrueChooseAns);
					 if(calcMD5(clTrueChooseAns) !== arAns[3]){
						arAnsRes[arAnsRes.length] = false;
						
						//return false;
					   
					 }else{
						arAnsRes[arAnsRes.length] = true;
					 }
			  
		  }//if(bAnsTypeSomeAns){
		
		var bAnsRes = true;
		for(var i = 0; i < arAnsRes.length; i++){
			if(!arAnsRes[i]){
				bAnsRes = false;
				g_answerResult = 'неверно';
				g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
				return 'неверно';		
			}
		}	
	if(bAnsRes){
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad + ', #idanswerzad2'+ iNumberZad ).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  		return 'верно';		
	}//if(bAnsRes){
}
//////////////////////////////////////////////////
function f_Empty_22(){
			g_answerResult = 'Введите ответ';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';	
}
//////////////////////////////////////////////////
function f_Empty_ChooseAns_22(){
			g_answerResult = 'Выберите ответ';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';	
}
//////////////////////////////////////////////////
function f_check_answer_begin_22(iNumberZad){
	

		if(gi_Answer_send != 11111 && gi_Answer_send !== g_iOpenZad){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
	
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000 && !gb_type_zad_9)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
			
return true;
}//////////////////////////////////////////////////
function f_check_answer_22_1(iNumberZad, ansTrue, ansUser){
	ansUser = fReplaceRus(ansUser);
	var sSymbols;
	var RegExpSymbols = new RegExp(';;','gi');
			if(RegExpSymbols.test(ansTrue)){
				var ar = ansTrue.split(";;");
				//ansTrue = ar[0];
				ansTrue = fReplaceRus(ar[0]);//11bb
				sSymbols = "[0-9"+ar[1]+"\\(\\)\^+\-]";
			}else{
				sSymbols = "[0-9\\(\\)\^+\-.,]";
			}	
	 var strbr = '';
 	  if((strbr = fChekRightLeftBrackets(ansUser, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }

		  /////////////////////
		  var bExtraSymbol = false; var sExtraSymbol = '';
			  for(var i = 0; i < ansUser.length; i++){//проверим ответ на лишние переменные
			  var regexp  = new RegExp(sSymbols,'gi');
			  var sss = ansUser.substr(i, 1);//11
						if(!regexp.test(ansUser.substr(i, 1) ) ){
							bExtraSymbol = true; sExtraSymbol = ansUser.substr(i, 1); break;
						}
			  } if(bExtraSymbol){
				  $('#idanswerResult' + iNumberZad).css('width', '350px');
					g_answerResult = "В ответе не должно быть ";
					var regexp  = new RegExp('[a-z]','g');
					if(regexp.test(ansUser.substr(i, 1) ) ){g_answerResult += "переменной - " + sExtraSymbol;}
					else{
						var regexp  = new RegExp('[А-Яа-я]','g');
						if(regexp.test(ansUser.substr(i, 1) ) ){g_answerResult += "русской буквы - " + sExtraSymbol;}
						else {g_answerResult += "символа  " + sExtraSymbol;}
			 		 }
					g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
				}
				//////////////		  
 			var aswerClient = fPrivedMchlenStandart("("+ansUser+")");
			aswerClient = calcMD5(String(aswerClient));//11bb 
	  if(ansTrue == aswerClient){
		  //var ttttt = fCheckMultiples(iNumberZad);//11bb
		  //if(bCheckMultiple && !fCheckMultiples(iNumberZad)){return false;}//если надо было разложитьна множители
		  return true;
	  }else{
				g_answerResult = 'неверно';
				g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
				return false;
	  }
}//function f_check_answer_22_1(iNumberZad, ansTrue, ansUser){
//////////////////////////////////////////////////
function f_check_answer_22_2(iNumberZad, ansTrue, ansUser1, ansUser2){
	ansUser1 = fReplaceRus(ansUser1);ansUser2 = fReplaceRus(ansUser2);
	var arAnsUser = new Array(ansUser1, ansUser2);
var arAnsTrue = ansTrue.split("::");
for(var k = 0; k < 2; k++){	
	var sSymbols;
			if(/;;/gi.test(arAnsTrue[k])){
				var ar = arAnsTrue[k].split(";;");
				//arAnsTrue[k] = ar[0];
				arAnsTrue[k] = fReplaceRus(ar[0]);//11bb
				sSymbols = "[0-9"+ar[1]+"\\(\\)\^+\-]";
			}else{
				sSymbols = "[0-9\\(\\)\^+\-]";
			}	
	 var strbr = '';
 	  if((strbr = fChekRightLeftBrackets(ansUser1, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }
	  if((strbr = fChekRightLeftBrackets(ansUser2, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }

		  /////////////////////
		  var bExtraSymbol = false; var sExtraSymbol = '';
			  for(var i = 0; i < arAnsUser[k].length; i++){//проверим ответ на лишние переменные
			  var regexp  = new RegExp(sSymbols,'gi');
			  var sss = arAnsUser[k].substr(i, 1);//11
						if(!regexp.test(arAnsUser[k].substr(i, 1) ) ){
							bExtraSymbol = true; sExtraSymbol = arAnsUser[k].substr(i, 1); break;
						}
			  } if(bExtraSymbol){
				  $('#idanswerResult' + iNumberZad).css('width', '350px');
					g_answerResult = "В ответе не должно быть ";
					if(k === 0){g_answerResult = "В числителе не должно быть ";}
					if(k === 1){g_answerResult = "В знаменателе не должно быть ";}
					var regexp  = new RegExp('[a-z]','g');
					if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "переменной - " + sExtraSymbol;}
					else{
						var regexp  = new RegExp('[А-Яа-я]','g');
						if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "русской буквы - " + sExtraSymbol;}
						else {g_answerResult += "символа  " + sExtraSymbol;}
			 		 }
					g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
				}
				//////////////	
}//for(var i = 0; i < 2; i++){
 			var aswerClient1 = String(fPrivedMchlenStandart("("+ansUser1+")"));
			var aswerClient2 = String(fPrivedMchlenStandart("("+ansUser2+")"));
			
			
	  if(arAnsTrue[0] == calcMD5(aswerClient1) && arAnsTrue[1] == calcMD5(aswerClient2)){
		  //var ttttt = fCheckMultiples(iNumberZad);//11bb
		  //if(bCheckMultiple && !fCheckMultiples(iNumberZad)){return false;}//если надо было разложитьна множители
		  return true;
	  }else{
		  var b = false;
			for(var l = 2 ; l < 1166; l++){
					var gg1 = calcMD5(parseFloat(aswerClient1 / l)+'');
					//11bb 
					var gg2 = calcMD5(parseFloat(aswerClient2 / l)+'');
					//11bb 
				if(arAnsTrue[0] === gg1 && arAnsTrue[1] === gg2){
					//fSetResult('Сократи дробь', iNumberZad);
					b = true;
				g_answerResult = 'Сократи дробь';
				  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
				  return false;
				}
			}// for(l = 1 ; l < 66; l++){
				if(!b){
				  g_answerResult = 'неверно';
				  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
				  return false;
				}
	  }
	  
	  
	  
}//function f_check_answer_22_2(iNumberZad, ansTrue, ansUser, ansUser){
//////////////////////////////////////////////////
function f_check_answer_22_3(iNumberZad, ansTrue, ansUser1, ansUser2, ansUser3){
	ansUser1 = fReplaceRus(ansUser1);ansUser2 = fReplaceRus(ansUser2);ansUser3 = fReplaceRus(ansUser3);
	var arAnsUser = new Array(ansUser1, ansUser2, ansUser3);
var arAnsTrue = ansTrue.split("::");
for(var k = 0; k < 3; k++){	
	var sSymbols;
			if(/;;/gi.test(arAnsTrue[k])){
				var ar = arAnsTrue[k].split(";;");
				//arAnsTrue[k] = ar[0];
				arAnsTrue[k] = fReplaceRus(ar[0]);//11bb
				sSymbols = "[0-9"+ar[1]+"\\(\\)\^+\-]";
			}else{
				sSymbols = "[0-9\\(\\)\^+\-]";
			}	
	 var strbr = '';
 	  if((strbr = fChekRightLeftBrackets(ansUser1, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }
 	  if((strbr = fChekRightLeftBrackets(ansUser2, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }
 	  if((strbr = fChekRightLeftBrackets(ansUser3, 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  		g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }	  
		  /////////////////////
		  var bExtraSymbol = false; var sExtraSymbol = '';
			  for(var i = 0; i < arAnsUser[k].length; i++){//проверим ответ на лишние переменные
			  var regexp  = new RegExp(sSymbols,'gi');
			  var sss = arAnsUser[k].substr(i, 1);//11
						if(!regexp.test(arAnsUser[k].substr(i, 1) ) ){
							bExtraSymbol = true; sExtraSymbol = arAnsUser[k].substr(i, 1); break;
						}
			  } if(bExtraSymbol){
				  $('#idanswerResult' + iNumberZad).css('width', '350px');
					g_answerResult = "В ответе не должно быть ";
					if(k === 0){g_answerResult = "В целой части не должно быть ";}
					if(k === 1){g_answerResult = "В числителе не должно быть ";}
					if(k === 2){g_answerResult = "В знаменателе не должно быть ";}
					var regexp  = new RegExp('[a-z]','g');
					if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "переменной - " + sExtraSymbol;}
					else{
						var regexp  = new RegExp('[А-Яа-я]','g');
						if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "русской буквы - " + sExtraSymbol;}
						else {g_answerResult += "символа  " + sExtraSymbol;}
			 		 }
					g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
				}
				//////////////	
}//for(var i = 0; i < 2; i++){
 			 ansUser1 = String(fPrivedMchlenStandart("("+ansUser1+")"));
			 ansUser2 = String(fPrivedMchlenStandart("("+ansUser2+")"));
			 ansUser3 = String(fPrivedMchlenStandart("("+ansUser3+")"));
			
	  if(arAnsTrue[0] == calcMD5(ansUser1) && arAnsTrue[1] == calcMD5(ansUser2) && arAnsTrue[2] == calcMD5(ansUser3) ){
		  //var ttttt = fCheckMultiples(iNumberZad);//11bb
		  //if(bCheckMultiple && !fCheckMultiples(iNumberZad)){return false;}//если надо было разложитьна множители
		  return true;
	  }else{					   
		if(arAnsTrue[0] == calcMD5(ansUser1)){
			for(var i = 1 ; i < 11; i++){
		 	 var gg2 = calcMD5(parseFloat(ansUser2 / i)+'');
			 //11bb 
		 	 var gg3 = calcMD5(parseFloat(ansUser3 / i)+'');
	
				if(  arAnsTrue[1] === gg2 && arAnsTrue[2] === gg3 ){
					 g_answerResult='Сократи дробь';
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					 return false;
				}

			}// for(var i = 1 ; i < 1166; i++){
		}else{//if(g_trueAnswer1 == g_aswerClient[1]MD5){
		  if(parseInt(ansUser2, 10) > parseInt(ansUser3, 10) ){

			for(var j = 1 ; j < parseInt(ansUser2 / ansUser3 + 1, 10); j++){
				var g_aswerClient2Minus = calcMD5((ansUser2 - ansUser3 * j) + '');
				//11bb 
				var g_aswerClient1Plus = calcMD5((ansUser1 + j) + '');
					if(arAnsTrue[0] == g_aswerClient1Plus && arAnsTrue[1] == g_aswerClient2Minus && arAnsTrue[2] == g_aswerClient3MD5){
						$('#idanswerResult' + iNumberZad).css('width', '350px');
								g_answerResult = 'Выдели целую часть из неправильной дроби!';
								 g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
								 return false;
					}else{
						for(var i = 1 ; i < 11; i++){
						 var gg2 = calcMD5(parseFloat((ansUser2 - ansUser3 * j) / i)+'');
						 //11bb 
						 var gg3 = calcMD5(parseFloat(ansUser3 / i)+'');
				
							 if(  arAnsTrue[1] === gg2 && arAnsTrue[2] === gg3 ){
								 $('#idanswerResult' + iNumberZad).css('width', '450px');
								g_answerResult = 'Выдели целую часть из неправильной дроби';//и сократи дробь
								 g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
								 return false;
							 }
			
						}

					}
			}
		  }//if(g_aswerClient[2] > g_aswerClient[3])
		  
		}//}else{//if(g_trueAnswer1 == g_aswerClient[1]MD5){
								  
	 }
	  
								g_answerResult = 'неверно';
								 g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
								 return false;	  
	  
}//function f_check_answer_22_3(iNumberZad, ansTrue, ansUser, ansUser){
//////////////////////////////////////////////////
function fReplaceRus(str){
	  var g = 0;
	  var regExp = new RegExp("[а-я]","gi");
  while((g = str.search(regExp)) != -1){
	  var a = str.substr(g, 1);//11bb
		switch( str.substr(g, 1)){
			case "а":str = str.replace(/а/gi, "a"); break;
			case "в":str = str.replace(/в/gi, "b"); break;
			case "с":str = str.replace(/с/gi, "c"); break;
			case "х":str = str.replace(/х/gi, "x"); break;
			case "у":str = str.replace(/у/gi, "y"); break;
			case "о":str = str.replace(/о/gi, "o"); break;
			case "е":str = str.replace(/е/gi, "e"); break;
			case "к":str = str.replace(/к/gi, "k"); break;
			case "н":str = str.replace(/н/gi, "h"); break;
			case "м":str = str.replace(/м/gi, "m"); break;
			case "т":str = str.replace(/т/gi, "t"); break;

			default : return str;
		}
	  
	  
  }
	return str;
}
/////////////////////////////////////////////////
String.prototype.trim = function() {  
return this.replace(/^\s+|\s+$/g,""); 
} 
String.prototype.ltrim = function() 
{  
return this.replace(/^\s+/,""); 
} 
String.prototype.rtrim = function() {  
return this.replace(/\s+$/,""); }
var gHex="0123456789abcdef";function rhex(n){s = "";for(j=0;j<=3;j++) s+=gHex.charAt((n>>(j*8+4))&0x0F)+gHex.charAt((n >> (j * 8)) & 0x0F);return s;}function fSMD5(s){n=((s.length+8)>>6)+1;k=new Array(n*16);for(i=0;i<n*16;i++)k[i]=0;for(i=0;i<s.length;i++)k[i>>2]|=s.charCodeAt(i)<<((i%4)*8);k[i>>2]|=0x80<<((i%4)*8);k[n*16-2] = s.length*8;return k;}
function add(x,y){var l=(x&0xFFFF)+(y&0xFFFF);var m=(x>>16)+(y>>16)+(l>>16);return (m<<16)|(l&0xFFFF);}


function rol(num, cnt)
{
  return (num << cnt) | (num >>> (32 - cnt));
}

function cmn(q, a, b, x, s, t)
{
  return add(rol(add(add(a, q), add(x, t)), s), b);
}
function ff(a, b, c, d, x, s, t)
{
  return cmn((b & c) | ((~b) & d), a, b, x, s, t);
}
function gg(a, b, c, d, x, s, t)
{
  return cmn((b & d) | (c & (~d)), a, b, x, s, t);
}
function hh(a, b, c, d, x, s, t)
{
  return cmn(b ^ c ^ d, a, b, x, s, t);
}
function ii(a, b, c, d, x, s, t)
{
  return cmn(c ^ (b | (~d)), a, b, x, s, t);
}

function calcMD5(s)
{
  x = fSMD5(s);
  a =  1732584193;
  b = -271733879;
  c = -1732584194;
  d =  271733878;

  for(i = 0; i < x.length; i += 16)
  {
    olda = a;
    oldb = b;
    oldc = c;
    oldd = d;

    a = ff(a, b, c, d, x[i+ 0], 7 , -680876936);
    d = ff(d, a, b, c, x[i+ 1], 12, -389564586);
    c = ff(c, d, a, b, x[i+ 2], 17,  606105819);
    b = ff(b, c, d, a, x[i+ 3], 22, -1044525330);
    a = ff(a, b, c, d, x[i+ 4], 7 , -176418897);
    d = ff(d, a, b, c, x[i+ 5], 12,  1200080426);
    c = ff(c, d, a, b, x[i+ 6], 17, -1473231341);
    b = ff(b, c, d, a, x[i+ 7], 22, -45705983);
    a = ff(a, b, c, d, x[i+ 8], 7 ,  1770035416);
    d = ff(d, a, b, c, x[i+ 9], 12, -1958414417);
    c = ff(c, d, a, b, x[i+10], 17, -42063);
    b = ff(b, c, d, a, x[i+11], 22, -1990404162);
    a = ff(a, b, c, d, x[i+12], 7 ,  1804603682);
    d = ff(d, a, b, c, x[i+13], 12, -40341101);
    c = ff(c, d, a, b, x[i+14], 17, -1502002290);
    b = ff(b, c, d, a, x[i+15], 22,  1236535329);    

    a = gg(a, b, c, d, x[i+ 1], 5 , -165796510);
    d = gg(d, a, b, c, x[i+ 6], 9 , -1069501632);
    c = gg(c, d, a, b, x[i+11], 14,  643717713);
    b = gg(b, c, d, a, x[i+ 0], 20, -373897302);
    a = gg(a, b, c, d, x[i+ 5], 5 , -701558691);
    d = gg(d, a, b, c, x[i+10], 9 ,  38016083);
    c = gg(c, d, a, b, x[i+15], 14, -660478335);
    b = gg(b, c, d, a, x[i+ 4], 20, -405537848);
    a = gg(a, b, c, d, x[i+ 9], 5 ,  568446438);
    d = gg(d, a, b, c, x[i+14], 9 , -1019803690);
    c = gg(c, d, a, b, x[i+ 3], 14, -187363961);
    b = gg(b, c, d, a, x[i+ 8], 20,  1163531501);
    a = gg(a, b, c, d, x[i+13], 5 , -1444681467);
    d = gg(d, a, b, c, x[i+ 2], 9 , -51403784);
    c = gg(c, d, a, b, x[i+ 7], 14,  1735328473);
    b = gg(b, c, d, a, x[i+12], 20, -1926607734);
    
    a = hh(a, b, c, d, x[i+ 5], 4 , -378558);
    d = hh(d, a, b, c, x[i+ 8], 11, -2022574463);
    c = hh(c, d, a, b, x[i+11], 16,  1839030562);
    b = hh(b, c, d, a, x[i+14], 23, -35309556);
    a = hh(a, b, c, d, x[i+ 1], 4 , -1530992060);
    d = hh(d, a, b, c, x[i+ 4], 11,  1272893353);
    c = hh(c, d, a, b, x[i+ 7], 16, -155497632);
    b = hh(b, c, d, a, x[i+10], 23, -1094730640);
    a = hh(a, b, c, d, x[i+13], 4 ,  681279174);
    d = hh(d, a, b, c, x[i+ 0], 11, -358537222);
    c = hh(c, d, a, b, x[i+ 3], 16, -722521979);
    b = hh(b, c, d, a, x[i+ 6], 23,  76029189);
    a = hh(a, b, c, d, x[i+ 9], 4 , -640364487);
    d = hh(d, a, b, c, x[i+12], 11, -421815835);
    c = hh(c, d, a, b, x[i+15], 16,  530742520);
    b = hh(b, c, d, a, x[i+ 2], 23, -995338651);

    a = ii(a, b, c, d, x[i+ 0], 6 , -198630844);
    d = ii(d, a, b, c, x[i+ 7], 10,  1126891415);
    c = ii(c, d, a, b, x[i+14], 15, -1416354905);
    b = ii(b, c, d, a, x[i+ 5], 21, -57434055);
    a = ii(a, b, c, d, x[i+12], 6 ,  1700485571);
    d = ii(d, a, b, c, x[i+ 3], 10, -1894986606);
    c = ii(c, d, a, b, x[i+10], 15, -1051523);
    b = ii(b, c, d, a, x[i+ 1], 21, -2054922799);
    a = ii(a, b, c, d, x[i+ 8], 6 ,  1873313359);
    d = ii(d, a, b, c, x[i+15], 10, -30611744);
    c = ii(c, d, a, b, x[i+ 6], 15, -1560198380);
    b = ii(b, c, d, a, x[i+13], 21,  1309151649);
    a = ii(a, b, c, d, x[i+ 4], 6 , -145523070);
    d = ii(d, a, b, c, x[i+11], 10, -1120210379);
    c = ii(c, d, a, b, x[i+ 2], 15,  718787259);
    b = ii(b, c, d, a, x[i+ 9], 21, -343485551);

    a = add(a, olda);
    b = add(b, oldb);
    c = add(c, oldc);
    d = add(d, oldd);
  }
  return rhex(a) + rhex(b) + rhex(c) + rhex(d);
}
			var g_sSboi ='Сбой связи. Или у вас нет соиденения с интернетом,';
			g_sSboi +='или наш сервер оказался перегружен. Приносим извенения.';
			g_sSboi +=' Мы в скором времени исправим ситуацию.'
			
var gClass;
var g_timer_chekanswer = 0;
var  g_answerResult='';
var  g_iSendZad='';
var g_id_page ;
var gi_time_pause_zad_etalon = 500;
var ga_id_zad = new Array();
var ga_time_pause_zad = new Array();
var gi_Answer_send = 11111;
var gi_Answer_send_Number = 0;
var g_trueAnswer1 = '';
var g_trueAnswer2 = '';
var g_trueAnswer3 = '';
var g_aswerClient = new Array();
 g_aswerClient[1] = '';
 g_aswerClient[2] = '';
 g_aswerClient[3] = '';
var gi_timeout_zad = 2000;
var gAddingzad;//при добавлении задач кнопка Проверить работает постоянно True в add_z_next_prev.js 
var gKeycode = 0;
var gKeyUpID = 0;
var ga_TextZadachi = new Array();
var ga_TextZadachiOn = new Array();
var g_ch = 'lооkReshеnie';
for(var i = 0 ; i < 20; i++){ga_TextZadachiOn[i] = 1;}

var ga_InteractiveKeyboardCounter = new Array();

var ga_InteractiveKeyboardText = new Array();
var ga_InteractiveKeyboardOn = new Array();
var g_iNumAnswer  = new Array();//номер поля в ответе

var gPartOfWord = new Array();
gPartOfWord[0] = 'pris';
var gSoftorTireSign = 'sign';

var timerZad = 0;
var time_Zad = new Array();
var resheno = new Array();
var g_iOpenZad = 0;
var g_bLook = 0;
var g_iTime_resh_appear = 10;
var gbReshShowing = false;
var g_AddingNumAns = "";
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
function f_g_timer_chekanswer(){
		
send_answer(g_answerResult);
 g_timer_chekanswer = 0;
}

function send_answer(answerResult){
		gAddingzad = gAddingzad || false;
		
		if(/Не/g.test(answerResult) || /не/g.test(answerResult)){answerResult = 'неверно';}
		if(/Выбер/g.test(answerResult)){answerResult = 'Введите ответ';}
		if(/став/g.test(answerResult)){answerResult = 'Введите ответ';}
		if(/определитесь/g.test(answerResult)){answerResult = 'Введите ответ';}
		if(/Введите/g.test(answerResult)){answerResult = 'Введите ответ';}

	var datastr = "answerResult=" + encodeURIComponent(answerResult);
	datastr +=  "&time="+time_Zad[g_iSendZad];
	datastr +=  "&idZad="+$('input[name="name_id_zad'+g_iSendZad+'"]').val();
	datastr +=  "&id_page="+g_id_page;
	datastr +=  "&predmet="+$('#idpredmet').val();
	datastr +=  "&class="+gClass;
	datastr +=  "&t_but="+parseInt(g_iTime_resh_appear/60, 10);

	if(gAddingzad) datastr = '';
	
	var op = {
	url:	 'http://school-assistant.ru/_mainp/sav/saveAnswer.php', 
	async: true,
	type:	 'POST',
	timeout: 22000,//gi_timeout_zad,
	data: datastr,
	beforeSend:function(){
		
			f_timer_zadach_stop();
			$('#idanswerResult' + g_iSendZad).val('');
			$('#idanswerResult' + g_iSendZad).css('background-image','url(http://school-assistant.ru/images/main/loadsmall.gif)');
			
			},
			success: function(response){				
				gi_Answer_send = 11111;	
				f_timer_start();
				$('#idanswerResult' + g_iSendZad).css('background-image','none');
				$('#idanswerResult' + g_iSendZad).val(g_answerResult);	
			},
		error:  function(err){
				  alert('Сбой связи. Или у вас нет соиденения с интернетом, или наш сервер оказался перегружен. Приносим извенения. Мы в скором времени исправим ситуацию!!!' );
			gi_Answer_send = 11111;
			$('#idanswerResult'+g_iSendZad).css('background-image','none');
			
			f_timer_zadach_stop();
			$('#idbutcheck' + g_iSendZad).removeAttr('disabled');
		},
		complete:function (XMLHttpRequest, textStatus) {}
	}
	
	if(typeof(giNumberZadToLook) !== 'undefined'){
				gi_Answer_send = 11111;	
				f_timer_start();
				$('#idanswerResult' + g_iSendZad).css('background-image','none');
				$('#idanswerResult' + g_iSendZad).val(g_answerResult);		
	}else{
	  $.ajax(op);
	}
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
function f_send_look_zad(sUrl, sTarget){
	var stringPredmet = "";
if(typeof(giNumberZadToLook) !== 'undefined'){
	g_id_page = "no";
	 stringPredmet =  ggPredmet;
}else{
	 stringPredmet = $('#idpredmet').val();
}
	sTarget = f_sipResh(sTarget) || '';
	var datastr = "idZad="+$('input[name="name_id_zad'+g_iOpenZad+'"]').val();
	datastr +=  "&time="+time_Zad[g_iOpenZad];
	 datastr +=   "&target="+sTarget;
	 datastr +=  "&id_page="+g_id_page;
	 datastr +=  "&predmet="+stringPredmet;
	 datastr +=  "&ch="+encodeURIComponent(g_ch);
	 datastr +=  "&class="+gClass ;
	 datastr +=  "&t_but="+parseInt(g_iTime_resh_appear/60, 10);

	 
	var op = {
	url:	 sUrl,
	async: true,
	type: "POST",
	//timeout: gi_timeout_zad,
	data: datastr,
	beforeSend:function(){
		$('#idButresh'+g_iOpenZad).css('background-image', 'url(http://school-assistant.ru/images/main/reg/inputback32b.gif)');
			
			},
			success: function(data, textStatus, XMLHttpRequest){
	$('#idButresh'+g_iOpenZad).css('background-image', 'url(http://school-assistant.ru/images/main/reg/inputback32.gif)');
var regexp  = /this player/; 
var bVideoResult = regexp.test(data);	
		if(sTarget == 'lооkReshеniе'){
 
	  var closeReshButtonText = "";	
	  
	  var browser_name = navigator.appName;//11
	var browser_version = parseFloat(navigator.appVersion);//11

	  if('\v'=='v' && false){// если IE
		closeReshButtonText = "Пока мы не смогли себе позволить потратить ";
		closeReshButtonText += "массу времени на доработку сайта под IE. <br>Просмотр решений в этом браузере не работает. <br>Рекомендуем скачать  и установить в три клика, за 5 мин. по этой ссылке <br> ";
		closeReshButtonText += "<a href='http://www.google.com/chrome?hl=ru' style='font-style:italic;text-decoration:none;color:#d77;'>";
		closeReshButtonText += "GOOGLE CHROME</a>, <br>&nbsp;Попробуйте, и вы не пожалеете.";
		closeReshButtonText += "<br>Все функции сайта будут работать отлично. ( и решения тоже) <br><br>"+data;
	   closeReshButtonText += "<br><br><span style='color:red;'>А теперь нажмите клавишу \"F5\", что бы снова увидеть задачу.</span>";
		$('#idtextzadachi_'+g_iOpenZad).html(closeReshButtonText);
	  }else{
		  if($.browser.mozilla){
			  data = data.replace("<a href=\"http://school-assistant.ru/reg/reg.php\" style=\"font-size:15px\"> Регистрация </a>","");
				data += "<br><br><br>";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";
				data += " &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;";				
				data += "<span id=\"idmreshclose\" style='font-size:24px;font-style:italic;'>Закрыть решение</span> ";
			  }
			$('#dialog_reshenie_zadachi').html(data);
				// $('#dialog_reshenie_zadachi').flash("http://school-assistant.ru/images/zadachi/7/geometr/mat_vir/1.swf");
			$('#dialog_reshenie_zadachi').dialog('open');
			if($.browser.mozilla){
			  $('#idmreshclose').click(function(){$('#dialog_reshenie_zadachi').dialog('close');});
			  $('#idmreshclose').mouseover(function(){ $(this).css('cursor', 'pointer');$(this).css('color','#a00');});
			  $('#idmreshclose').mouseout(function(){ $(this).css('cursor','default');$(this).css('color','#600'); });
			}
	  }

			
			if(bVideoResult){
		  var s1 = new SWFObject("video/player.swf","single","550","400","7");
			  s1.addParam("allowfullscreen","true");
			 s1.addParam("menu", "false");
			// s1.addParam("wmode", "transparent"); 
			// s1.addParam("wmode", "opaque");
			  
			  s1.addVariable("autostart","true");
			  
			  s1.addVariable("file","http://school-assistant.ru/images/zadachi/7/geometr/mat_vir/1.flv");
			  s1.write("player1");
			 
			}
		//$('#dialog_reshenie_zadachi').blur();
		var aaa = $('#dialog_reshenie_zadachi').find("input:focus").val();
		var el = $('#dialog_reshenie_zadachi').find("input:focus");el.val(el.val());
		}
		gbReshShowing = false;
			//alert(' ответ сервера - ' + data);
			},
		error:  function(err){gbReshShowing = false;
		$('#idButresh'+g_iOpenZad).css('background-image', 'url(http://school-assistant.ru/images/main/reg/inputback32.gif)');
		alert(' Нет ответа от сервера. Попробуйте еще раз.');
		},
		complete:function (XMLHttpRequest, textStatus) {

					  }
	}
	
	
	  $.ajax(op);
}

function f_timer_start(){
resheno[g_iOpenZad] = resheno[g_iOpenZad] || false;	
	if(g_bLook){
		if(!resheno[g_iOpenZad]){f_send_look_zad('http://school-assistant.ru/_mainp/sav/saveLookZad.php');}
		g_bLook = 0;
	}

if(!resheno[g_iOpenZad])
$('#idButresh'+g_iOpenZad).hide();
if(timerZad != 0)
window.clearTimeout(timerZad);
if(!resheno[g_iOpenZad])
timerZad = window.setTimeout("f_timer_zadach_();", 1000);

return true;
}

function	f_timer_zadach_show() {
		$('#idtimeron').val(0);$('#idtimer' + g_iOpenZad).val("");
		$('#idButresh' + g_iOpenZad).val("Решение");
	    $('#idButresh' + g_iOpenZad).removeAttr("disabled").css({ 'opacity' : 1 }).attr("title", "");
		$('#idButresh'+g_iOpenZad).show();
}

function	f_timer_zadach_() {
	time_Zad[g_iOpenZad] = time_Zad[g_iOpenZad] || 0;
	var strSek = " сек.";var strMinute = " мин.";
	var stime = g_iTime_resh_appear-time_Zad[g_iOpenZad];
	var bTimerOn = parseInt($('#idtimeron').val()) || false;
	
	if(stime <= 0 || ( g_answerResult == 'верно' && g_iSendZad == g_iOpenZad )  ){f_timer_zadach_show();
    }else{
		//$('#idtimer' + g_iOpenZad).val(stime);//11bb
		 var sTitle = "Время появления решения -> Мой кабинет -> Настройки";
		 $('#idButresh' + g_iOpenZad).val("Решение - "+stime);
	     $('#idButresh' + g_iOpenZad).attr('disabled', 'disabled').css({ 'opacity' : 0.3 }).attr("title", sTitle);
		 $('#idButresh'+g_iOpenZad).show();	
		 time_Zad[g_iOpenZad]++;
	     f_timer_zadach_stop();
	     timerZad = window.setTimeout("f_timer_zadach_();", 1000);
     }
	
	                                       //11bb

	
	//if(time_Zad[g_iOpenZad] > g_iTime_resh_appear)
	//f_timer_zadach_stop();

}
	  
function	f_timer_zadach_stop(){
		if( timerZad!= 0){
		window.clearTimeout(timerZad);
		timerZad = 0;

		}	
}
////////////////////////////////////////////////////////////////	  
function fMyCode(str){
	str2  = "";// return str.substr(1, 1);
	for(i = 0 ; i < str.length; i++){
		switch(str.substr(i, 1)){
		  case "й" : str2 += "1";break;
		  case "ц" : str2 += "2";break;
		  case "у" : str2 += "3";break;
		  case "к" : str2 += "4";break;
		  case "е" : str2 += "5";break;
		  case "н" : str2 += "6";break;
		  case "г" : str2 += "7";break;
		  case "ш" : str2 += "8";break;
		  case "щ" : str2 += "9";break;
		  case "з" : str2 += "10";break;
		  case "х" : str2 += "11";break;
		  case "ъ" : str2 += "12";break;
		  case "ф" : str2 += "13";break;
		  case "ы" : str2 += "14";break;
		  case "в" : str2 += "15";break;
		  case "а" : str2 += "16";break;
		  case "п" : str2 += "17";break;
		  case "р" : str2 += "18";break;
		  case "о" : str2 += "19";break;
		  case "л" : str2 += "20";break;
		  case "д" : str2 += "21";break;
		  case "ж" : str2 += "22";break;
		  case "э" : str2 += "23";break;
		  case "я" : str2 += "24";break;
		  case "ч" : str2 += "25";break;
		  case "с" : str2 += "26";break;
		  case "м" : str2 += "27";break;
		  case "и" : str2 += "28";break;
		  case "т" : str2 += "29";break;
		  case "ь" : str2 += "30";break;
		  case "б" : str2 += "31";break;
		  case "ю" : str2 += "32";break;
		  case "," : str2 += ",";break;
		  case "ё" : str2 += "33";break;
		  default :  str2 += str.substr(i, 1);break;
	
		  }
	}
	return str2;
}
////////////////////////////////////////////////////////////////////////////////

function fLetKeyup(pEllement, keyCode){
	
		switch(keyCode){
				case 192:	if(gKeycode == 'ё'){ $(pEllement).val('ёё');$(pEllement).width(26);}
				else { $(pEllement).val('ё');$(pEllement).width(15);} break;
			
				case 81:	if(gKeycode == 'й'){ $(pEllement).val('йй');$(pEllement).width('1.7em');}
							else { $(pEllement).val('й');$(pEllement).width('1em');} break;
				case 87:	if(gKeycode == 'ц'){ $(pEllement).val('цц');$(pEllement).width(29);}
							else { $(pEllement).val('ц');$(pEllement).width(16);} break;
				case 69:	if(gKeycode == 'у'){ $(pEllement).val('уу');$(pEllement).width(26);}
							else { $(pEllement).val('у');$(pEllement).width(14);} break;			 
				case 82:	if(gKeycode == 'к'){ $(pEllement).val('кк');$(pEllement).width(27);}
							else { $(pEllement).val('к');$(pEllement).width(15);} break;			 
				case 84:	if(gKeycode == 'е'){ $(pEllement).val('ее');$(pEllement).width(24);}
							else { $(pEllement).val('е');$(pEllement).width(15);} break;			 
				case 89:	if(gKeycode == 'н'){ $(pEllement).val('нн');$(pEllement).width(24);}
							else { $(pEllement).val('н');$(pEllement).width(13);} break;			 
				case 85:	if(gKeycode == 'г'){ $(pEllement).val('гг');$(pEllement).width(23);}
							else { $(pEllement).val('г');$(pEllement).width(13);} break;			 
				case 73:	if(gKeycode == 'ш'){ $(pEllement).val('шш');$(pEllement).width(39);}
							else { $(pEllement).val('ш');$(pEllement).width(21);} break;			 
				case 79:	if(gKeycode == 'щ'){ $(pEllement).val('щщ');$(pEllement).width(31);}
							else { $(pEllement).val('щ');$(pEllement).width(17);} break;			 
				case 80:	if(gKeycode == 'з'){ $(pEllement).val('зз');$(pEllement).width(24);}
							else { $(pEllement).val('з');$(pEllement).width(13);} break;			 
				case 219:	if(gKeycode == 'х'){ $(pEllement).val('хх');$(pEllement).width(25);}
							else { $(pEllement).val('х');$(pEllement).width(14);} break;			 
				case 221:	 $(pEllement).val('ъ');$(pEllement).width(15); break;
				
				
				case 65:	if(gKeycode == 'ф'){ $(pEllement).val('фф');$(pEllement).width(36);}
							else { $(pEllement).val('ф');$(pEllement).width(19);} break;			 
				case 83:	if(gKeycode == 'ы'){ $(pEllement).val('ыы');$(pEllement).width(37);}
							else { $(pEllement).val('ы');$(pEllement).width(19);} break;			 
				case 68:	if(gKeycode == 'в'){ $(pEllement).val('вв');$(pEllement).width(28);}
							else { $(pEllement).val('в');$(pEllement).width(15);} break;			 
				case 70:	if(gKeycode == 'а'){ $(pEllement).val('аа');$(pEllement).width(27);}
							else { $(pEllement).val('а');$(pEllement).width(15);} break;			 
				case 71:	if(gKeycode == 'п'){ $(pEllement).val('пп');$(pEllement).width(29);}
							else { $(pEllement).val('п');$(pEllement).width(16);} break;			 
				case 72:	if(gKeycode == 'р'){ $(pEllement).val('рр');$(pEllement).width(28);}
							else { $(pEllement).val('р');$(pEllement).width(16);} break;			 
				case 74:	if(gKeycode == 'о'){ $(pEllement).val('оо');$(pEllement).width(26);}
							else { $(pEllement).val('о');$(pEllement).width(14);} break;			 
				case 75:	if(gKeycode == 'л'){ $(pEllement).val('лл');$(pEllement).width(26);}
							else { $(pEllement).val('л');$(pEllement).width(14);} break;			 
				case 76:	if(gKeycode == 'д'){ $(pEllement).val('дд');$(pEllement).width(26);}
							else { $(pEllement).val('д');$(pEllement).width(14);} break;			 
				case 186:	if(gKeycode == 'ж'){ $(pEllement).val('жж');$(pEllement).width(37);}
							else { $(pEllement).val('ж');$(pEllement).width(19);} break;			 
				case 222:	if(gKeycode == 'э'){ $(pEllement).val('ээ');$(pEllement).width(24);}
							else { $(pEllement).val('э');$(pEllement).width(13);} break;			 


				case 90:	if(gKeycode == 'я'){ $(pEllement).val('яя');$(pEllement).width(25);}
							else { $(pEllement).val('я');$(pEllement).width(13);} break;			 
				case 88:	if(gKeycode == 'ч'){ $(pEllement).val('чч');$(pEllement).width(26);}
							else { $(pEllement).val('ч');$(pEllement).width(14);} break;			 
				case 67:	if(gKeycode == 'с'){ $(pEllement).val('сс');$(pEllement).width(24);}
							else { $(pEllement).val('с');$(pEllement).width(13);} break;			 
				case 86:	if(gKeycode == 'м'){ $(pEllement).val('мм');$(pEllement).width(33);}
							else { $(pEllement).val('м');$(pEllement).width(18);} break;			 
				case 66:	if(gKeycode == 'и'){ $(pEllement).val('ии');$(pEllement).width(29);}
							else { $(pEllement).val('и');$(pEllement).width(16);} break;			 
				case 78:	if(gKeycode == 'т'){ $(pEllement).val('тт');$(pEllement).width(24);}
							else { $(pEllement).val('т');$(pEllement).width(14);} break;			 
				case 77:	$(pEllement).val('ь');$(pEllement).width(14); break;
				
				case 188:	if(gKeycode == 'б'){ $(pEllement).val('бб');$(pEllement).width(28);}
							else { $(pEllement).val('б');$(pEllement).width(15);} break;			 
				case 190:	if(gKeycode == 'ю'){ $(pEllement).val('юю');$(pEllement).width(39);}
							else { $(pEllement).val('ю');$(pEllement).width(21);} break;			
		
		}
		//if(gKeycode !== ''){ $(pEllement).width('1.7em');}
		//else { $(pEllement).width('1em');} 
    //alert(keyCode);	
}
///////////////////////////////////////////////////////////////////////////////////////
function fLetKeyup7(pEllement, keyCode){
	
	}
///////////////////////////////////////////////////////////////////////////////////////
function fLetKeycode7(keyCode){
	
		switch(keyCode){
				case 192:	if(gKeycode == 'ё'){ $(pEllement).val('ёё');$(pEllement).width(26);}
				else { $(pEllement).val('ё');$(pEllement).width(15);} break;
			
				case 81:	if(gKeycode == 'й'){ $(pEllement).val('йй');$(pEllement).width('1.7em');}
							else { $(pEllement).val('й');$(pEllement).width('1em');} break;
				case 87:	if(gKeycode == 'ц'){ $(pEllement).val('цц');$(pEllement).width(29);}
							else { $(pEllement).val('ц');$(pEllement).width(16);} break;
				case 69:	if(gKeycode == 'у'){ $(pEllement).val('уу');$(pEllement).width(26);}
							else { $(pEllement).val('у');$(pEllement).width(14);} break;			 
				case 82:	if(gKeycode == 'к'){ $(pEllement).val('кк');$(pEllement).width(27);}
							else { $(pEllement).val('к');$(pEllement).width(15);} break;			 
				case 84:	if(gKeycode == 'е'){ $(pEllement).val('ее');$(pEllement).width(24);}
							else { $(pEllement).val('е');$(pEllement).width(15);} break;			 
				case 89:	if(gKeycode == 'н'){ $(pEllement).val('нн');$(pEllement).width(24);}
							else { $(pEllement).val('н');$(pEllement).width(13);} break;			 
				case 85:	if(gKeycode == 'г'){ $(pEllement).val('гг');$(pEllement).width(23);}
							else { $(pEllement).val('г');$(pEllement).width(13);} break;			 
				case 73:	if(gKeycode == 'ш'){ $(pEllement).val('шш');$(pEllement).width(39);}
							else { $(pEllement).val('ш');$(pEllement).width(21);} break;			 
				case 79:	if(gKeycode == 'щ'){ $(pEllement).val('щщ');$(pEllement).width(31);}
							else { $(pEllement).val('щ');$(pEllement).width(17);} break;			 
				case 80:	if(gKeycode == 'з'){ $(pEllement).val('зз');$(pEllement).width(24);}
							else { $(pEllement).val('з');$(pEllement).width(13);} break;			 
				case 219:	if(gKeycode == 'х'){ $(pEllement).val('хх');$(pEllement).width(25);}
							else { $(pEllement).val('х');$(pEllement).width(14);} break;			 
				case 221:	 $(pEllement).val('ъ');$(pEllement).width(15); break;
				
				
				case 65:	if(gKeycode == 'ф'){ $(pEllement).val('фф');$(pEllement).width(36);}
							else { $(pEllement).val('ф');$(pEllement).width(19);} break;			 
				case 83:	if(gKeycode == 'ы'){ $(pEllement).val('ыы');$(pEllement).width(37);}
							else { $(pEllement).val('ы');$(pEllement).width(19);} break;			 
				case 68:	if(gKeycode == 'в'){ $(pEllement).val('вв');$(pEllement).width(28);}
							else { $(pEllement).val('в');$(pEllement).width(15);} break;			 
				case 70:	if(gKeycode == 'а'){ $(pEllement).val('аа');$(pEllement).width(27);}
							else { $(pEllement).val('а');$(pEllement).width(15);} break;			 
				case 71:	if(gKeycode == 'п'){ $(pEllement).val('пп');$(pEllement).width(29);}
							else { $(pEllement).val('п');$(pEllement).width(16);} break;			 
				case 72:	if(gKeycode == 'р'){ $(pEllement).val('рр');$(pEllement).width(28);}
							else { $(pEllement).val('р');$(pEllement).width(16);} break;			 
				case 74:	if(gKeycode == 'о'){ $(pEllement).val('оо');$(pEllement).width(26);}
							else { $(pEllement).val('о');$(pEllement).width(14);} break;			 
				case 75:	if(gKeycode == 'л'){ $(pEllement).val('лл');$(pEllement).width(26);}
							else { $(pEllement).val('л');$(pEllement).width(14);} break;			 
				case 76:	if(gKeycode == 'д'){ $(pEllement).val('дд');$(pEllement).width(26);}
							else { $(pEllement).val('д');$(pEllement).width(14);} break;			 
				case 186:	if(gKeycode == 'ж'){ $(pEllement).val('жж');$(pEllement).width(37);}
							else { $(pEllement).val('ж');$(pEllement).width(19);} break;			 
				case 222:	if(gKeycode == 'э'){ $(pEllement).val('ээ');$(pEllement).width(24);}
							else { $(pEllement).val('э');$(pEllement).width(13);} break;			 


				case 90:	if(gKeycode == 'я'){ $(pEllement).val('яя');$(pEllement).width(25);}
							else { $(pEllement).val('я');$(pEllement).width(13);} break;			 
				case 88:	if(gKeycode == 'ч'){ $(pEllement).val('чч');$(pEllement).width(26);}
							else { $(pEllement).val('ч');$(pEllement).width(14);} break;			 
				case 67:	if(gKeycode == 'с'){ $(pEllement).val('сс');$(pEllement).width(24);}
							else { $(pEllement).val('с');$(pEllement).width(13);} break;			 
				case 86:	if(gKeycode == 'м'){ $(pEllement).val('мм');$(pEllement).width(33);}
							else { $(pEllement).val('м');$(pEllement).width(18);} break;			 
				case 66:	if(gKeycode == 'и'){ $(pEllement).val('ии');$(pEllement).width(29);}
							else { $(pEllement).val('и');$(pEllement).width(16);} break;			 
				case 78:	if(gKeycode == 'т'){ $(pEllement).val('тт');$(pEllement).width(24);}
							else { $(pEllement).val('т');$(pEllement).width(14);} break;			 
				case 77:	$(pEllement).val('ь');$(pEllement).width(14); break;
				
				case 188:	if(gKeycode == 'б'){ $(pEllement).val('бб');$(pEllement).width(28);}
							else { $(pEllement).val('б');$(pEllement).width(15);} break;			 
				case 190:	if(gKeycode == 'ю'){ $(pEllement).val('юю');$(pEllement).width(39);}
							else { $(pEllement).val('ю');$(pEllement).width(21);} break;			
		
		}
		//if(gKeycode !== ''){ $(pEllement).width('1.7em');}
		//else { $(pEllement).width('1em');} 
    //alert(keyCode);	
}
///////////////////////////////////////////////////////////////////////////////////////
function fPartword(pEll){
	var thisCl = gPartOfWord[g_iOpenZad];
	var ar = new Array();
	var reEmpty = new RegExp(" ");
	var reThisCl = new RegExp(thisCl);
	var pEllCl = pEll.attr('class');
	var bAlredyThisCl = reThisCl.test(pEllCl);
	var bOtherClass = false;
	var ar1 = new Array(); 
		  if(reEmpty.test(pEllCl)){ 
								if(!bAlredyThisCl)
								bOtherClass = true;
		  ar1 = pEll.attr('class').split(' '); 
		  pEllCl = ar1[1]; 
		  }
	
	var bFirst = false;
	var bNeighborThis = false;
	var bTwoNeighborsThis = false;
	
	var bOtherClassMiddle = false;
	var ellsThis = pEll.parent().children("."+thisCl);
	var sizeThis = ellsThis.size();
	var bFirst = !parseInt(sizeThis);
	
	var ellsPart = pEll.parent().children(".partword");
	var sizePart = ellsPart.size();
	var numberThis = 111;
	////////////////////////////////////////////
		for(var i = 0; i < sizePart; i++){
	
			if(pEll.attr('id') == ellsPart.eq(i).attr('id')  ){
				numberThis = i;
			  if(!bFirst){
				if( ( i!=0 && ellsPart.eq(i-1).hasClass(thisCl) ) || (i!=sizePart-1 && ellsPart.eq(i+1).hasClass(thisCl)) )
				bNeighborThis = true;
				if( ( i!=0 && ellsPart.eq(i-1).hasClass(thisCl) ) && (i!=sizePart-1 && ellsPart.eq(i+1).hasClass(thisCl)) ){
				bTwoNeighborsThis = true;
				return true;}
			  }//if(!bFirst){
		var leftOtherNeighbor = (i!=0 && reEmpty.test(ellsPart.eq(i-1).attr('class')) && !ellsPart.eq(i-1).hasClass(thisCl));
		var rightOtherNeighbor = (i!=sizePart-1 && reEmpty.test(ellsPart.eq(i+1).attr('class')) && !ellsPart.eq(i+1).hasClass(thisCl));
						  if(leftOtherNeighbor){
							  var leftClFull = ellsPart.eq(i-1).attr('class');
							  var leftCl = leftClFull.substr(leftClFull.indexOf(" "))
						  }
						  if(rightOtherNeighbor){
							  var rightClFull = ellsPart.eq(i+1).attr('class');
							  var rightCl = rightClFull.substr(rightClFull.indexOf(" "))
						  }
				if(leftOtherNeighbor && rightOtherNeighbor && leftCl == rightCl){ bOtherClassMiddle = true; 
				return true;}
				
			}//if(pEll.attr('id') == ellsPart.eq(i).attr('id')  ){
		}//for
	///////////////////////////////////////////
	if(bAlredyThisCl && !bTwoNeighborsThis){
		pEll.removeClass(thisCl); pEll.css('backgroundImage' ,'none'); fPartwordDraw(pEll, thisCl); return true; 
		}
	if(!bOtherClass && bNeighborThis && !bTwoNeighborsThis){
		pEll.addClass(thisCl); fPartwordDraw(pEll, thisCl);
		return true; 
		}
	if(bOtherClass && !bOtherClassMiddle && (bNeighborThis || bFirst) ){
		pEll.removeClass(pEllCl );pEll.addClass(thisCl); fPartwordDraw(pEll, thisCl);fPartwordDraw(pEll, pEllCl);
		return true; 
		}
		  if(!bOtherClass && ((bNeighborThis && !bFirst) || bFirst ) && !bAlredyThisCl){
			  pEll.addClass(thisCl); fPartwordDraw(pEll, thisCl);
			  return true; 
		  }
return true; 
		
}
//////////////////////////////////////////////////////////////////////////////////////////////
function fPartwordDraw(pEllement, drawclass){
	var ellements = pEllement.parent().children("."+drawclass);
	var size = ellements.size();
	
	for(var i = 0; i < size; i++){
		var url = "url(http://school-assistant.ru/images/zadachi/russian/partword/"+drawclass+"/"+size+"/"+size+drawclass+i+".gif)";
		
	ellements.eq(i).css('backgroundImage' ,url);
	regexpend = /end0.gif/;
	if(regexpend.test(url))ellements.eq(i).css('backgroundPosition', 'left top'); ;
	}	
}
///////////////////////////////////////////////////////////////////////////////////////////////////
	function fInputbut_pw(pEll){
					var nEll = pEll.parent().children('input');					 
					 var size = nEll.size();
					 for(var i = 0; i < size; i++){
						var classN = nEll.eq(i).attr('class');
						nEll.eq(i).removeClass(classN).addClass('inputbut_pw');
						if(nEll.eq(i).val() == pEll.val()){
							switch(i){
							case 0:	gPartOfWord[g_iOpenZad] = 'pris';  break;
							case 1:	gPartOfWord[g_iOpenZad] = 'root';  break;
							case 2:	gPartOfWord[g_iOpenZad] = 'sufix';  break;
							case 3:	gPartOfWord[g_iOpenZad] = 'postf';  break;
							case 4:	gPartOfWord[g_iOpenZad] = 'end';  break;
							case 5:	gPartOfWord[g_iOpenZad] = 'roo2';  break;
							case 6:	gPartOfWord[g_iOpenZad] = 'sufi2';  break;
							}
						} 
					 }
					 pEll.removeClass('inputbut_pw').addClass('inputbut_pw_push')
					  $('.inputbut_pw').unbind('click');
					 $('.inputbut_pw').click(function(){ fInputbut_pw($(this)); return true; });
					   return true; 
	}
////////////////////////////////////////////////////////////////////////////////////
	function fInputbut_SoftorTireSign(pEll){
					var nEll = pEll.parent().children('input');					 
					 var size = nEll.size();
					 for(var i = 0; i < size; i++){
						var classN = nEll.eq(i).attr('class');
						nEll.eq(i).removeClass(classN).addClass('inputbut_st');
						if(nEll.eq(i).val() == pEll.val()){
							switch(i){
							case 0:	gSoftorTireSign = 'sign';  break;
							case 1:	gSoftorTireSign = 'softsign';  break;
							case 2:	gSoftorTireSign = 'tiresign';  break;

							}
						} 
					 }
					 pEll.removeClass('inputbut_st').addClass('inputbut_st_push')
					  $('.inputbut_st').unbind('click');
					 $('.inputbut_st').click(function(){ fInputbut_SoftorTireSign($(this)); return true; });
					   return true; 
	}
////////////////////////////////////////////////////////////////////////////////////

function fSoftsignClick(pEll){
	var a = pEll.attr('class');
						switch(pEll.attr('class')){
							case 'softsign':
									pEll.addClass('sign');
									pEll.html('ь');
									pEll.attr('width','disable');pEll.width(9);
							break;
							case 'softsign sign':
									pEll.removeClass('sign');
									pEll.addClass('pusto');
									pEll.html('');
									pEll.attr('width','disable');pEll.width(0);
									
							break;
					
							case 'softsign pusto':
									pEll.removeClass('pusto');
									pEll.html('_');;
									pEll.attr('width','disable');pEll.width(13);
							break;
	
							}
}
/////////////////////////////////////////////////////////////////////////
function fTiresignClick(pEll){
	var a = pEll.attr('class');
						switch(pEll.attr('class')){
							case 'tiresign':
									pEll.addClass('sign');
									pEll.html('-');
									pEll.attr('width','disable');pEll.width(9);
							break;
							case 'tiresign sign':
									pEll.removeClass('sign');
									pEll.addClass('pusto');
									pEll.html('');
									pEll.attr('width','disable');pEll.width(0);
							break;
					
							case 'tiresign pusto':
									pEll.removeClass('pusto');
									pEll.html('_');;
									pEll.attr('width','disable');pEll.width(13);
							break;
	
							}
}
/////////////////////////////////////////////////////////////////////////
function fSlitnoClick(pEll){
	var a = pEll.attr('class');
						switch(pEll.attr('class')){
							case 'slitno':
									pEll.addClass('probel');
									pEll.html(' &nbsp;');
									pEll.attr('width','disable');pEll.width(13);
									pEll.prev().css("margin-right",-1);
							break;
/*							case 'slitno tire':
									pEll.removeClass('tire').addClass('probel');
									pEll.html(' &nbsp;');;
							break;*/
							case 'slitno probel':
									pEll.removeClass('probel').addClass('pusto'); 
									pEll.html('');
									pEll.attr('width','disable');pEll.width(1);
									pEll.prev().css("margin-right",-3.5);  
							break;
							case 'slitno pusto':
									pEll.removeClass('pusto');
									pEll.html('_');;
									pEll.attr('width','disable');pEll.width(13);
									pEll.prev().css("margin-right",-1);
							break;
	
							}
}
/////////////////////////////////////////////////////////////////////////

function fSosedClick(pEll){
	if(pEll.attr('class') == 'sosed'){
		  var nabor = pEll.parent().children('span')
		  var size = nabor.size();
		  for(var i = 0; i < size; i++){
			  if(pEll.attr('id') == nabor.eq(i).attr('id'))
			  fSlitnoClick(nabor.eq(i+1))
			  
		  }
	}
	if(pEll.attr('class') == 'sosedR'){
		  var nabor = pEll.parent().children('span');
		  var size = nabor.size();
		  for(var i = 0; i < size; i++){
			  if(pEll.attr('id') == nabor.eq(i).attr('id')){

			  
			  	  if(nabor.eq(i-1).hasClass('tiresign') )
				 	 fTiresignClick(nabor.eq(i-1));
				  if(nabor.eq(i-1).hasClass('softsign') )
				 	 fSoftsignClick(nabor.eq(i-1));
				  if(nabor.eq(i-1).hasClass('slitno') )
				  	fSlitnoClick(nabor.eq(i-1));
			  }
			  
		  }
	}
	
	if(pEll.attr('class') == 'sosedL'){
		  var nabor = pEll.parent().children('span')
		  var size = nabor.size();
		  for(var i = 0; i < size; i++){
			  if(pEll.attr('id') == nabor.eq(i).attr('id')){
			  
			  	  if(nabor.eq(i+1).hasClass('tiresign') )
				 	 fTiresignClick(nabor.eq(i+1));
				  if(nabor.eq(i+1).hasClass('softsign') )
				 	 fSoftsignClick(nabor.eq(i+1));
				  if(nabor.eq(i+1).hasClass('slitno') )
				  	fSlitnoClick(nabor.eq(i+1));
			  }
			  
		  }
	}
}
////////////////////////////////////////////////////////////

function fWidthEll(Ell){
	switch(Ell.val()){
							case 'й':Ell.css('width','11px'); return true; 
							case 'ц':Ell.css('width','12px'); return true; 
							case 'у':Ell.css('width','12px'); return true; 
							case 'к':Ell.css('width','10px'); return true; 
							case 'е':Ell.css('width','11px'); return true; 
							case 'н':Ell.css('width','11px'); return true; 
							case 'г':Ell.css('width','9px'); return true; 
							case 'ш':Ell.css('width','16px'); return true; 
							case 'щ':Ell.css('width','16px'); return true; 
							case 'з':Ell.css('width','9px'); return true; 
							case 'х':Ell.css('width','12px'); return true; 
							case 'ъ':Ell.css('width','13px'); return true; 
							case 'ф':Ell.css('width','15px'); return true; 
							case 'ы':Ell.css('width','15px'); return true; 
							case 'в':Ell.css('width','11px'); return true; 
							case 'а':Ell.css('width','11px'); return true; 
							case 'п':Ell.css('width','12px'); return true; 
							case 'р':Ell.css('width','11px'); return true; 
							case 'о':Ell.css('width','11px'); return true; 
							case 'л':Ell.css('width','12px'); return true; 
							case 'д':Ell.css('width','13px'); return true; 
							case 'ж':Ell.css('width','13px'); return true; 
							case 'э':Ell.css('width','10px'); return true; 
							case 'я':Ell.css('width','11px'); return true; 
							case 'ч':Ell.css('width','11px'); return true; 
							case 'с':Ell.css('width','10px'); return true; 
							case 'м':Ell.css('width','13px'); return true; 
							case 'и':Ell.css('width','11px'); return true; 
							case 'т':Ell.css('width','10px'); return true; 
							case 'ь':Ell.css('width','11px'); return true; 
							case 'б':Ell.css('width','12px'); return true; 
							case 'ю':Ell.css('width','15px'); return true;
							default:Ell.css('width','13px'); return true;

	
					}	
}
//////////////////////////////////////////////////////////////////
function fStrIns(str, strin, i){
	if(i < str.length - 1)
		return str.substring(0, i+1) + strin + str.substring(i+1);
	else
		return str.substring(0, i+1) + strin;
	
}
/////////////////////////////////////
function f_sipResh(sTarget){if(typeof(sTarget) != 'undefined' && sTarget !== "") return sTarget.substring(0, 11) + "е";}
function fStrReplace(str, strin, i){
	if(i < str.length ){
		if(i < str.length - 1 ) return str.substring(0, i) + strin + str.substring(i+1);
		else return str.substring(0, i) + strin;
	}
	else
		return str;
	
}
///////////////////////////////////////////















///////////////////////////////////////////////////////////////////////
function f_check_answer_rus1(iNumberZad, let){
	 
var trueAnswer1 = $('#idtrueanswerzad'+iNumberZad).val() ;
	 
		if(gi_Answer_send != 11111){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
		gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
	
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
		
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
	

var trueStr = '';
var size = $('#idtextzadachi_'+iNumberZad).children(".r_c").size();
	for(var i = 0; i< size; i++){
trueStr += fTranslate_rgb($('#idtextzadachi_'+iNumberZad).children(".r_c").eq(i).css('color'));
	}
trueStr2 = $('#idtrueanswerzad'+iNumberZad).val()

			if(trueStr == ''){
			g_answerResult = 'Выберете слова';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
if(let == "let")trueStr = fMyCode(trueStr);

		  if(trueStr == trueStr2){
					$('#idanswerResult' + iNumberZad).css('color' , '#090');
					resheno[g_iOpenZad] = true;
					  $('#idanswerzad1' + iNumberZad).attr('readonly', true);
					 if(!gAddingzad) $('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
					  g_answerResult = 'верно';
					  g_iSendZad = iNumberZad;
					  ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					  f_timer_zadach_show();
					  return 'верно';
		  }
		  
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);	
	return 'неверно';
}
//////////////////////////////////////////////////////////////////

//trueStrCl = fMyCode(trueStrCl);
			////trueStrCl = trueStrCl.replace(/ё/g,"е");
			
           //trueStrCl = calcMD5(trueStrCl);////111!!!
function fCalcE(str, arPos){
	var pos = -1;var calc = 0;var i = 0;
 while(  -1 < ( pos = str.indexOf("е", pos+1) )  ){
	 calc++;
	 arPos[i] = pos;
	 i++;
 }
 return calc;
}////////////////////////////////
function fReplace(str, pos, arPos){

	return str.substring(0, arPos[pos]) + "ё" + str.substring(arPos[pos]+1, str.length);
 // trueStrCl = trueStrCl.replace(/е/g,"ё");	
}/////////////////////////////////
function fCompare1002Recurs(trueStrCl, trueAnswer, pos, arPos){

	trueStrCl2 = fMyCode(trueStrCl);trueStrCl2 = calcMD5(trueStrCl2);
	if(trueStrCl2 == trueAnswer){ 
	    return true;}
	if(arPos.length>pos+1){if(fCompare1002Recurs(trueStrCl, trueAnswer, pos+1, arPos)){
		return true;}}
	
	trueStrCl = fReplace(trueStrCl, pos, arPos);	
	trueStrCl2 = fMyCode(trueStrCl);trueStrCl2 = calcMD5(trueStrCl2);
	if(trueStrCl2 == trueAnswer) {
		return true;}
	if(arPos.length>pos+1){if(fCompare1002Recurs(trueStrCl, trueAnswer, pos+1, arPos)){
		return true;}}
	
	return false;
}
/////////////////////
function fCompare1002(trueStrCl, trueAnswer){
	var arPos = new Array();
	var numberE = 0;
	numberE = fCalcE(trueStrCl, arPos);

	
	return fCompare1002Recurs(trueStrCl, trueAnswer, 0, arPos);
}
		  
		  //////////////////////////////////////////////////////////////////
function f_check_answer_rus2(iNumberZad){
//trueAnswer = $('#idtrueanswerzad'+iNumberZad).val()	
	//fCompare1002("е;е;е;", trueAnswer);//1122
	
	
	var bTrueStrCl = true;
	var Nellem;
var trueAnswer1 = $('#idtrueanswerzad'+iNumberZad).val() ;
		if(gi_Answer_send != 11111){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
	
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
		
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
	

var ar = new Array();
var trueStrCl = ''; var trueStrClComma = '';  var trueStrClNe = '';
var size = $('#idtextzadachi_'+iNumberZad).children(".let,.let7").size();
	for(var i = 0; i< size; i++){
		var pLet = $('#idtextzadachi_'+iNumberZad).children(".let,.let7").eq(i);
		if(pLet.val() != "_" && pLet.val() != "" ) trueStrCl += pLet.val() + ';';
		else bTrueStrCl = false;
	}

trueAnswer = $('#idtrueanswerzad'+iNumberZad).val()

			if(!bTrueStrCl){
			g_answerResult = 'Вставьте буквы';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}

 size = $('#idtextzadachi_'+iNumberZad).children(".comma").size();
	for(var i = 0; i< size; i++){
		if ($('#idtextzadachi_'+iNumberZad).children(".comma").eq(i).val() == "")
		trueStrClComma += "l";
		else trueStrClComma += $('#idtextzadachi_'+iNumberZad).children(".comma").eq(i).val();
	}
	if(trueStrClComma.length > 0)
	trueStrCl += "--" + trueStrClComma;
				var regexp  = /,/; 
var bGoodResultComma = regexp.test(trueStrClComma);
			if(!bGoodResultComma  && size){
			g_answerResult = 'поставте знаки препинания';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
			
			
			
			
			var ellNe =  $('#idtextzadachi_'+iNumberZad).children(".slitno") ;
			size = ellNe.size();
			
			if(size == 0){
				ellNe = $('#idtextzadachi_'+iNumberZad).children(".let3").children(".slitno");
			    size = ellNe.size();
			}
			var vmestoNe = "";
	for(var i = 0; i< size; i++){
		if (ellNe.eq(i).html() == ""){
		trueStrClNe += "s;";}
		else {
			    if (ellNe.eq(i).html() == " &nbsp;"){
		         trueStrClNe += "p;";}
			    else{
				     vmestoNe = (ellNe.eq(i).prev().html()+"_").trim();
			        }
		     }
	}
 	
	if(trueStrClNe.length > 0) trueStrCl += "--" + trueStrClNe;				 

			if(trueStrClNe.length/2  != size){
			g_answerResult = "определитесь с написанием "+vmestoNe;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
			
			Nellem = $('#idtextzadachi_'+iNumberZad).children(".softsign");
			size = Nellem.size();
			var trueStrClSS = "";
					for(var i = 0; i< size; i++){
						if (Nellem.eq(i).html() == "") trueStrClSS += "1;";
						if (Nellem.eq(i).html() == "_") trueStrClSS += "";
						if (Nellem.eq(i).html() == "ь") trueStrClSS += "3;";
					}			
if(trueStrClSS.length > 0) trueStrCl += "--" + trueStrClSS;				 

			if(trueStrClSS.length/2  != size){
			g_answerResult = "определитесь с написанием 'ь'";
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
			
			
	/////////		
				Nellem = $('#idtextzadachi_'+iNumberZad).children(".tiresign");
			size = Nellem.size();
			var trueStrClTS = "";
					for(var i = 0; i< size; i++){
						var utr = Nellem.eq(i).html();
						if (Nellem.eq(i).html() == "") trueStrClTS += "1;";
						if (Nellem.eq(i).html() == "_") trueStrClTS += "";
						if (Nellem.eq(i).html() == "-") trueStrClTS += "3;";
					}			
if(trueStrClTS.length > 0) trueStrCl += "--" + trueStrClTS;				 

			if(trueStrClTS.length/2  != size){
			g_answerResult = "определитесь с написанием '-'";
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}		
	//////////		
			
			//trueStrCl = fMyCode(trueStrCl);
			////trueStrCl = trueStrCl.replace(/ё/g,"е");
			
           //trueStrCl = calcMD5(trueStrCl);////111!!!

		  if(fCompare1002(trueStrCl, trueAnswer)){//if(trueStrCl == trueAnswer){
					$('#idanswerResult' + iNumberZad).css('color' , '#090');
					resheno[g_iOpenZad] = true;
					  $('#idanswerzad1' + iNumberZad).attr('readonly', true);
					 if(!gAddingzad) $('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
					  g_answerResult = 'верно';
					  g_iSendZad = iNumberZad;
					  ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					  f_timer_zadach_show();
					  return 'верно';
		  }
		  
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);	
	return 'неверно';
}
//////////////////////////////////////////////////////////////////
function f_check_answer_rus3(iNumberZad){
	var bTrueStrCl = true;
var trueAnswer1 = $('#idtrueanswerzad'+iNumberZad).val() ;
		if(gi_Answer_send != 11111){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
	
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
		
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
	


	var trueStrCl = fCodeAnswPWCl(iNumberZad); 
	var bTrueStrCl = true;
		  var allRe = /l/g;  
		if(trueStrCl.replace(allRe, "") == "") bTrueStrCl = false;
		
trueAnswer = $('#idtrueanswerzad'+iNumberZad).val()

			if(!bTrueStrCl){
			g_answerResult = 'Выберите части слова';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}



			
trueStrCl = calcMD5(trueStrCl);

		  if(trueStrCl == trueAnswer){
					$('#idanswerResult' + iNumberZad).css('color' , '#090');
					resheno[g_iOpenZad] = true;
					  $('#idanswerzad1' + iNumberZad).attr('readonly', true);
					 if(!gAddingzad) $('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
					  g_answerResult = 'верно';
					  g_iSendZad = iNumberZad;
					  ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					  f_timer_zadach_show();
					  return 'верно';
		  }
		  
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);	
	return 'неверно';
}
//////////////////////////////////////////////////////////////////

function f_check_answer_rus5(iNumberZad){
	var bTrueStrCl = true;
var trueAnswer1 = $('#idtrueanswerzad'+iNumberZad).val() ;
		if(gi_Answer_send != 11111){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
	
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
		
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
	


var trueStrCl = fCodeAnswSelWord($("#idtextzadachi_"+iNumberZad));
	

trueAnswer = $('#idtrueanswerzad'+iNumberZad).val()

			if(trueStrCl.indexOf("3") == -1){
			g_answerResult = 'Выбери варианты ответа';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}	
	
trueStrCl = calcMD5(trueStrCl);

		  if(trueStrCl == trueAnswer){
					$('#idanswerResult' + iNumberZad).css('color' , '#090');
					resheno[g_iOpenZad] = true;
					  $('#idanswerzad1' + iNumberZad).attr('readonly', true);
					 if(!gAddingzad) $('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
					  g_answerResult = 'верно';
					  g_iSendZad = iNumberZad;
					  ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					  f_timer_zadach_show();
					  return 'верно';
		  }
		  
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);	
	return 'неверно';
}
//////////////////////////////////////////////
function f_check_answer_rus6(iNumberZad){//11 10 07 2011
	var bTrueStrCl = true;
var trueAnswer1 = $('#idtrueanswerzad'+iNumberZad).val() ;
		if(gi_Answer_send != 11111){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;	
		
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
		
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
	

var trueArCl = new Array();
trueArCl = fCodeAnsClForCheck1006(iNumberZad);


trueAnswer = fCodeTrueAnsForCheck1006(iNumberZad);

			if(!trueArCl[1111]){
			g_answerResult = 'Введите все ответы';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
			delete trueArCl[1111];
		var bTrueAns = true;
		for(var i = 0; i < trueAnswer.length; i++){
			var b = false;
			for(var j = 0; j < trueAnswer[i].length; j++){
				trueArCl[i] = trueArCl[i].replace(/ё/g,"е");
				trueAnswer[i][j] = trueAnswer[i][j].replace(/ё/g,"е");
				if(trueArCl[i] === trueAnswer[i][j]){b = true;}
			}
			if(!b){bTrueAns = false;}
		}

		  if(bTrueAns){
					$('#idanswerResult' + iNumberZad).css('color' , '#090');
					resheno[g_iOpenZad] = true;
					  $('#idanswerzad1' + iNumberZad).attr('readonly', true);
					 if(!gAddingzad) $('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
					  g_answerResult = 'верно';
					  g_iSendZad = iNumberZad;
					  ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
					  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
					  f_timer_zadach_show();
					  return 'верно';
		  }
		  
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);	
	return 'неверно';
}
/////////////////////////////////////////////////////
function fCodeAnsClForCheck1006(iNumberZad){
	var l = "";
	var k = 0;
	var iCols = $("#idnumcol"+iNumberZad).val();
	var iRows = $("#idnumraw"+iNumberZad).val();
	var ar  = new Array();
	for(var i = 0; i < iRows; i++){		 
		for(var j = 0; j < iCols; j++){
			l = $("#idanswer_"+iNumberZad+"_"+i+"_"+j).val().trim();
			if(l === ""){ar[1111] = false;return ar;}
			ar[k] = (l); //11 calcMD5 
			k++;
		}
	}
ar[1111] = true;
	return ar;
}/////////////////////////////////////////////
function fCodeTrueAnsForCheck1006(iNumberZad){
	var l = "";
	var k = 0;
	var iCols = $("#idnumcol"+iNumberZad).val();
	var iRows = $("#idnumraw"+iNumberZad).val();
	var ar  = new Array();
	ar = $("#idtrueanswerzad"+iNumberZad).val().split(";;");
	var ar2 = new Array();
	for(var i = 0; i < ar.length; i++){
		 ar2[i] = new Array();
		 if(/::/g.test(ar[i])){ar2[i] = ar[i].split("::");}
		 else{ar2[i][0] = ar[i]}	
	}
	return ar2;
}//11 10 07 2011
	  function removeSpaces(s) 
	  {
		  var allSpacesRe = /\s+/g;
		  
		  var ss = s.replace(allSpacesRe, "");
		 
		  return  ss.replace(",", ".");
	  }

///////////////////////////////////////
	  
	function removeRus(s) 
	  { 
		if((/[а-я]/).test(s)){
			
		  var allRe = /а/g;
		  var ss = s.replace(allRe, "a");
		  
		  var allRe = /с/g;
		  var ss = ss.replace(allRe, "c");
		  
		  var allRe = /в/g;
		  var ss = ss.replace(allRe, "b");
		  
		  var allRe = /м/g;
		  var ss = ss.replace(allRe, "m");
		  
		  var allRe = /о/g;
		  var ss = ss.replace(allRe, "o");
		  
		  var allRe = /р/g;
		  var ss = ss.replace(allRe, "p");
		  
		  		  
		  var allRe = /н/g;
		  var ss = ss.replace(allRe, "h");		  
		  var allRe = /е/g;
		  var s = ss.replace(allRe, "e");
		  
		  
		}// if((/^([а-я]){1,15}$/i).test(s)){
		 
		  return  s;
	  }// function removeRus(s) 
	  
	  
function fTranslate_rgb(rgb_str){
	
	switch(rgb_str){
		case "rgb(0, 144, 192)": return "1";
		case "rgb(0, 144, 193)": return "pris";
		case "rgb(0, 144, 194)": return "root";
		case "rgb(0, 144, 195)": return "sufix";
		case "rgb(0, 144, 196)": return "postf";
		case "rgb(0, 144, 197)": return "end";
		case "rgb(0, 144, 198)": return "et";
		case "rgb(0, 144, 199)": return "mn";
		case "rgb(48, 0, 0)": return "3";
		
		case "#0090c0": return "1";
		case "#0090c1": return "pris";
		case "#0090c2": return "root";
		case "#0090c3": return "sufix";
		case "#0090c4": return "postf";
		case "#0090c5": return "end";
		case "#0090c6": return "et";
		case "#0090c7": return "mn";
		case "#300000": return "3";
		default:return "";
	}
return "";
}	  
function fCodeAnswPWCl(numberzadachi){
	nzadachi = numberzadachi || g_iOpenZad;
var pWords = $("#idtextzadachi_"+nzadachi).children("span");
var sizeText = pWords.size();
var sAnsw = "";
var arAnswer = new Array();
	  for(var i = 0; i < sizeText; i++){
		var sizeWord = pWords.eq(i).children(".partword").size();
			for(var j = 0; j < sizeWord; j++){
				arAnswer[i] = arAnswer[i] || "";
				  arAnswer[i] += fTrnsltPWCl( pWords.eq(i).children(".partword").eq(j).attr('class') );
				  
			}//for(var j = 0; j < sizeWord; j++){
				if( arAnswer[i].indexOf("sl") != -1 &&  arAnswer[i].indexOf("s2l") != -1 ){
					if( arAnswer[i].indexOf("sl") >  arAnswer[i].indexOf("s2l") ){
							arAnswer[i] = arAnswer[i].replace(/sl/g, "gg");
							arAnswer[i] = arAnswer[i].replace(/s2l/g, "sl");
							arAnswer[i] = arAnswer[i].replace(/gg/g, "s2l");
					}	
				}
					  if( arAnswer[i].indexOf("rl") != -1 &&  arAnswer[i].indexOf("r2l") != -1 ){
						  if( arAnswer[i].indexOf("rl") >  arAnswer[i].indexOf("r2l") ){ 
								  arAnswer[i] = arAnswer[i].replace(/rl/g, "gg");
								  arAnswer[i] = arAnswer[i].replace(/r2l/g, "rl");
								  arAnswer[i] = arAnswer[i].replace(/gg/g, "r2l");
						  }  
					  }	
			if( arAnswer[i].indexOf("rl") == -1 &&  arAnswer[i].indexOf("r2l") != -1 ){						
						arAnswer[i] = arAnswer[i].replace(/r2l/g, "rl");	  
			}
			if( arAnswer[i].indexOf("sl") == -1 &&  arAnswer[i].indexOf("s2l") != -1 ){						
						arAnswer[i] = arAnswer[i].replace(/s2l/g, "sl");	  
			}
					  
					  
	  }//for(var i = 0; i < sizeText; i++){

 for(var k = 0; k < arAnswer.length; k++){
	 sAnsw += arAnswer[k];
 }
	  return sAnsw;
}
///////////////////////////////////////////////////////////////////
function fCodeAnswSelWord(pEl){
		var nEl = pEl.children('.selword');
		var nElS = pEl.children('span.selword');
		var nElI = pEl.children('input.selword');
		var size = nEl.size();
		var sizeS = nElS.size();
		var sizeI = nElI.size();
		var bS = size==sizeS;
		var bI = size==sizeI;
		var sTrueAns = "";
		 for(var k = 0; k < size; k++){

			 if((bI && nElI.eq(k).val().length > 1) || (bS && nElS.eq(k).html().length > 1) )
			 sTrueAns += fTranslate_rgb(nEl.eq(k).css("color"));
		 }
		 
		
	return 	sTrueAns;
}
/////////////////////////////////////////////////////////////////////////
function fTrnsltPWCl(pClass){
	
	  var ar = new Array(); 
	  ar = pClass.split(' '); pClass = ar[1];
	
	switch(pClass){
		case "pris": return "prl";
		case "root": return "rl";
		case "sufix": return "sl";
		case "roo2": return "r2l";
		case "sufi2": return "s2l";
		case "postf": return "pol";
		case "end": return "el";

		default:return "l";
	}
return "";
}
	  
	  
	  var g_timer_chekanswer = 0;
var  g_answerResult='';
var  g_iSendZad='';
var g_id_page ;
var gi_time_pause_zad_etalon = 500;
var ga_id_zad = new Array();
var ga_time_pause_zad = new Array();
var gi_Answer_send = 11111;
var gi_timeout_zad = 2000;
var gAddingzad;//при добавлении задач кнопка Проверить работает постоянно True в add_z_next_prev.js 
var gKeycode = 0;
var gKeyUpID = 0;

var gPartOfWord = new Array();
gPartOfWord[0] = 'pris';
var gSoftorTireSign = 'sign';
var gb_type_zad_9 = false;
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////
//////////////////////////////////////////////
function f_check_answer_331(iNumberZad, countAnswers){	
countAnswers = countAnswers || 1;	
var bool = f_check_answer_begin_text(iNumberZad, countAnswers);
if(!bool || bool == 'lazy') return false;
/// 1
	 g_aswerClient[1] = calcMD5(g_aswerClient[1]);
	 var b2 = true;
	 if(countAnswers == 2){
		 g_aswerClient[2] = calcMD5(g_aswerClient[2]);
		 if(g_trueAnswer2 != g_aswerClient[2]){b2 = false;}
		 }// 1 //// 33
var trueStrCl = fCodeAnswSelWord($("#idtextzadachi_"+iNumberZad));
trueAnswer = $('#idtrueanswerzad_'+iNumberZad).val()
			if(trueStrCl.indexOf("3") == -1){
			  g_answerResult = 'Выбери варианты ответа';
			  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			  return 'lazy';
			}		
trueStrCl = calcMD5(trueStrCl);// 33 //

	  if(g_trueAnswer1 == g_aswerClient[1] && b2 && trueStrCl == trueAnswer){
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad + ', #idanswerzad2'+ iNumberZad ).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  		return 'верно';
	  }
	  		
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
		
	return 'неверно';	
}
//////////////////////////////////////////////
function f_check_answer_1(iNumberZad, countAnswers){
	

countAnswers = countAnswers || 1;	
var bool = f_check_answer_begin_text(iNumberZad, countAnswers);
if(!bool || bool == 'lazy') return 'lazy';

	 g_aswerClient[1] = calcMD5(g_aswerClient[1]);
	 var b2 = true;
	 if(countAnswers == 2){
		 g_aswerClient[2] = calcMD5(g_aswerClient[2]);
		 if(g_trueAnswer2 != g_aswerClient[2]){b2 = false;}
		 }

	  if(g_trueAnswer1 == g_aswerClient[1] && b2){
		  
		if(gb_type_zad_9){
			return true;}
	  
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad + ', #idanswerzad2'+ iNumberZad ).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  		return 'верно';
	  }
	  		
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
		
	return 'неверно';	
}
//////////////////////////////////////////////
function f_check_answer_31(iNumberZad, bCheckMultiple, sSymbols){
	
var bool = f_check_answer_begin_text(iNumberZad, 1);
if(!bool || bool == 'lazy') return 'lazy';
 
 var strbr = '';
 	  if((strbr = fChekRightLeftBrackets(g_aswerClient[1], 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  					g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }

		  /////////////////////
		  var bExtraSymbol = false; var sExtraSymbol = '';
		  		var ssttrr = '[0-9'+sSymbols+'\\(\\)\^+\-]';// \(\)\+\-\^\*
				
			  for(var i = 0; i < g_aswerClient[1].length; i++){//проверим ответ на лишние переменные
			  var regexp  = new RegExp(ssttrr,'g');
			  var sss = g_aswerClient[1].substr(i, 1);//11
						if(!regexp.test(g_aswerClient[1].substr(i, 1) ) ){
							bExtraSymbol = true; sExtraSymbol = g_aswerClient[1].substr(i, 1); break;
						}
			  } if(bExtraSymbol){
				  $('#idanswerResult' + iNumberZad).css('width', '350px');
					g_answerResult = "В ответе не должно быть ";
					var regexp  = new RegExp('[a-z]','g');
					if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "переменной - " + sExtraSymbol;}
					else{
						var regexp  = new RegExp('[А-Яа-я]','g');
						if(regexp.test(g_aswerClient[1].substr(i, 1) ) ){g_answerResult += "русской буквы - " + sExtraSymbol;}
						else {g_answerResult += "символа  " + sExtraSymbol;}
			 		 }
					g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
				}
				//////////////
				
 			var aswerClient1 = fPrivedMchlenStandart("("+g_aswerClient[1]+")");
			aswerClient1 = calcMD5(String(aswerClient1));
	  if(g_trueAnswer1 == aswerClient1){
		  var ttttt = fCheckMultiples(iNumberZad);//11
		  if(bCheckMultiple && !fCheckMultiples(iNumberZad)){return false;}//если надо было разложитьна множители

			if(gb_type_zad_9){g_answerResult = 'верно';
			return true;}	
		  
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  		return 'верно';
	  }
	  		
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
		
	return 'неверно';
}//31
//////////////////////////////////////////////
function f_check_answer_9(iNumberZad, iCountAnswer){
	gb_type_zad_9 = true;
	
	for(var i = 0; i < iCountAnswer; i++){
		g_AddingNumAns = "_"+i;
		var iTypeAns = $("#idtypeanswerzad_"+iNumberZad+"_"+i).val();
		var b = window['f_check_answer_'+iTypeAns](iNumberZad, false, $("#idsymbols_"+iNumberZad+"_"+i).val() );
		if(b == 'lazy'){
			return 'lazy';}
		
		if(b == 'неверно'){
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return false;
		}
		if(/должно/g.test(g_answerResult)){//g_answerResult == "В ответе не должно быть "
			//g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return false;
		}

	}
	
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad + ', #idanswerzad2'+ iNumberZad ).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  	
			
	g_AddingNumAns = "";gb_type_zad_9 = false;
		return 'верно';
}
//////////////////////////////////////////////
function f_check_answer_2(iNumberZad){	

var bool = f_check_answer_begin_text(iNumberZad, 2);
if(!bool || bool == 'lazy') return false;

	var g_aswerClient1MD5 = calcMD5(g_aswerClient[1]);
	var g_aswerClient2MD5 = calcMD5(g_aswerClient[2])

	  if(g_trueAnswer1 == g_aswerClient1MD5 && g_trueAnswer2 == g_aswerClient2MD5){
				fSetResult('верно', iNumberZad);return true;
	  }else{

		for(var l = 2 ; l < 1166; l++){
		 	 	var gg1 = calcMD5(parseFloat(g_aswerClient[1] / l)+'');
		 	 	var gg2 = calcMD5(parseFloat(g_aswerClient[2] / l)+'');
			if(g_trueAnswer1 === gg1 && g_trueAnswer2 === gg2){fSetResult('Сократи дробь', iNumberZad);return false;}
		}// for(l = 1 ; l < 66; l++){
	
		  
	  }// }else{   if(g_trueAnswer1 == g_aswerClient[1] && g_trueAnswer2 == g_aswerClient[2]){
	  		
		fSetResult('неверно', iNumberZad, true); return false;		
}
//////////////////////////////////////////////
function f_check_answer_3(iNumberZad){
	
var bool = f_check_answer_begin_text(iNumberZad, 3);
if(!bool || bool == 'lazy') return false;

	var g_aswerClient1MD5 = calcMD5(g_aswerClient[1]);
	var g_aswerClient2MD5 = calcMD5(g_aswerClient[2])
	var g_aswerClient3MD5 = calcMD5(g_aswerClient[3]);

	  if(g_trueAnswer1 == g_aswerClient1MD5 && g_trueAnswer2 == g_aswerClient2MD5 && g_trueAnswer3 == g_aswerClient3MD5){
			fSetResult('верно', iNumberZad);return true;
	  }else{					   
		if(g_trueAnswer1 == g_aswerClient1MD5){
			for(var i = 1 ; i < 1166; i++){
		 	 var gg2 = calcMD5(parseFloat(g_aswerClient[2] / i)+'');
		 	 var gg3 = calcMD5(parseFloat(g_aswerClient[3] / i)+'');
	
				 if(  g_trueAnswer2 === gg2 && g_trueAnswer3 === gg3 ){fSetResult('Сократи дробь', iNumberZad);return false;}

			}// for(var i = 1 ; i < 1166; i++){
		}else{//if(g_trueAnswer1 == g_aswerClient[1]MD5){
		  if(parseInt(g_aswerClient[2], 10) > parseInt(g_aswerClient[3], 10) ){

			for(var j = 1 ; j < parseInt(g_aswerClient[2] / g_aswerClient[3] + 1, 10); j++){
				var g_aswerClient2Minus = calcMD5((g_aswerClient[2] - g_aswerClient[3] * j) + '');
				var g_aswerClient1Plus = calcMD5((g_aswerClient[1] + j) + '');
					if(g_trueAnswer1 == g_aswerClient1Plus && g_trueAnswer2 == g_aswerClient2Minus && g_trueAnswer3 == g_aswerClient3MD5){
								fSetResult('Выдели целую часть из неправильной дроби!', iNumberZad);return false;
					}else{
						for(var i = 1 ; i < 1166; i++){
						 var gg2 = calcMD5(parseFloat((g_aswerClient[2] - g_aswerClient[3] * j) / i)+'');
						 var gg3 = calcMD5(parseFloat(g_aswerClient[3] / i)+'');
				
							 if(  g_trueAnswer2 === gg2 && g_trueAnswer3 === gg3 ){ 
								fSetResult('Выдели целую часть из неправильной дроби!', iNumberZad);return false;//и сократи дробь
							 }
			
						}
					}
			}
		  }//if(g_aswerClient[2] > g_aswerClient[3])
		  
		}//}else{//if(g_trueAnswer1 == g_aswerClient[1]MD5){
								  
	 }//else  if(g_trueAnswer1 == g_aswerClient[1] && g_trueAnswer2 == g_aswerClient[2] && g_trueAnswer3 == g_aswerClient[3]){		  
		  	  
	  		
			fSetResult('неверно', iNumberZad, true);
	
	return false;	
}
//////////////////////////////////////////////





////////////////////////////////////////////////
function f_check_answer_32(iNumberZad, sSymbols1, sSymbols2){
	
 if(sSymbols2 === '' && removeSpaces( $('#idanswerzad2' + iNumberZad).val()) === ''){$('#idanswerzad2' + iNumberZad).val(1);}	
var bool = f_check_answer_begin_text(iNumberZad, 2);
if(!bool || bool == 'lazy') return false;
 	if(sSymbols2 === '' && parseInt(g_aswerClient[2], 10) === 1){
			 $('#idanswerzad2' + iNumberZad).val('');
			 $('#idtextzadachiVirazen2' + iNumberZad).html('');
	 }	
 var strbr = '';
 	  if((strbr = fChekRightLeftBrackets(g_aswerClient[1], 0)) !== ''){
	 		$('#idanswerResult' + iNumberZad).css('width', '300px');
	  					g_answerResult = strbr;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
	  }

		  /////////////////////
		  
		  		
  for(var j = 1; j < 3; j++){//проверим ответы на лишние переменные
	  var bExtraSymbol = false; var sExtraSymbol = '';	
  	if(j == 1){var ssttrr = '[0-9'+sSymbols1+'\^+\-]';}// \(\)\+\-\^\*
	else{var ssttrr = '[0-9'+sSymbols2+'\^+\-]';}// \(\)\+\-\^\*	
			  for(var i = 0; i < g_aswerClient[j].length; i++){
			  var regexp  = new RegExp(ssttrr,'g');
			  var sss = g_aswerClient[j].substr(i, 1);//11
						if(!regexp.test(g_aswerClient[j].substr(i, 1) ) ){
							bExtraSymbol = true; sExtraSymbol = g_aswerClient[j].substr(i, 1); break;
						}
			  } if(bExtraSymbol){
				  $('#idanswerResult' + iNumberZad).css('width', '390px');
					if(j == 1){g_answerResult = "В числителе не должно быть ";}
					else{g_answerResult = "В знаменателе не должно быть ";}
					var regexp  = new RegExp('[a-z]','g');
					if(regexp.test(g_aswerClient[j].substr(i, 1) ) ){g_answerResult += "переменной - " + sExtraSymbol;}
					else{
						var regexp  = new RegExp('[А-Яа-я]','g');
						if(regexp.test(g_aswerClient[j].substr(i, 1) ) ){g_answerResult += "русской буквы - " + sExtraSymbol;}
						else {g_answerResult += "символа  " + sExtraSymbol;}
			 		 }
					g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);return false;
				}
				//////////////
  }//for(var j = 1; j < 3; j++){
 		var aswerClient1 = MultipleMchlen(fPrivedMchlenStandart(g_aswerClient[1]), '1');
			aswerClient1 = calcMD5(String(aswerClient1));
		var aswerClient2 = MultipleMchlen(fPrivedMchlenStandart(g_aswerClient[2]), '1');
			aswerClient2 = calcMD5(String(aswerClient2));
		var aswerClient3 = MultipleMchlen(fPrivedMchlenStandart(g_aswerClient[1]), '-1');
			aswerClient3 = calcMD5(String(aswerClient3));
		var aswerClient4 = MultipleMchlen(fPrivedMchlenStandart(g_aswerClient[2]), '-1');
			aswerClient4 = calcMD5(String(aswerClient4));
if( (g_trueAnswer1 == aswerClient1 && g_trueAnswer2 == aswerClient2 ) || (g_trueAnswer1 == aswerClient3 && g_trueAnswer2 == aswerClient4 ) ){
	
		  $('#idanswerResult' + iNumberZad).css('color','#090');
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad).attr('readonly', true);
			$('#idanswerzad2' + iNumberZad).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			g_answerResult = 'верно';
			g_iSendZad = iNumberZad;
			ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			f_timer_zadach_show();
	  		return 'верно';
	  }
	  		
			g_answerResult = 'неверно';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
		
	return 'неверно';
}


//////////////////////////////////////////////////////////////////
function fSetResult(str, iNumberZad, bTimeEtalonNOChange){
	if(str == 'верно'){
		$('#idanswerResult' + iNumberZad).css('color','#090');
		
		  resheno[g_iOpenZad] = true;
			$('#idanswerzad1' + iNumberZad + ', #idanswerzad2'+ iNumberZad + ', #idanswerzad3'+ iNumberZad ).attr('readonly', true);
			$('#idbutcheck' + iNumberZad).attr('disabled', 'disabled');
			f_timer_zadach_show();
	}
	
		if(str.indexOf('!')!== -1){
		$('#idanswerResultLong' + iNumberZad).css('width',str.length + 'em');
		$('#idanswerResultLong' + iNumberZad).css('color','#e00');
		$('#idanswerResultLong' + iNumberZad).html(str);
		g_answerResult = '';	
		}else{
		$('#idanswerResultLong' + iNumberZad).css('width',20 + 'em');
		$('#idanswerResultLong' + iNumberZad).css('color','#600');
		$('#idanswerResultLong' + iNumberZad).html('');
		g_answerResult = str;	
		}
bTimeEtalonNOChange = bTimeEtalonNOChange || false;

	
	g_iSendZad = iNumberZad;
	if(!bTimeEtalonNOChange){ga_time_pause_zad[g_iOpenZad] = gi_time_pause_zad_etalon;}
	g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
}
//////////////////////////////////////////////////









	  
	  

function f_CheckToSokrDrob(sChisl, sZnamen){
	sZnamen = sZnamen || '';
	sChisl = sChisl + '+' +  sZnamen;
var strChislPlus = sChisl.replace(/\+/g,'-');if(strChislPlus.substr(0, 1) == '-'){strChislPlus = strChislPlus.substr(1);}
var strZnamenPlus = sZnamen.replace(/\+/g,'-');if(strZnamenPlus.substr(0, 1) == '-'){strZnamenPlus = strZnamenPlus.substr(1);}
var arChisl = strChislPlus.split('-');
var arZnamen = new Array();
 arZnamen = strZnamenPlus.split('-');
var bRes = false; var sRezLetter = '';
		for(var i = 0 ; i < arChisl.length; i++){
			var str = arChisl[i]; var sDigit = ''; var j = 0;
			while ( new RegExp('\\d','g').test(str.substr(j, 1)) ){sDigit += str.substr(j, 1); j++;}
			var str2 = '';
				for( ; j < str.length; j++){
						if(/[a-z]/g.test(str.substr(j,1))){ str2 += str.substr(j,1);}
				}
			
			arChisl[i] = new Array(sDigit, str2);
		}


	// проверка по совпадению букв. множ во всех одночленах
		for(var j = 0 ; j < arChisl[0][1].length; j++){
			bRes = true;
				for(var k = 1 ; k < arChisl.length; k++){
					var ss = arChisl[0][1].substr(j, 1);
					if(! new RegExp(ss,'g').test(arChisl[k][1]) ){
						bRes = false; 
						}
				}
				
				if(bRes){
					sRezLetter = arChisl[0][1].substr(j, 1);
					break;
				}
		}
		
		// проверка по совпадению цифровых. множ во всех одночленах
		var arProstChisla = new Array(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149);
		var iObshDelitel = 1;var bResChisl= true;
		for(var j = 0 ; j < arProstChisla.length; j++){
			bResChisl = true;
				for(var k = 0 ; k < arChisl.length; k++){
					//11
					var ss11 = arChisl[k][0];var ss22 = arProstChisla[j];
					var aa11 = ss11 % ss22;
					if(aa11 === 0)
						var aaaa1111 =  0;
					else
						var aaaa1111 =  0;
					   //11
					if( (arChisl[k][0] == "" || arChisl[k][0]%arProstChisla[j] !== 0) ){bResChisl = false;} 
				}
				if(bResChisl){iObshDelitel = arProstChisla[j]; break;}
		}
if(bResChisl){bRes = true;}
if(iObshDelitel == '1'){iObshDelitel = '';}
var ar = new Array(bRes, sRezLetter, iObshDelitel);	
return ar;	
}
/////////////////////////////////////////////////////////////////////

function f_check_answer_begin_text(iNumberZad, countAnswers){
	var bEmpty1 = false;var bEmpty2 = false;var bEmpty3 = false;
	 g_trueAnswer1 = removeSpaces($('#idtrueanswerzad1_'+iNumberZad+g_AddingNumAns).val());
	 g_aswerClient[1] =removeSpaces( $('#idanswerzad1' + iNumberZad+g_AddingNumAns).val()) ;
 
if(countAnswers > 1){
  g_trueAnswer2 = removeSpaces($('#idtrueanswerzad2_'+iNumberZad+g_AddingNumAns).val());
 g_aswerClient[2] = removeSpaces($('#idanswerzad2' + iNumberZad+g_AddingNumAns).val()) ;
}
if(countAnswers > 2){
  g_trueAnswer3 = removeSpaces($('#idtrueanswerzad3_'+iNumberZad+g_AddingNumAns).val());
 g_aswerClient[3] = removeSpaces($('#idanswerzad3' + iNumberZad+g_AddingNumAns).val()) ;
}	

		if(gi_Answer_send != 11111 && gi_Answer_send !== g_iOpenZad){	
			if(gi_Answer_send != g_iOpenZad) alert('Дождитесь ответа или полностью решите задание '+(gi_Answer_send+1));		
			return false;
		}
	gi_Answer_send = g_iOpenZad;
	ga_time_pause_zad[g_iOpenZad] = ga_time_pause_zad[g_iOpenZad] || gi_time_pause_zad_etalon;
		$('#idanswerResult' + iNumberZad).val('');
		$('#idanswerResult' + iNumberZad).css('background-image', 'url(http://school-assistant.ru/images/main/loadsmall.gif)')
  		$('#idanswerResult' + iNumberZad).css('color', '#f00');
	
			g_iSendZad = iNumberZad;
			if(ga_time_pause_zad[g_iOpenZad]> 10000)
				alert('Подумайте над задачей повнимательнее. Прочтите правила. ' );
			if(ga_time_pause_zad[g_iOpenZad]> 2000 && !gb_type_zad_9)
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 2000;
			ga_time_pause_zad[g_iOpenZad]= ga_time_pause_zad[g_iOpenZad]+ 1000;
			
	bEmpty1 = (g_aswerClient[1] === '');
	if(countAnswers > 1) {bEmpty2 = (g_aswerClient[2] === '' );}
	if(countAnswers > 2) {bEmpty3 = (g_aswerClient[3] === '' );}
	
			if(bEmpty1 || bEmpty2  || bEmpty3){
			g_answerResult = 'Введите ответ';
			g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
			return 'lazy';
			}
			
			return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


function sortanswer(str){
	var j = 0; var i = 0;  var g = 0; var strnew = '';
	
//str = "2а -4аd+ 4сa";
str = removeSpaces(str);
str = removeRus(str);
var str1 = str.charAt(0);

if(str1 != '-' && str1 != '+') str = '+' + str;
		  
		  var strPlus = str.replace(/\+/g, "-");
		 var indexArray = new Array();
 
	while ( g != -1){	  
		g = strPlus.indexOf('-',j);
		if(g!= -1) indexArray[i] = g;
		  j = indexArray[i] + 1;
		  i++;
		  if(i > 10) break;
	}
	var strArray = new Array();
	for(i = 0; i < indexArray.length; i++){
		if(i < indexArray.length - 1)g = indexArray[i+1];
		else g = str.length;
		strArray[i] = sortSubStr(str.substring(indexArray[i],g));
	}
	strArray = strArray.sort();
	for(i = 0; i < strArray.length; i++){
		strnew = strnew + strArray[i];
	}
	return strnew;
}
//////////////////////////////////
function sortSubStr(str){
var i = 0; var j = 0; var strnew = '';
var subStrArray = new Array();
	for(i = 0; i < str.length; i++,j++){
		if(str.charAt(i+1) == '^'){
		subStrArray[j] = str.charAt(i) + str.charAt(i+1) + str.charAt(i+2);	
		i = i + 2;
		
		}else
		subStrArray[j] = str.charAt(i)
	}
	
	subStrArray = subStrArray.sort();
	
	for(i = 0; i < subStrArray.length; i++){
		strnew = strnew + subStrArray[i];
	}
	return strnew;
}
	///////////////////////////////////////////////////////////////////////////

function fInteractiveKeyboardStrHTML(textZadachi){
var str = "<div class='interactivekeyboardBox'>";
    str += "<table style='width:800px;!important'><tr>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('a',0,'no');\">a</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('b',0,'no');\">b</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('c',0,'no');\">c</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('d',0,'no');\">d</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('e',0,'no');\">e</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('k',0,'no');\">k</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('l',0,'no');\">l</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('m',0,'no');\">m</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('n',0,'no');\">n</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('x',0,'no');\">x</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('y',0,'no');\">y</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('z',0,'no');\">z</td>";
	str += "<td rowspan = '5'> &nbsp; &nbsp; </td>"; 
	str += "<td rowspan = '5' class='textzadachi'>"+textZadachi+"</td>"; 
	str += "  </tr><tr>";
    str += "<td class='interactivekeyboard'></td>";
 	str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('.');\">.</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('0');\">0</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('1');\">1</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('2');\">2</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('3');\">3</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('4');\">4</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('5');\">5</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('6');\">6</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('7');\">7</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('8');\">8</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('9');\">9</td>";
	
    str += "  </tr><tr>";
    str += "<td class='interactivekeyboard3' colspan='4'></td>";
  
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('2',1,'no');\">x<sup>2</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('3',1,'no');\">x<sup>3</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('4',1,'no');\">x<sup>4</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('5',1,'no');\">x<sup>5</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('6',1,'no');\">x<sup>6</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('7',1,'no');\">x<sup>7</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('8',1,'no');\">x<sup>8</sup></td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw('9',1,'no');\">x<sup>9</sup></td>";
  

    str += "  </tr><tr>";
	str += "<td class='interactivekeyboard4' colspan='6' onClick=\"fIntKeyDraw('delete');\">стереть</td>";
    str += "<td class='interactivekeyboard' style='font-size: 16px;' onClick=\"fIntKeyDraw('( ',false,'no');\">(</td>";
    str += "<td class='interactivekeyboard' style='font-size: 16px;' onClick=\"fIntKeyDraw(' )',false,'no');\">)</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw(' + ',false,'no');\">+</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw(' - ',false,'no');\">&#8211;</td>";
    str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw(' * ',false,'no');\">&bull;</td>";
	
	var gg = typeof(gTypeZad);//11
			if(typeof(gTypeZad) !== 'undefined' && gTypeZad == 31 && giStep == 6){
				str += "<td class='interactivekeyboard' onClick=\"fIntKeyDraw(' &nbsp; &nbsp; = &nbsp; &nbsp; ',false,'no');\">=</td>";}
			else{
				str += "<td class='interactivekeyboard'></td>";}
	
   //11 
	str += "</tr><td colspan='7'>&nbsp;</td></tr>";	
	str += "</tr></table>";
	

	str += "</div>";
    
 

  //  str += "  </tr><tr>";
  //	str += "<td colspan='3'></td>";
  //  str += "<td colspan='9'class='dialog_InteractiveKeyboardClose'><br>Закрыть интерактивную клавиатуру</td>";
    
	return str;
	}
///////////////////////////////////////
function fInteractiveKeyboardOpen(strEl){
	var el = $(strEl);
	ga_InteractiveKeyboardCounter[g_iOpenZad] = ga_InteractiveKeyboardCounter[g_iOpenZad] || 0;
	if(ga_InteractiveKeyboardCounter[g_iOpenZad] != 0)return false;
	ga_InteractiveKeyboardOn[g_iOpenZad] = ga_InteractiveKeyboardOn[g_iOpenZad] || false;
	if(ga_InteractiveKeyboardOn[g_iOpenZad]){fInteractiveKeyboardClose(el); return true;}
	ga_TextZadachi[g_iOpenZad] = $('#idtextzadachi_'+g_iOpenZad).html();
	var textZadachiHTML = '';var txtZ = ga_TextZadachi[g_iOpenZad]; 
	if(txtZ.indexOf('<img') != -1){
		var index1 = txtZ.indexOf('<img');
		var index2 = txtZ.indexOf('>', index1);
		textZadachiHTML = txtZ.substring(0, index1) + txtZ.substr(index2+1);
	}else{
		textZadachiHTML = txtZ;
	}
var str = fInteractiveKeyboardStrHTML(textZadachiHTML);
	
	el.html('текст задачи &nbsp; &nbsp; &nbsp;  &nbsp; &nbsp; ');
	el.attr('title','вернуться к тексту задачи');
	//11
	ga_InteractiveKeyboardText[g_iOpenZad] = str;
	fInteractiveKeyboardOpenTimer();
	//$('#idtextzadachi_'+g_iOpenZad).html(str);
	//11
/*	$('.interactivekeyboard').mouseover(function(){ $(this).css('cursor', 'pointer'); $(this).css('color', '#f00');
		$(this).css('background-image', 'url(images/main/intKeyboard/interactivekeyboard2.gif)');return false; });
	
	$('.interactivekeyboard').mouseout(function(){ $(this).css('cursor','default');$(this).css('color', '#600');
		$(this).css('background-image', 'url(images/main/intKeyboard/interactivekeyboard3.gif)');return false; });
	
		$('.interactivekeyboard4').mouseover(function(){ $(this).css('cursor', 'pointer'); $(this).css('color', '#f00');return false; });
	$('.interactivekeyboard4').mouseout(function(){ $(this).css('cursor','default');$(this).css('color', '#600');return false; });
	ga_InteractiveKeyboardOn[g_iOpenZad] = true;
	ga_TextZadachiOn[g_iOpenZad] = 0;*/
	
}
//////////////////////////////////////////////////////////////////////////////
function fInteractiveKeyboardOpenTimer(str){
	if(ga_TextZadachiOn[g_iOpenZad] == 0 && ga_InteractiveKeyboardCounter[g_iOpenZad] == 0) return true;
	ga_InteractiveKeyboardCounter[g_iOpenZad] = ga_InteractiveKeyboardCounter[g_iOpenZad] || 0;
	
	  switch(ga_InteractiveKeyboardCounter[g_iOpenZad]){
		 case 0:   str = $('#idtextzadachi_'+g_iOpenZad).css('height'); 
		 			$('#idtextzadachi_'+g_iOpenZad).animate({opacity: 0.0}, 200, function() {
					 ga_InteractiveKeyboardCounter[g_iOpenZad] = 1;
					 fInteractiveKeyboardOpenTimer(str);
					});
				  
	 			 break;
		case 1:	$('#idtextzadachi_'+g_iOpenZad).html(ga_InteractiveKeyboardText[g_iOpenZad]);
		$('#idtextzadachi_'+g_iOpenZad).css('height', str);
				ga_InteractiveKeyboardCounter[g_iOpenZad] = 0;

		 var urlprev = ''; if(typeof(g_bAddZadOn) !== 'undefined'){if(g_bAddZadOn){urlprev = '../';
		 $('.interactivekeyboard, .interactivekeyboard4').css('color', '#600');}}
			  
		$('.interactivekeyboard').mouseover(function(){ $(this).css('cursor', 'pointer'); $(this).css('color', '#f00');
		$(this).css('background-image', 'url('+urlprev+'images/main/intKeyboard/interactivekeyboard2.gif)');return false; });
	
		$('.interactivekeyboard').mouseout(function(){ $(this).css('cursor','default');$(this).css('color', '#600');
		$(this).css('background-image', 'url('+urlprev+'images/main/intKeyboard/interactivekeyboard3.gif)');return false; });
	
		$('.interactivekeyboard4').mouseover(function(){ $(this).css('cursor', 'pointer'); $(this).css('color', '#f00');return false; });
		$('.interactivekeyboard4').mouseout(function(){ $(this).css('cursor','default');$(this).css('color', '#600');return false; });
		ga_InteractiveKeyboardOn[g_iOpenZad] = true;
		ga_TextZadachiOn[g_iOpenZad] = 0;
		
	 	ga_InteractiveKeyboardCounter[g_iOpenZad] = 0;
		$('#idtextzadachi_'+g_iOpenZad).animate({opacity: 1.0},300, function() {
					ga_TextZadachiOn[g_iOpenZad] = 0;
		});
				break;
	}

}
//////////////////////////////////////////////////////////////////////////////
function fInteractiveKeyboardClose(el){
		if(ga_TextZadachiOn[g_iOpenZad] == 1 && ga_InteractiveKeyboardCounter[g_iOpenZad] == 0) return true;
	ga_InteractiveKeyboardCounter[g_iOpenZad] = ga_InteractiveKeyboardCounter[g_iOpenZad] || 0;
	
	  switch(ga_InteractiveKeyboardCounter[g_iOpenZad]){
		  
		 case 0:	$('#idtextzadachi_'+g_iOpenZad).animate({opacity: 0.0}, 200, function() {
					ga_InteractiveKeyboardCounter[g_iOpenZad] = 1;																	  
					  fInteractiveKeyboardClose(el);
					}); break;
		case 1:		ga_InteractiveKeyboardCounter[g_iOpenZad] = 0;	  
					el.html('интерактивная<br>клавиатура &nbsp; &nbsp;  &nbsp; &nbsp; &nbsp; &nbsp; ');
					el.attr('title','удобный способ введения ответа');
					$('#idtextzadachi_'+g_iOpenZad).html(ga_TextZadachi[g_iOpenZad]);
					ga_TextZadachiOn[g_iOpenZad] = 1;
					ga_InteractiveKeyboardOn[g_iOpenZad] = false;
					$('#idtextzadachi_'+g_iOpenZad).animate({opacity: 1.0},300, function() {
					  	ga_TextZadachiOn[g_iOpenZad] = 1;
					});  break;					
	  }
}
////////////////////////////////////////////////////////////////////////////////
function fIntKeyDraw(str, bDegree, bsNum){

	var rexpnum = /\d/;
	bDegree = bDegree || false;
	bsNum = bsNum || 'yes';
	g_iNumAnswer[g_iOpenZad] = g_iNumAnswer[g_iOpenZad] || 1;

	var el = $('#idanswerzad'+g_iNumAnswer[g_iOpenZad]+g_iOpenZad)
	
	var str2 = el.val();
	//////////////////////////////32
	if( (str === ' + ' || str === ' - ' || str === ' = ' || str === '...' || str === ' * ' || str === ' : '  ) && bDegree && bsNum == 'next' && (gTypeZad == 32 || gTypeZad == 2 )){
		if(str === '...'){ str = ' &nbsp; &nbsp; &nbsp; ';}
		if(str === ' - '){str = " &#8211; ";}
		if(str === ' * '){str = " &bull; ";}
		if(giStep == 6){
			fDrawVirazReshDrob32(el, str, true);
		}else{
			fDrawVirazDrob32(el, str, true);
		}
		return true;
	}//11  //////////////////////////////
	if( (str === 'delete') && bDegree && bsNum == 'next' && gTypeZad == 32){
		if(giStep == 6){fDeleteVirazReshDrob32(el, str, true);}
		else{fDeleteVirazDrob32(el, str, true);}
		return true;
	}//11  //////////////////////////////
		
		var last = str2.substr(str2.length - 1, 1);
		var prlast = str2.substr(str2.length - 2, 1);
		var prprlast = str2.substr(str2.length - 3, 1);
		var last3 = str2.substr(str2.length - 3, 3);	
	if(str == 'delete'){// удаление символов

		var i = 1; 
if(last==' ' && prprlast==' ' && (prlast=='+' || prlast=='-' || prlast=='*' || prlast==':')) i = 3;

if(last==' ' && prlast=='(') i = 2;if(prlast==' ' && last==')') i = 2;	
if(rexpnum.test(last) && prlast == '^')i = 2;						  
if(rexpnum.test(last) &&rexpnum.test(prlast) && prprlast == '^')i = 3;					  
						
						str2 = str2.substr(0, str2.length - i);
						el.val(str2);
		
	}else{//ввод символов
	if(bDegree){//степени
		if((rexpnum.test(last) && prlast == '^') || (rexpnum.test(last) &&rexpnum.test(prlast) && prprlast == '^')){
			 el.val(el.val() + str); 	
		}else{
			
			el.val(el.val() + '^' + str);
		}
	}else{//не степени
		if((rexpnum.test(last) && prlast == '^') || (rexpnum.test(last) &&rexpnum.test(prlast) && prprlast == '^')){
			if(bsNum == 'yes'){ el.val(el.val() + ' * ' + str); 
			}else{ el.val(el.val() + str); }
		}else
	el.val(el.val() + str); 	
	}
	
	
	
	}
fIntDegreeDraw(el.val());
el.focus();
}
//////////////////////////////////////////
function fIntDegreeDraw(str){//по полю text (a^2) выдает (a<sup>2</sup>)
	var str2 = '';
	g_iOpenZad = g_iOpenZad || 0;
	g_iNumAnswer[g_iOpenZad] = g_iNumAnswer[g_iOpenZad] || 1;
	var rexpnum = /\d/;
var	elstr  = '#idtextzadachiVirazen'+g_iNumAnswer[g_iOpenZad]+g_iOpenZad;
var el = $('#idtextzadachiVirazen'+g_iNumAnswer[g_iOpenZad]+g_iOpenZad);

var ai = new Array();var al = new Array(); var j = 0;var i = 0;

ai[0] = -1;
		for(i = 0; str.indexOf('^',j+1) != -1; i++ ){
			ai[i] = str.indexOf('^',j+1);
			
			if( rexpnum.test(str.charAt(ai[i]+1)) ) al[i] = 1;
						  if( rexpnum.test(str.charAt(ai[i]+2)) ){ al[i] = 2;
							  if( rexpnum.test(str.charAt(ai[i]+3)) ) al[i] = 3;
						  }
			 
			j = ai[i];
			
		}
			if(ai[0] != -1){
				j=0;i = 0
					while(i < ai.length){
						str2 += str.substr(j,ai[i]-j);
						str2 += '<sup>'+str.substr(ai[i]+1,al[i])+'</sup>';
						j = ai[i] + al[i]+1;
						i++;
					}
				
					var bstr =str.substr(j,str.length - j);
					var b =/\^/g.test(bstr);
					if(!b)
					str2 += bstr;
			}else{
				str2 = str;
			}
			
			str2 = str2.replace(new RegExp("-",'ig'),"&#8211;");
			str2 = str2.replace(/\*/i,"&bull;");
var sZadachiVirazen = '';		
	if(typeof(g_bAddZadOn) !== 'undefined'){
		if(g_bAddZadOn && g_bAddZadOff){
					if((giStep == 3 || giStep == 6) && gTypeZad == 31){
							sZadachiVirazen = "<br><br><div class='textzadachiVirazen' id='idtextzadachiVirazen10'>";
							sZadachiVirazen += str2;
							sZadachiVirazen += "</div><br>";
							el.html(str2);
					}
					if((giStep == 3 || giStep == 6) && gTypeZad == 32){
							sZadachiVirazen = "<br><br><div class='textzadachiVirazen' id='idtextzadachiVirazen10'>";
							sZadachiVirazen += str2;
							sZadachiVirazen += "</div><br>";
							if(giStep == 6){gReshZadachiVirazen = sZadachiVirazen;}
							else{gTextZadachiVirazen = sZadachiVirazen;}
							
								if(giStep == 6){fDrawVirazReshDrob32(el, str2);}
								else{fDrawVirazDrob32(el, str2);}
					}
			}else{el.html(str2);}
		}else{el.html(str2);}
}
/////////////////////////////////////////////////////////////////////////////////
function fIntDegreeDrawRetStr(str, elstr){//по полю text (a^2) выдает (a<sup>2</sup>)
	var str2 = '';
	g_iOpenZad = g_iOpenZad || 0;
	g_iNumAnswer[g_iOpenZad] = g_iNumAnswer[g_iOpenZad] || 1;
	var rexpnum = /\d/;
var	elstr  = elstr || '#idtextzadachiVirazen'+g_iNumAnswer[g_iOpenZad]+g_iOpenZad;
var el = $(elstr);
var ai = new Array();var al = new Array(); var j = 0;var i = 0;

ai[0] = -1;
		for(i = 0; str.indexOf('^',j+1) != -1; i++ ){
			ai[i] = str.indexOf('^',j+1);
			
			if( rexpnum.test(str.charAt(ai[i]+1)) ) al[i] = 1;
						  if( rexpnum.test(str.charAt(ai[i]+2)) ){ al[i] = 2;
							  if( rexpnum.test(str.charAt(ai[i]+3)) ) al[i] = 3;
						  }
			 
			j = ai[i];
			
		}
			if(ai[0] != -1){
				j=0;i = 0
					while(i < ai.length){
						str2 += str.substr(j,ai[i]-j);
						str2 += '<sup>'+str.substr(ai[i]+1,al[i])+'</sup>';
						j = ai[i] + al[i]+1;
						i++;
					}
				
					var bstr =str.substr(j,str.length - j);
					var b =/\^/g.test(bstr);
					if(!b)
					str2 += bstr;
			}else{
				str2 = str;
			}
			
			str2 = str2.replace(new RegExp("-",'g'),"&#8211;");
			str2 = str2.replace(/\*/g,"&bull;");
		el.html(str2);
}

/////////////////////////////////////////////////////////////////////////////////

function fMyAlert(str){
	var g_t_z = ''; var f_size = $('#idtextzadachi_'+g_iOpenZad).css('font-size');;
	var strBR = str.replace(new RegExp("\n",'g'),"<br>")
	 strBR = strBR.replace(new RegExp("&mdash;",'g')," &nbsp;  &nbsp; -  &nbsp;  &nbsp; ")
		  g_t_z = $('#idtextzadachi_'+g_iOpenZad).html();
	  $('#idtextzadachi_'+g_iOpenZad).html(strBR);
	  $('#idtextzadachi_'+g_iOpenZad).css('font-size','22px');
	  alert(str);
	  $('#idtextzadachi_'+g_iOpenZad).html(g_t_z);
	  $('#idtextzadachi_'+g_iOpenZad).css('font-size',f_size);
}
/////////////////////////////////////////////////////////////////////////////////
function removeSpaces(s) {
		  var allSpacesRe = /\s+/g;		  
		  s = s.replace(allSpacesRe, "");
		  return  s.replace(",", ".");
	  }// удаление пробелов замена запятой точкой
	  ////////////////////////////////////////////



var gstr;

var g_inDegree = 0;


function fChekRightLeftBrackets(str, chisl){
	var iChislOrZnametatel = 'Не';
	if(chisl == 1)iChislOrZnametatel = 'В числителе не';
	if(chisl == 2)iChislOrZnametatel = 'В знаменателе не';
	
	var g = 0; var j = 0; var  j1 = 0; var  j2 = 0;//проверим соответствие кол-ва скобок левых и правых
	while ( (g = str.indexOf('(',j)) != -1){j1++; j = g + 1;}
	g = 0; j = 0;						   
	while ( (g = str.indexOf(')',j)) != -1){j2++; j = g + 1;}
			if(j1-1 == j2)
			return iChislOrZnametatel+' хватает правой скобки';	
			if(j1 > j2)
			return iChislOrZnametatel+' хватает правых скобок';				   
			if(j2-1 == j1) 
			return iChislOrZnametatel+' хватает левой скобки';	
			if(j2 > j1)
			return iChislOrZnametatel+' хватает левых скобок';
			g = 0; j = 0; j1 = 0; j2 = 0;
			return '';
}
//////////////////////////////////////////////////////////////////////////////////////////////

function fPrivedMchlenStandart(str, chisl, first){// приведение многочлена к стандартному виду
//var regexpADigitNo=new RegExp('[^\\d.,\(\)]','g'); if(!regexpADigitNo.test(str)){return str.replace(/,/gi, ".").replace(/[\(\)\s]/gi,"")}
//11bb
var regexpA=new RegExp('[.,]','g'); if(regexpA.test(str)){return str.replace(/,/gi, ".").replace(/[\(\)\s]/gi,"")}

first = first || 0;
chisl = chisl || 0;//числитель-1   знаменатель-2

	  
	str = removeSpaces(removeRus(str));
		  			//создадим многомерный массив с информацией о скобках
					//arBrackets[i][0]-индекс в строке левой скобки;
					//arBrackets[i][1]-индекс в строке этойже правой скобки
					//arBrackets[i][2]-индекс в arBrackets родительских скобок, либо 'no'
					//arBrackets[i][3]-уровень вложенности
					if ( (str.indexOf('(',j)) == -1)
										return str;

										
					var arBrackets = fMakeMassivOfBrackets(str);		  
var iMaxInsertLevel = 0; for(var i = 0 ; i < arBrackets.length; i++){if(iMaxInsertLevel < arBrackets[i][3])iMaxInsertLevel = arBrackets[i][3];}
	var j = 0; var aBracketPart = new Array(); var aBracketPartParent;
	for(var i = 0 ; i < arBrackets.length; i++){
		
		 if( j > 0 && iMaxInsertLevel == arBrackets[i][3] && arBrackets[i][2] == aBracketPart[0][2]){
			 aBracketPart[j] = arBrackets[i];
			if(arBrackets[i][3] > 0) aBracketPartParent = arBrackets[arBrackets[i][2]];
			 j++;
		 }//if
			 if(iMaxInsertLevel == arBrackets[i][3] && j == 0){
				 aBracketPart[j] = arBrackets[i];
				 if(arBrackets[i][3] > 0) aBracketPartParent = arBrackets[arBrackets[i][2]];
				 j++;
			 }//if
	 }//for
			  if(iMaxInsertLevel == 0){
			  	indexStrPart_0 =  0; 	indexStrPart_end =  str.length-1;
			  }else{
			  	indexStrPart_0 =  aBracketPartParent[0]+1; 	indexStrPart_end =  aBracketPartParent[1]-1;
			  }
	 StrPart= fPrivedMchlenStandartPartM(str.substring(indexStrPart_0, indexStrPart_end+1))//схема ()()
str = str.substring(0, indexStrPart_0) + StrPart + str.substr(indexStrPart_end+1);

str = fPrivedMchlenStandart(str, chisl, 1);

return str;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function fPrivedMchlenStandartPartM(str){// схема ()()
if ( (str.indexOf('(')) == -1) return str;
var arStr2 = new Array();
var str1 = ''; var str2 = '';var nextIndex = 9999999; 
		  str = fHaveBracketDegree(str);

	  //()()() begin
	  str = removeSpaces(str);
	  var strForDivide1 = str.replace(/\)\+\(/g,')::(');
	var	strForDivide2 = strForDivide1.replace(/\)-/g,')::-');
	var  strForDivide3 = strForDivide2.replace(/\)\+/g,')::+');
	var  strForDivide4 = strForDivide3.replace(/\+\(/g,'::(');
var arStr = strForDivide4.split('::');
		for(var i = 0 ; i < arStr.length; i++){
			if(arStr[i].indexOf('(') != -1){
				var arBrackets = fMakeMassivOfBrackets(arStr[i]);
				arStr2[i] = MultipleMchlen(arStr[i].substring(arBrackets[0][0]+1,arBrackets[0][1]), '1');
				
				for(var j = 1 ; j < arBrackets.length; j++){
					var strToMultiple = MultipleMchlen(arStr[i].substring(arBrackets[j][0]+1,arBrackets[j][1]), '1');
					arStr2[i] = MultipleMchlen(arStr2[i], strToMultiple);
				}
			}else{
				arStr2[i] = arStr[i];
			}//if else
		}//for
		
		  for(var i = 0 ; i < arStr2.length; i++){
			  if(arStr2[i].substr(0,1) != '-' && i != 0){
					str1 += '+' + arStr2[i];   
			  }else{
				  str1 +=  arStr2[i];
			  }
 			 
		  }	
		var str11 = MultipleMchlen(str1, '1');
return str11;
}
/////////////////////////////////////////////////////////////////////
function fHaveBracketDegree(str){// схема n*()^n
var str2 = str; var arBrackets;
var arBrackets1 = fMakeMassivOfBrackets(str);
var str3 = '';var str4 = '';
 var str1 = str3 = str.substring(arBrackets1[0][0]+1, arBrackets1[0][1]);

	for(var i = 0 ; i < arBrackets1.length; i++){
			   arBrackets = fMakeMassivOfBrackets(str2);
		str1 = str3 = MultipleMchlen(str.substring(arBrackets1[i][0]+1, arBrackets1[i][1]), '1');	  
		  if(str2.substr(arBrackets[i][1]+1, 1) == '^'){
			  for(var ii = 0 ; new RegExp('\\d','g').test(str2.substr(arBrackets[i][1]+2+ii, 1)); )ii++;
			   g_inDegree = ii;
			  iDegree = parseInt(str2.substr(arBrackets[i][1]+2, ii));

					  for(var j = 1 ; j < iDegree ; j++)
					
					 str3 = MultipleMchlen(str3, str1);
			str2 = str2.substring(0, arBrackets[i][0]) +'(' + str3 + ')' + str2.substr(arBrackets[i][1]+ii+2);  
		  }
	}//for ////^n end
		  
		
	var inPlus = new Array();arBrackets = fMakeMassivOfBrackets(str2); var strNext = '';	   
	for(var i = 0 ; i < arBrackets1.length; i++){	 //n()begin	  

					  if(i != arBrackets.length-1) strNext = str2.substring(arBrackets[i][1]+1, arBrackets[i+1][0]);
					  else  strNext = str2.substr(arBrackets[i][1]+1);
					  
					  var strNextPlus = strNext.replace(/\+/g,'-');
					  if( ( inPlus[i] = strNextPlus.indexOf('-') ) != -1){
					  		strNext = strNext.substring(0,inPlus[i]);
					  }else {
						  inPlus[i] = 0; 
						 if( i < arBrackets.length-1) strNext = ''; 
					  }
							
					strNext = strNext.replace(/\*/g,'');
				
				var index_0 = 0; if(i != 0 )index_0 = arBrackets[i-1][1]+1;
				
				var strPrev = str2.substring(index_0, arBrackets[i][0]);
				if(strPrev.indexOf('*', strPrev.length-1) != -1 ) strPrev = strPrev.substring(0,strPrev.length-1);//удаляем перед скобкой
				var strPrevPlus = strPrev.replace(/\+/g, "-");
			  var prevSlagaem = ''; var prevMnozit = '';
				var fist_index_Plus = strPrevPlus.indexOf('-');
				  var last_index_Plus = strPrevPlus.lastIndexOf('-');
						if(last_index_Plus != -1 && last_index_Plus != fist_index_Plus){
							prevSlagaem = strPrev.substring(fist_index_Plus, last_index_Plus+1);
							prevMnozit = strPrev.substring(last_index_Plus, arBrackets[i][0]);
						}
						if(last_index_Plus == -1)prevMnozit = strPrev;
						
						if(last_index_Plus != -1 && last_index_Plus == fist_index_Plus){//один плюс и он есть (или минус)
							if(i == 0){
							prevSlagaem = strPrev.substring(0, last_index_Plus+1);
							prevMnozit = strPrev.substring(last_index_Plus, arBrackets[i][0]);
							}else {
								if(strPrev.length == 1){
									prevSlagaem = strPrev;
									prevMnozit = '1';
								}else{
									prevSlagaem = '+';
									prevMnozit = strPrev.substring(last_index_Plus, arBrackets[i][0]);
								}
							}
								
						}// if     один плюс и он есть (или минус)
				if(prevMnozit == '-')prevMnozit= '-1';	
				if(prevMnozit == '')prevMnozit = '1';
				
			if(prevSlagaem.substr(prevSlagaem.length-1) == '-')
			prevSlagaem = prevSlagaem.substring(0,prevSlagaem.length-1) + '+';
			// if(prevSlagaem == '')prevSlagaem = '';
					var strpart = str2.substring(arBrackets[i][0]+1, arBrackets[i][1]);
				var strend = '';
					if(i ==arBrackets1.length-1){
						strend = str2.substr(arBrackets[i][1]+1);
						if( !new RegExp('[\+,-]','g').test(strend))strend = '';
						else{
							strendPlus = strend.replace(/\+/g,'-');
							 inPlus[i] = strendPlus.indexOf('-');
							 strend = strend.substr(inPlus[i]);
							}
					}
					var strNewPart = MultipleMchlen(prevMnozit, strpart);
					if(strNext != '')strNewPart = MultipleMchlen(strNewPart, strNext);
						str4 +=prevSlagaem +'(' + strNewPart + ')' + strend;
					
					 //11
				 var sssl2 = '   после степеней &mdash; ' +   str2  +'\n\n';
				 sssl2 += '  i  &mdash;   '+   i +'\n';
				 sssl2 += '  strNext  &mdash;   '+   strNext +'\n';
				 sssl2 += '  prevMnozit  &mdash;   '+   prevMnozit +'\n';
				 sssl2 += '  strpart  &mdash;   '+   strpart +'\n';
				 
				 sssl2 += '  inPlus[i]  &mdash;   '+   inPlus[i] +'\n';
				 sssl2 += '  prevSlagaem  &mdash;   '+   prevSlagaem +'\n';
				 sssl2 += '  strNewPart  &mdash;   '+   strNewPart +'\n';
				 sssl2 += '  strend  &mdash;   '+   strend +'\n';
				  sssl2 += '  промеж резултат  &mdash;   '+   str4  +'\n';
				 sssl2 +=    '\n\n .....';
				 //fMyAlert(sssl2);
				 //11
			  
	}//for
	
					 //11
				 var sssl2 = '   после степеней &mdash; ' +   str2  +'\n\n';
				  sssl2 += '  конечный резултат  &mdash;   '+   str4  +'\n\n';
				 sssl2 +=    '\n\n .....';
				 //fMyAlert(sssl2);
				 //11
return str4;
}
/////////////////////////////////////////////////////////////////////
function fMakeMassivOfBrackets(str){
		  strOnlyRBracket=str.replace(/\(/g, ")");
		
var j = 0; var i = 0;  var g = 0; var aiLBracket = new Array(); var aiRBracket = new Array();
					while ( (g = str.indexOf('(',j)) != -1){aiLBracket[i] = g;  j = g + 1; i++; if(i > 10) break;}																				
if(aiLBracket.length > 9){str='Слишком много скобок в ';if(chisl==1)str+='числителе'; if(chisl==2)str+='знаменателе'; return str;}			  
j = 0; i = 0; g = 0; while ( (g = str.indexOf(')',j)) != -1){aiRBracket[i] = g;  j = g + 1; i++; if(i > 10) break;}
					//создадим многомерный массив arBrackets[i][0]-индекс в строке левой скобки;
					//arBrackets[i][1]-индекс в строке этойже правой скобки
					//arBrackets[i][2]-индекс в arBrackets родительских скобок, либо 'no'
					//arBrackets[i][3]-уровень вложенности
					var arBrackets = new Array();for(i=0;i<aiLBracket.length;i++){arBrackets[i] = new Array();}
j = 0; i = 0; g = 0; var gg = 0;var ggg = 0;var jj = 0;var jjj = 0;var iMaxRBrackket = 0;
					while(i<aiLBracket.length){
						arBrackets[i][0]=aiLBracket[i];j++;
						g = aiLBracket[i];
							  if(i>0){
								  var kk = 1 ;
								  if(arBrackets[i][0] < iMaxRBrackket){
									  
									  for(var k = 1 ; k < jjj+1; k++){
											if(arBrackets[i][0] > arBrackets[i-k][1]){
											jj = jjj ;jjj  = jjj-k+1;kk++;
											}
									  }
								  }
								  if(jj > 0){
									  arBrackets[i][2] = i-kk;
									  arBrackets[i][3]= jj;
								  }else{
									  arBrackets[i][2] = 'no'; arBrackets[i][3] = 0;
								  }
							  }
						for(var ii = i+1; ii < aiLBracket.length*2; ii++){
							  ggg = strOnlyRBracket.indexOf(')',g+1);
							  gg = str.indexOf('(',g+1);
												 
								  if(gg == ggg){
									  j++; 
									  if(ii == i+1)
									  jj++; //опять левая
								  }else{ 
									  j--;
									  if(ii == i+1){
									  jjj=jj; jj = 0; //нашел правую
									  }
								  }
								  
							  if(j==0){
								arBrackets[i][1]= str.indexOf(')',g+1)
							  
							  if(arBrackets[i][1] > iMaxRBrackket){
								  iMaxRBrackket = arBrackets[i][1];
								  jjj=0;
								  } break; 
							  }
							  g=ggg;
						}//for
						if(i==0){
							arBrackets[i][2] = 'no'; arBrackets[i][3] = 0;
							}
						i++;
					}//while
					return arBrackets;
}

////////////////////////////////////////////////////////

function MultipleMchlen(str1, str2){
	
str1 = removeSpaces(str1);str1 = removeRus(str1);
str2 = removeSpaces(str2);str2 = removeRus(str2);
if(str1.charAt(0) != '-' && str1.charAt(0) != '+') str1 = '+' + str1;
if(str2.charAt(0) != '-' && str2.charAt(0) != '+') str2 = '+' + str2;

 var strDiv1 = str1.replace(/\+/g, "::+");  strDiv1 = strDiv1.replace(/\-/g, "::-"); 
 var strDiv2 = str2.replace(/\+/g, "::+"); strDiv2 = strDiv2.replace(/\-/g, "::-"); 
 var sArray1 = new Array(); var sArray2 = new Array();
 sArray1 = strDiv1.substr(2).split('::');
 sArray2 = strDiv2.substr(2).split('::');
 var aResult = new Array();var g = 0;
 for(var i = 0; i < sArray1.length; i++){
		for(var j = 0; j < sArray2.length; j++){
			aResult[g] = new Array(); 
			aResult[g] = Multiple1chlen(sArray1[i], sArray2[j], true);
			g++;
		}
 }
 if(str1 != '+1' && str2 != '+1')//11
 var aa11 = 0;
	aResult= aResult.sort();
	var aResult2 = new Array();var g = 0; var countSymbols = 0;
 for(var i = 0; i < aResult.length; i++){//складываем подобные слагаемые
	 aResult2[g] =  new Array();
		aResult2[g][0] = aResult[i][2]; 
		aResult2[g][1] = aResult[i][1];
		aResult2[g][2] = aResult[i][0];
		
		for(var j = i+1; j < aResult.length; j++){

			if(aResult[i][0] == aResult[j][0]){
				aResult2[g] = Sum1chlens(aResult2[g], aResult[j]);
				countSymbols++;
			}
			if(aResult[i][0] != aResult[j][0] || j+1 == aResult.length){
				i += countSymbols;
				countSymbols = 0; 
				break;
			}
		}///for

		g++;
 }/////for
 var sResult = '';var bFistSign = true;	
	 for(var i = 0; i < aResult2.length; i++){//складываем подобные слагаемые
	 if(bFistSign && aResult2[i][0] == '-'){bFistSign = false;

	 }
	 if(bFistSign && aResult2[i][0] == '+'){
		 bFistSign = false;
		 if(parseInt(aResult2[i][1]) == 1){
		 sResult += aResult2[i][2];
		 if(sResult == '' && aResult2[i][0]=='+')
		 sResult='1';

		 }else
		sResult += aResult2[i][1]+aResult2[i][2];
	 }
	 else{
		 if(parseInt(aResult2[i][1]) == 1){
			 	if(aResult2[i][0]== '-' && aResult2[i][2] == '')
				sResult += aResult2[i][0]+aResult2[i][1];
		 		else sResult += aResult2[i][0]+aResult2[i][2];
		 }else 
		 	sResult += aResult2[i][0]+aResult2[i][1]+aResult2[i][2];
	 }
 	}/////for
	aResult2 = [];aResult = [];
	if(sResult.length > 2 )sResult = sResult.replace(/\+0/g, '');
	if(sResult.length > 1 && parseInt(sResult.substring(0, 1), 10) === 0)sResult = sResult.substr(1);
return sResult;	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Sum1chlens(ar1, ar22){
	var ar2 = new Array(); ar2[0] = ar22[2];  ar2[1] = ar22[1];   ar2[2] = ar22[0];var aResSum = new Array(); 
	
	var isNull_1 = (ar1[0] == '' && parseInt(ar1[1]) == 0 && ar1[2] == ''); 
	var isNull_2 = (ar2[0] == '' && parseInt(ar2[1]) == 0 && ar2[2] == '');
	if(isNull_1 || isNull_2) {aResSum[0] = '';aResSum[1] = '0';aResSum[2] = '';
	return aResSum;}
	
		if(ar1[1] > ar2[1] && ar1[0] != ar2[0]){
			aResSum[0] = ar1[0]; aResSum[1] = ar1[1] - ar2[1] }
		if(ar1[1] < ar2[1] && ar1[0] != ar2[0]){
			aResSum[0] = ar2[0]; aResSum[1] = ar2[1] - ar1[1] }
		
	//	if(ar1[1] != ar2[1] && ar1[0] == ar2[0]){aResSum[0] = ar2[0]; aResSum[1] = ar2[1] + ar1[1] }
		
	//	if(ar1[1] == ar2[1] ){
					if(ar1[0] == ar2[0]){
						aResSum[0] = ar1[0];
						aResSum[1] = ar2[1] + ar1[1];
					}else{
						if(ar1[1] == ar2[1]){
							aResSum[0] = '+';
							aResSum[1] = '0';
						}//+ и - числа равны
					}
	//	}
		
	if(ar1[2] == ar2[2]){
	aResSum[2] = ar2[2];
		if(aResSum[1] == '0'){
			aResSum[2] = '';
			aResSum[0] = '+';
		}
			ar2 = [];
		return aResSum;
	}

	
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Multiple1chlen(str, str2, bArrayReturn){

	bArrayReturn = bArrayReturn || false;
	str = removeSpaces(str);
str = removeRus(str);
str2 = removeSpaces(str2);
str2 = removeRus(str2);
if(str == '' && str2 == '') return '';
	 var degree = 1;
	
	var strBegin = ''; 
	var bM1 = str.substr(0, 1) == '-';var bM2 = str2.substr(0, 1) == '-';
	var bP1 = str.substr(0, 1) == '+';var bP2 = str2.substr(0, 1) == '+';
	if(bM1 || bP1)str = str.substr(1); if(bM2 || bP2)str2 = str2.substr(1);
	if((bM1 && !bM2) || (!bM1 && bM2) )strBegin = '-'; else strBegin = '+'
	str += '*'+str2;
		  	var j = 0; var i = 0; var aResult = new Array(); 
				for(i = 0; j < str.length; i++){
					if(str.substr(j, 1) == '*')j++;
					aResult[i] = new Array();
					var countSymbols = 1;
	if(j+1<str.length && new RegExp('\\d','g').test(str.substr(j, 1)) && new RegExp('\\d','g').test(str.substr(j+1, 1))){countSymbols = 2;
					if(j+2<str.length && new RegExp('\\d','g').test(str.substr(j+2, 1))){countSymbols = 3;
					if(j+3<str.length && new RegExp('\\d','g').test(str.substr(j+3, 1))){countSymbols = 4;
					if(j+4<str.length && new RegExp('\\d','g').test(str.substr(j+4, 1))){countSymbols = 5;
					if(j+5<str.length && new RegExp('\\d','g').test(str.substr(j+5, 1))){countSymbols = 6;
					if(j+6<str.length && new RegExp('\\d','g').test(str.substr(j+6, 1))){countSymbols = 7;
					}}}}}}
					aResult[i][0] = str.substr(j, countSymbols);//aResult[i][0]-основание   aResult[i][1]-степень
					j += countSymbols - 1;
					  if(str.substr(j+1, 1) == '^'){ 
						   //посчитаем кол-во символов в степени и переведем на это число счетчик i;
					 for(var jj = 0; jj < 4 != 0;jj++){if(!(new RegExp('\\d','g').test(str.substr(j+2+jj,1)))) break;}

						  aResult[i][1] = str.substr(j+2, jj);
						  j+= jj+1;
					  }else 
					  if(str.substr(j, 1) != '*')
					  aResult[i][1] = 1;
				  j++;
				}
	aResult= aResult.sort();
	var strNumber = 1;var strLitter = '';
	for(i = 0; i < aResult.length; i++){
		if( (new RegExp('\\d','g').test(aResult[i][0])) ){
			for(j = 0; j < aResult[i][1]; j++)
			strNumber *=aResult[i][0]; 
			
		}else{
			degree= parseInt(aResult[i][1]);
			for(j = i+1; j < aResult.length+1; j++){
				if(j < aResult.length && aResult[j][0] == aResult[i][0]){
					degree += parseInt(aResult[j][1]);}
				if(j+1 > aResult.length || (aResult[j][0] != aResult[i][0])) {
					strLitter+=aResult[i][0]; if(degree > 1)strLitter+='^'+degree; i=j-1;break;}
			}//for
		}//else
	}//for
	
//if(String(strNumber) == '1')strNumber = '';


if(parseInt(strNumber, 10) == 0)strLitter = '';
		if(bArrayReturn){
			var ar = new Array();
			  ar[2] = strBegin; ar[1] = strNumber; ar[0] = strLitter; 
			  return ar;
		}else{
				return strBegin + strNumber + strLitter;
		}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function fCheckMultiples(iNumberZad){
	var abRes = new Array(); var bRes = false;
	var g = 1;
var aswerClient = ''; var aswerClientPlus = g_aswerClient[1].replace(/\+/g, "-");;
if(aswerClientPlus.substring(0, 1).indexOf('-') != - 1){aswerClient = g_aswerClient[1].substr(1);aswerClientPlus = aswerClientPlus.substr(1);}
else {aswerClient = g_aswerClient[1];}

var arBrackets = fMakeMassivOfBrackets(aswerClient);
var j = 0; var arBracket0 = new Array();
	for(i = 0; i < arBrackets.length; i++){
		if(arBrackets[i][3] === 0){arBracket0[j] = new Array( arBrackets[i][0],arBrackets[i][1]); j++;}
	}
	
	if(j === 0 && aswerClientPlus.indexOf('-') == - 1){
		return true;}
	if(j === 0 && aswerClientPlus.indexOf('-') != - 1){
				  $('#idanswerResult' + iNumberZad).css('width', '300px');
							  g_answerResult = 'Не разложили на множители';
							  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
							  return false;	
	}
	//////////////////////////////////////////////////////////////////////////////////
	if(j === 1 && aswerClientPlus.substr(1).indexOf('-') != - 1){
		
		  
			 while((g = aswerClientPlus.indexOf('-', g+1)) != -1){
				 if(g > arBracket0[0][1] || g < arBracket0[0][0] ){
						$('#idanswerResult' + iNumberZad).css('width', '300px');
						g_answerResult = 'Не разложили на множители';
						g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
						return false;
					 }
			 }
		  var bNumber = /\d/g.test(aswerClientPlus.substring(arBracket0[0][1]+2, 1));
		 if(aswerClientPlus.indexOf('^', arBracket0[0][1]+1) != -1 && bNumber ||arBracket0[0][0] > 0  || arBracket0[0][1] < aswerClientPlus.length - 1 ){//11 надо доработать
				return true; 
		 }else{		
		 				$('#idanswerResult' + iNumberZad).css('width', '300px');
						g_answerResult = 'Не разложили на множители';
						g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
						return false;
		}
	}//if(j === 1 && aswerClientPlus.substr(1).indexOf('-') == - 1){///////////////////
	
	if(j > 1 && aswerClientPlus.indexOf('-') != - 1){
		 g = 1;
		  
		while((g = aswerClientPlus.indexOf('-', g+1)) != -1){
		  
			for(i = 0; i < arBracket0.length; i++){	
				 if(g > arBracket0[i][1] || g < arBracket0[i][0] ){abRes[i] = false;}
				 else {abRes[i] = true;}
			 }//for
				 for(i = 0; i < abRes.length; i++){	
					 if(abRes[i]){bRes = true;}
				 }//for
					   if(!bRes){
								  $('#idanswerResult' + iNumberZad).css('width', '300px');
							  g_answerResult = 'Не разложили на множители';
							  g_timer_chekanswer = window.setTimeout("f_g_timer_chekanswer();", ga_time_pause_zad[g_iOpenZad]);
							  return false;					 
					   }
		  	abRes = [];bRes = false;
		  }//while
		return true;
	}//if(j === 1 && aswerClientPlus.substr(1).indexOf('-') == - 1){///////////////////
	
	

return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function f_MakeDigitMnojit(str){
	
	
return str2;	
}

/*
 * One Click Upload - jQuery Plugin
 * Copyright (c) 2008 Michael Mitchell - http://www.michaelmitchell.co.nz
 */
eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('(1($){$.13.14=1(a){a=$.B({3:\'H\',5:\'15/C-16\',6:\'\',v:I,o:1(){},p:1(){},q:1(){},7:{}},a);r D $.E(z,a)},$.E=1(f,g){2 h=z;2 i=D 17().18().19().1a(8);2 j=$(\'<w \'+\'1b="w\'+i+\'" \'+\'3="w\'+i+\'"\'+\'></w>\').s({J:\'1c\'});2 k=$(\'<C \'+\'1d="1e" \'+\'5="\'+g.5+\'" \'+\'6="\'+g.6+\'" \'+\'1f="w\'+i+\'"\'+\'></C>\').s({K:0,L:0});2 l=$(\'<M \'+\'3="\'+g.3+\'" \'+\'N="H" \'+\'/>\').s({O:\'P\',J:\'1g\',1h:-1i+\'t\',1j:0});f.1k(\'<Q></Q>\');k.R(l);f.S(k);f.S(j);2 m=f.1l().s({O:\'P\',T:f.1m()+\'t\',1n:f.1o()+\'t\',1p:\'U\',1q:\'1r\',K:0,L:0});l.s(\'1s\',-m.T()-10+\'t\');m.1t(1(e){l.s({V:e.1u-m.W().V+\'t\',X:e.1v-m.W().X+\'t\'})});l.1w(1(){h.q();u(h.v){h.F()}});$.B(z,{v:I,o:g.o,p:g.p,q:g.q,1x:1(){r l.9(\'G\')},7:1(a){2 a=a?a:x;u(a){g.7=$.B(g.7,a)}y{r g.7}},3:1(a){2 a=a?a:x;u(a){l.9(\'3\',G)}y{r l.9(\'3\')}},6:1(a){2 a=a?a:x;u(a){k.9(\'6\',a)}y{r k.9(\'6\')}},5:1(a){2 a=a?a:x;u(a){k.9(\'5\',a)}y{r k.9(\'5\')}},Y:1(c,d){2 d=d?d:x;1 A(a,b){1y(a){1z:1A D 1B(\'[Z.E.Y] \\\'\'+a+\'\\\' 1C 1D 1E A.\');4;n\'3\':h.3(b);4;n\'6\':h.6(b);4;n\'5\':h.5(b);4;n\'7\':h.7(b);4;n\'v\':h.v=b;4;n\'o\':h.o=b;4;n\'p\':h.p=b;4;n\'q\':h.q=b;4}}u(d){A(c,d)}y{$.11(c,1(a,b){A(a,b)})}},F:1(){z.o();$.11(g.7,1(a,b){k.R($(\'<M \'+\'N="U" \'+\'3="\'+a+\'" \'+\'G="\'+b+\'" \'+\'/>\'))});k.F();j.1F().1G(1(){2 a=12.1H(j.9(\'3\'));2 b=$(a.1I.12.1J).1K();h.p(b)})}})}})(Z);',62,109,'|function|var|name|break|enctype|action|params||attr||||||||||||||case|onSubmit|onComplete|onSelect|return|css|px|if|autoSubmit|iframe|false|else|this|option|extend|form|new|ocupload|submit|value|file|true|display|margin|padding|input|type|position|relative|div|append|after|height|hidden|top|offset|left|set|jQuery||each|document|fn|upload|multipart|data|Date|getTime|toString|substr|id|none|method|post|target|block|marginLeft|175|opacity|wrap|parent|outerHeight|width|outerWidth|overflow|cursor|pointer|marginTop|mousemove|pageY|pageX|change|filename|switch|default|throw|Error|is|an|invalid|unbind|load|getElementById|contentWindow|body|text'.split('|'),0,{}))
// JavaScript Document
//Dialog
var date1 = new Date();
 var time_loading_begin = date1.getTime();
var g_user_status = 0;
var g_data_send_for_next_zadachi;
////////////////////////////////////////////////////////////
		function f_open_dilog_resh(){
				if(gbReshShowing) {$('#dialog_reshenie_zadachi').dialog('close'); return false;}
				gbReshShowing = true;
			f_send_look_zad('http://school-assistant.ru/_mainp/sav/saveLookResh.php', g_ch);	
		}
	////////////////////////////////////////////////////////////	
	function f_timer_send_for_next_zadachi(){
		
		$('#dialog_resh_zad').html(g_data_send_for_next_zadachi);
		
	var ga_id_zad_obj = new Array();		
	ga_id_zad_obj = $('input[name*="name_id_zad"]').serializeArray();
		
			for(i = 0, j = ga_id_zad.length; i < ga_id_zad_obj.length; i++,j++)
		ga_id_zad[j] =	ga_id_zad_obj[i].value;
		$('#accordion').unbind();
		$('#tabs').unbind();
		$("#accordion").accordion({ header: "h3" });

		$("#tabs").tabs({
		  event: "click",
		  selected: 0
		});
		
 g_timer_chekanswer = 0;
 g_answerResult='';
 g_iSendZad='';



ga_time_pause_zad = new Array();
gi_Answer_send = 11111;
gi_timeout_zad = 2000;		
		
			timerZad = 0;
			 time_Zad = new Array();
			 resheno = new Array();
			g_iOpenZad =  0;
			g_bLook = 1;
			f_timer_start();
			fAllClassesInclude();
			
	$('#dialog_resh_zad').dialog('open');	
	}
	//////////////////////////////////////////////////////////////
	function f_send_for_next_zadachi(){
		data = new Object();
		for (i = 0; i < ga_id_zad.length; i++)
		data['zad[' + i + ']'] = ga_id_zad[i];
					
		data['pageID'] = g_id_page;
		
					  
				 var op = {
				  url:	 '_mainp/NextZadachi.php',
				  type: "POST",
				  //timeout: gi_timeout_zad,
				  data: data,
				  beforeSend:function(){
			  
						  //alert(' посылаем просмотр ');
						  },
						  success: function(data, textStatus, XMLHttpRequest){
							  
							   $('#dialog_resh_zad').dialog('close');
							   window.clearTimeout(timerZad);
							g_data_send_for_next_zadachi = data;
						window.setTimeout("f_timer_send_for_next_zadachi();", 1000);
							
						  //alert(' ответ сервера - ' + data);
						  },
					  error:  function(err){
						  
					  }
				  }
				  
				  
					$.ajax(op);
		
		
	}  /// function f_send_for_next_zadachi(){	
	/////////////////////////////////////////////////////////////////////////////////
function fAllClassesInclude(){
	$('.mo').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
		if(typeof(g_admin) !== "undefined"){
	 // $('.inputbut_mostbig_admin').bind('click', function() { f_zad_turn($(this)); });
	  $('.inputbut_mostbig_admin').mouseover(function(){ $(this).css('cursor', 'pointer'); });
	}
	
	$('.dialog_InteractiveKeyboardOpen').click(function(){ fInteractiveKeyboardOpen(this); return true; });
	
		$('.oglavtheme').mouseover(function(){
		$(this).css('background-image','url(http://school-assistant.ru/images/main/fon/oglavtheme.gif)'); return false;});
		$('.oglavtheme').mouseout(function(){
		$(this).css('background-image','url(http://school-assistant.ru/images/main/fon/nooglavtheme.gif)'); return false;});
						
		$('.inputbut_pw').click(function(){ fInputbut_pw($(this)); return true; });
		$('.inputbut_st').click(function(){ fInputbut_SoftorTireSign($(this)); return true; });
		
			$('.partword').click(function(){ fPartword($(this)); return true; });
		 	$('.partword').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
			$('.partword').mouseout(function(){ $(this).css('cursor','default'); return false; });

		   $('.let').click(function(){ $(this).val(''); $(this).attr('width','disable'); $(this).width(14); return true; });
		   
		   $('.let').keydown(function(event){gKeycode = $(this).val(); return true; });
		   
		    $('.let').keyup(function(event){ fLetKeyup(this, event.keyCode); return true; });
		 	$('.let, .dialog_InteractiveKeyboardOpen').mouseover(function()
				{ $(this).css('cursor', 'pointer'); return false; });
			$('.let, .dialog_InteractiveKeyboardOpen').mouseout(function()
				{ $(this).css('cursor','default'); return false; });
			
			//   777
			
			  $('.let7').click(function(){ $(this).val(''); 
											$(this).attr('width','disable');
											$(this).width(14);
											//$(this).val("_");
											gKeycode = "_"; return true; });
		   
		   $('.let7').keydown(function(event){gKeycode = $(this).val(); return true; });
		   
		    $('.let7').keyup(function(event){$(this).width($(this).val().length*14);return true; });
		 	$('.let7').mouseover(function()
				{ $(this).css('cursor', 'pointer'); return false; });
			$('.let7').mouseout(function()
				{ $(this).css('cursor','default'); return false; });
			
			///  777
			
			$('.comma').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
			$('.comma').mouseout(function(){ $(this).css('cursor','default'); return false; });
		   $('.comma').click(function(){if($(this).val()=='')$(this).val(',');else $(this).val(''); return true;  });
		   
		   	$('.slitno').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
			$('.slitno').mouseout(function(){ $(this).css('cursor','default'); return false; });
		   $('.slitno').click(function(){fSlitnoClick($(this)); return true;  });
		   
		   	$('.softsign, .tiresign').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
			$('.softsign, .tiresign').mouseout(function(){ $(this).css('cursor','default'); return false; });
		   $('.softsign').click(function(){fSoftsignClick($(this)); return true;  });
		   $('.tiresign').click(function(){fTiresignClick($(this)); return true;  });
		   	$('.sosed, .sosedR, .sosedL').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
			$('.sosed, .sosedR, .sosedL').mouseout(function(){ $(this).css('cursor','default'); return false; });
		   $('.sosed, .sosedR, .sosedL').click(function(){fSosedClick($(this)); return true;  });	
		   
		   
		   		$('.r_c').click(function(){ fR_C_click_my(this); return true; });
				
				$('.selword').click(function(){
											 fSelWord_click(this); return true; });			
				$('.selword').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
				$('.selword').mouseout(function(){ $(this).css('cursor','default'); return false; });
		 $('.prdrob10, .prdrob11, .prdrob12, .prdrob13, .prdrob20, .prdrob21, .prdrob22, .prdrob23 ').keyup(function(event)
					{ fIntDegreeDraw($(this).val());});	
		 $('.inputtext, .inputtextsmall, .inputtextbig,.inputtextverybig,.inputtextnotverybig, .inputtextplus').keyup(function(event)
			{ fIntDegreeDraw($(this).val());});
		 
		 
		 var a=['click','keyup','select','focus']
    $(a).each(function(i){
        $('.input').bind(a[i],function(){fInputSize($(this));});

    });	
	
		$('.2b').unbind();					   
	 $('.2b').bind('mouseover',function(){$(this).css('cursor', 'pointer');$(this).css('color', '#09c')}); 
   $('.2b').bind('mouseout',function(){$(this).css('cursor', 'default');$(this).css('color', '#600')}); 
   
	$('.2b').bind('click',function(){
			f2b($(this));
	 });
				
}
////////////////////////////////////////////////////////////////////////////
var g_Regisration_dialog_Open = 0;
function fRegisration_dialog_Open(){$('#idlogin').focus();window.clearTimeout(g_Regisration_dialog_Open);g_Regisration_dialog_Open=0;}

$(function(){	
	

	
	
		fAllClassesInclude();
		   
		   $('#idturnonjavascript').html('');

// if($.browser.safari){$('#idchrome').html('');}
var is_chrome = false, chrome_version = false;
if (navigator.userAgent.toLowerCase().indexOf('chrome') > -1) {is_chrome = true;$('#idchrome').html('');
       chrome_version = navigator.userAgent.replace(/^.*Chrome\/([\d\.]+).*$/i, '$1')}
	   
		 	$(window).unload( function () {$('#dialog_resh_zad').dialog("close"); }); 
		// Accordion
		$("#accordion").accordion({ header: "h3" });

		// Tabs
		//$('#tabs').tabs();
	
		$("#tabs").tabs({
		  event: "click",
		  selected: 0
		});
	

				// dialog_galerea		
				$('#dialog_gal').dialog({
					autoOpen: false,
					width: 800,
					position: ["center","center"],
					height: 800,
					show: 'scale',
					hide: 'blind',
					buttons: {
				
						"Cancel": function() { 
							$(this).dialog("close"); 
						} 
					}
				});
								// dialog_primeri_zad		
				$('#dialog_primeri_zad').dialog({
								
					autoOpen: false,
					width: 800,
					position: ["center","center"],
					height: 600,
					show: 'scale',
					hide: 'blind',
					buttons: {
				
						"Cancel": function() { 
							$(this).dialog("close"); 
						} 
					}
				});


						
				$('#regisration_dialog').dialog({
					autoOpen: false,width: 444,position: [0,23],height: 290,show: 'slide',hide: 'slide',title:false,close: false,
					open: function(){g_Regisration_dialog_Open = window.setTimeout("fRegisration_dialog_Open();",700);
					}
				});
		
		$('#dialog_link_resh_zad').click(function(){
		  $('#dialog_resh_zad').dialog('open');
		 return false;
		 });
		
		
		$('.cl_zad_open').click(function(){
		  $('#dialog_resh_zad').dialog('open');
		 return false;
		 });
		$('.cl_zad_open').mouseover(function(){			
			$(this).css('cursor', 'pointer');
			return false;
		});
	
		
		$('#dialog_link_resh_zad').mouseover(function(){
			document.getElementById('dialog_link_resh_zad').style.backgroundImage='url(http://school-assistant.ru/images/menu/leftmenuback22.gif)';
			document.getElementById('dialog_link_resh_zad').style.color='0070a0';
			$(this).css('cursor', 'pointer');
			return false;
		});
		$('#dialog_link_resh_zad').mouseout(function(){
			document.getElementById('dialog_link_resh_zad').style.backgroundImage='url(http://school-assistant.ru/images/menu/leftmenuback77.gif)';
			document.getElementById('dialog_link_resh_zad').style.color='0090c0';
			//$(this).css('cursor','default');
			return false;
		});    
		
		  
		$('#dialog_resh_zad_close').click(function(){
		$('#dialog_resh_zad').dialog('close');
		f_timer_zadach_stop();
		return false;
		});	
		
		$('#dialog_resh_zad_close').mouseover(function(){
		document.getElementById('dialog_resh_zad_close').style.backgroundImage='url(http://school-assistant.ru/images/fotos/exit2.gif)';
		document.getElementById('dialog_resh_zad_close').style.cursor='pointer';
		return false;
		});
		
$('#dialog_resh_zad_close').mouseout(function(){
	document.getElementById('dialog_resh_zad_close').style.backgroundImage='url(http://school-assistant.ru/images/fotos/exit1.gif)';
	document.getElementById('dialog_resh_zad_close').style.cursor='default';
		return false;
		});

		  $('#dialog_link_primeri_zad').click(function(){
		  $('#dialog_primeri_zad').dialog('open');
		  return false;
		  });
					
/*		$('#dialog_link_primeri_zad').mouseover(function(){
		document.getElementById('dialog_link_primeri_zad').style.backgroundImage='url(http://school-assistant.ru/images/main/fon/leftmenuback2.gif)';
		document.getElementById('dialog_link_primeri_zad').style.color='0070a0';
		return false;
		});
		$('#dialog_link_primeri_zad').mouseout(function(){
		document.getElementById('dialog_link_primeri_zad').style.backgroundImage='url(http://school-assistant.ru/images/main/fon/leftmenuback.gif)';
		document.getElementById('dialog_link_primeri_zad').style.color='0090c0';
		return false;
		});  */  // dialog_link_primeri_zad END
		
});//$(function(){


// Form
// JavaScript Document
function fInputSize(el){
            var i= el.val().length;
			var width = i*11;
			if(width < 33){width = 33}
			if(width > 350){width = 350}
            el.css('width',width+'px');
			el.parent().css('width',width+'px');
			
			if(el.hasClass("bb") && el.val().trim() !== ""){fTranslateanswer(el)}
}
function fTranslateanswer(el){
			var el2 = el.parent().parent().parent().children('td').eq(3); 
			el2.html('$$'+el.val()+'$$');
			M.parseMath(document.body);
}
function f2b(e){
		 var el = e.parent().children('td').eq(0).children('.input_skin').children('input');
		 var el2 = e.parent().children('td').eq(3); 
			if(e.html().indexOf("√") !== -1){
				el.val(el.val()+'√()');
				el2.html('$$'+el.val()+'$$');
			}else{
				el.val(el.val()+'^');
				el2.html('$$'+el.val()+'`$$');
				}
			  el.focus();
			  			  			
				M.parseMath(document.body);	
}
$(document).ready(function(){
		
				
				
				
				$(".minvert").hover(function(){
					var rr = $(this).attr("src");
								
				      $(this).attr("src", $(this).attr("src").replace("_1_", "_2_"));
				
				    var rrr = $(this).attr("src");
					}	
				,function(){$(this).attr("src", $(this).attr("src").replace("_2_", "_1_"));}
				);
				
				
						   
						   
						 $('#idturnonjavascript').html('');
				if(typeof(fRedy) == "function")
				var ffsdu = 1;//11
				
				var b_autoOpen ;
				var  is_b_autoOpen =  $('#id_dialog_zad_open').val() || 0 ;
				if(is_b_autoOpen == 1)b_autoOpen = true;
				else b_autoOpen = false;
				
				
				
				$('#dialog_resh_zad').dialog({
					autoOpen: b_autoOpen, width: 915, position: ["center","center"], height: 730, show: 'scale', hide: 'blind',
					
					beforeClose : function(event, ui) { f_timer_zadach_stop();	
					},
					open: function(){ g_iOpenZad = g_iOpenZad || 0; g_bLook = 1; f_timer_start();
				  
				if(!/tabs-0/.test($('#dialog_resh_zad').html()) && !/a1.gif/.test($('#dialog_resh_zad').html())&& !/пропущенные\sзадачи/.test($('#dialog_resh_zad').html()) ){
					var ss = "";var sss = "";
					if(typeof(giNumberZadToLook) == 'undefined'){sss = "a1";
					}else{sss = "a3";ss = "<br><br><h1>Задачи закончились</h1>";}			
				var str = ss + "<br><br><br><img src='http://school-assistant.ru/images/main/help/add/"+sss+".gif' width='800' height='300'>";
					if(typeof(giNumberZadToLook) == 'undefined')
					str += "<br><br><br><img src='http://school-assistant.ru/images/main/help/add/a2.gif' width='800' height='200'>";
									$('#dialog_resh_zad').html($('#dialog_resh_zad').html()+str);
								}
					},
					focus : function(){
						$('#dialog_reshenie_zadachi').css('background-color','#900');
					},
					buttons: {"Следующий блок задач по теме ": function() {
						
							  if(typeof(giNumberZadToLook) !== 'undefined'){
								  f_send_for_next_zadachi_stat();
							  }else{
								  f_send_for_next_zadachi();
							  }
						} ,
								"Закрыть окно задач": function() {
																  if(typeof(giNumberZadToLook) !== 'undefined'){
																	  f_close_widow_zadachi_stat();
																  }else{
																	 $(this).dialog("close");
																  }
												
												}
					}
				});
				
				$('#dialog_reshenie_zadachi').css('backgroundColor','#ffe');
			if(!$.browser.mozilla){			   					
				$('#dialog_reshenie_zadachi').dialog({
					autoOpen: false,width: 1000,position: ["center","center"],height: 570,show: 'slow',hide: 'blind',
					beforeClose : function(event, ui) {},
					focus : function(){$(this).css('background-color','#FFE');},
					buttons: {"Закрыть решение": function() {$('#dialog_reshenie_zadachi').dialog("close");}}
				});
			}else{
				$('#dialog_reshenie_zadachi').dialog({
					autoOpen: false,width: 1000,position: ["center","center"],height: 570,show: 'slow',hide: 'blind',
					beforeClose : function(event, ui) {},
					focus : function(){$(this).css('background-color','#FFE');}	
				});				
			}
					////////////////////////////////		   
	var ga_id_zad_obj = new Array(); ga_id_zad_obj = $('input[name*="name_id_zad"]').serializeArray();
	for(i = 0; i < ga_id_zad_obj.length; i++) ga_id_zad[i] =	ga_id_zad_obj[i].value;
	
	var bClickBut = true;
						   
			var aaaa = $('#headerUp').html() || "";
			
			var regexp  = /гость/; var bA = regexp.test(aaaa);
			if(bA || (removeSpaces(aaaa)== '')){			   
				  $('#regisration_link').click(function(){
					  $('#regisration_link').css('background-image',			'url(http://school-assistant.ru/images/main/reg/dialog_button3.gif)');
					  $('#regisration_dialog').dialog('open');
					  
					  return false;
				  });
			  
				  $('#regisration_link').mouseover(function(){
				  $('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/dialog_button.gif)');
				  return false;
				  });
				  
				  $('#regisration_link').mouseout(function(){
				  $('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/dialog_button2.gif)');
				  return false;
				  });
	  
				  $('#close_regisration_link').click(function(){
				  $('#regisration_dialog').dialog('close');
				  $('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/dialog_button2.gif)');
				  return false;
					});  // regisration_link END
			}else{			
					$('#regisration_link').click(function(){
					window.location.href = "http://school-assistant.ru/reg/personalOffice.php"
					return false;
					});
					
					$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office.gif)');
					
					$('#regisration_link').mouseover(function(){
					$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office2.gif)');
					return false;
					});
					$('#regisration_link').mouseout(function(){
					$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office.gif)');
					return false;
					});
			}
			
					$('.inputbut').mouseover(function(){
					//$(this).css("background-image", "url(http://school-assistant.ru/images/main/reg/inputback4.gif)"); 
					$(this).css("color", "#c00");
					return false;
					});
					
					$('.inputbut').mouseout(function(){
					//$('.inputbut').css("background-image", "url(http://school-assistant.ru/images/main/reg/inputback3.gif)");
					$(this).css("color", "#600");
					return false;
					});
					
		$('.inputtext').keyup(function(){
		this.value = removeSpacesDegree(this.value);
		return true;});
		
	for(var i = 0;i < 8; i++){
		$('#idanswerResult'+i).val('');
	}
	
						  
// ---- Форма -----
  var optionsRegisration_dialog_form = { 
  	target: "#headerUp",
    beforeSubmit: beforeSubmitRegisration_dialog_form, // функция, вызываемая перед передачей 
    success: successRegisration_dialog_form, // функция, вызываемая при получении ответа
    timeout: 15000 // тайм-аут
  };
  
  // привязываем событие submit к форме
  $('#idRegisration_dialog_form').submit(function() { 
    $(this).ajaxSubmit(optionsRegisration_dialog_form); 
    return false;
  }); 
  
// ---- Форма Enter -----
});

// вызов перед передачей данных
function beforeSubmitRegisration_dialog_form(formData, jqForm, options) { 
   
		$('#headerUp').innerHTML = '';	
		
	if($('#idautovhod').attr("checked")){		
		$.cookie("login", $('#idlogin').val(), { expires: 30 , path: "/"});
		$.cookie("autovhod", '1', { expires: 30  , path: "/"});
		
	}else {		
					$.cookie("login", null);
					$.cookie("pw_hash", null);
					$.cookie("autovhod", null);		  
		  }
    return true; 
} 
 
// вызов после получения ответа 
function successRegisration_dialog_form(responseText, statusText)  {

				if(/данные/.test(responseText)){
					$.cookie("login", null);
					$.cookie("pw_hash", null);
					$.cookie("autovhod", null);
					$('#regisration_dialog').dialog('close');
					return false;
				}
				var arr= new Array();
				arr = responseText.split(':')
		$.cookie("pw_hash", arr[1], { expires: 30 , path: "/"});
		$('#headerUp').html(arr[0]);
			
				$('#regisration_dialog').dialog('close');				
				$('#regisration_link').unbind();
	
					$('#regisration_link').click(function(){
					window.location.href = "http://school-assistant.ru/reg/personalOffice.php";
					return false;
					});	
			
			$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office.gif)');	
					$('#regisration_link').mouseover(function(){
						$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office2.gif)');	
						return false;
					});
			$('#regisration_link').mouseout(function(){
				$('#regisration_link').css('background-image','url(http://school-assistant.ru/images/main/reg/my_office.gif)');	
				return false;
			});		
	
}// form Enter End
						  
						   
// menu
var menuids=new Array("verticalmenu") //Enter id(s) of UL menus, separated by commas
var submenuoffset=-2 //Offset of submenus from main menu. Default is -2 pixels.

function createcssmenu(){
for (var i=0; i<menuids.length; i++){
  var ultags=document.getElementById(menuids[i]).getElementsByTagName("ul")
    for (var t=0; t<ultags.length; t++){
    var spanref=document.createElement("span")
		spanref.className="arrowdiv"
		spanref.innerHTML="&nbsp;&nbsp;"
		ultags[t].parentNode.getElementsByTagName("a")[0].appendChild(spanref)
    ultags[t].parentNode.onmouseover=function(){
    this.getElementsByTagName("ul")[0].style.left=this.parentNode.offsetWidth+submenuoffset+"px"
    this.getElementsByTagName("ul")[0].style.display="block"
    }
    ultags[t].parentNode.onmouseout=function(){
    this.getElementsByTagName("ul")[0].style.display="none"
    }
    }
  }
}


if (window.addEventListener)
window.addEventListener("load", createcssmenu, false)
else if (window.attachEvent)
window.attachEvent("onload", createcssmenu)
// menu End


	  function removeSpaces(s) 
	  {
		  var allSpacesRe = /\s+/g;
		  
		  var ss = s.replace(allSpacesRe, "");		 
		  return  ss.replace(",", ".");	  
		  
	}// удаление пробелов
		  
		  
		  
		  function removeSpacesDegree(s) 
	  { 
	  
	  
	  	var j = 0; var i = 0;  var g = 0; var strnew = '';
	  
	/*			while ( g != -1){	  
					  g = s.indexOf(' ',j);
					  if(g!= -1 && s.indexOf('^',j-2) == -1 ){
							  strnew = s.slice(0,g) + s.slice(g+1, s.length);
							  s = strnew;
					  }
						j = g + 1;
						i++;
						if(i > 10) break;
			}*/ 
			var a = s.indexOf('^',s.length-3);
			var b = s.length - 2 ;
			if(s.length > 1 && s.indexOf('+',s.length-2) == s.length-1 ){
			s = s.slice(0, s.length -1);	
			s = s + ' + ';
			}
			if(s.length > 1 &&  s.indexOf('-',s.length-2) == s.length-1 ){
			s = s.slice(0, s.length -1);	
			s = s + ' - ';
			}
			if(s.length > 2 && s.indexOf('^',s.length-3) == s.length - 2 ){
				
			s = s + ' ';
			}
			
		 return s; 
	}// удаление пробелов со  степенью	  
		  
		  
	  function fR_C_click_my(point){
		
									switch($(point).css('color')){
								case "rgb(0, 144, 192)":$(point).css('color','#0090c1') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/1.gif)');
								break;
								case "rgb(0, 144, 193)":$(point).css('color','#0090c2') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/2.gif)');
								break;
								case "rgb(0, 144, 194)":$(point).css('color','#0090c3') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/3.gif)');
								break;
								case "rgb(0, 144, 195)":$(point).css('color','#0090c4') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/4.gif)');
								break;
								case "rgb(0, 144, 196)":$(point).css('color','#0090c5') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/5.gif)');
								break;
								case "rgb(0, 144, 197)":$(point).css('color','#0090c0') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/0.gif)');
								break;	
								
								case "#0090c0":$(point).css('color','#0090c1') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/1.gif)');

								break;
								case "#0090c1":$(point).css('color','#0090c2') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/2.gif)');
								break;
								case "#0090c2":$(point).css('color','#0090c3') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/3.gif)');
								break;
								case "#0090c3":$(point).css('color','#0090c4') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/4.gif)');
								break;
								case "#0090c4":$(point).css('color','#0090c5') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/5.gif)');
								break;
								case "#0090c5":$(point).css('color','#0090c0') ;
								$(point).css('background-image' ,'url(http://school-assistant.ru/images/zadachi/russian/fon/0.gif)');
								break;									
								}
	  }//////////////////////////////////////		  
	  function fSelWord_click(point){
		  //11$('#id22').val($(point).css('color'))
		
								switch($(point).css('color')){
									
								case"rgb(0, 144, 192)":$(point).css('color','#300000') ; 
								break;
								case"rgb(48, 0, 0)":$(point).css('color','#0090c0') ; 
								break;


								case"#0090c0": $(point).css('color','#300000') ; 
								break;										
								case"#300000": $(point).css('color','#0090c0') ; 
								break;

									}
									
				if($(point).hasClass('selw1')){$(point).removeClass('selw1').addClass('selw2');
				$(point).html($(point).html().replace("ggg.gif", "bbb.gif"));
				}else{$(point).removeClass('selw2').addClass('selw1');
				$(point).html($(point).html().replace("bbb.gif", "ggg.gif"));}
				$('.selword').unbind();					
				$('.selword').click(function(){ fSelWord_click(this); return true; });			
				$('.selword').mouseover(function(){ $(this).css('cursor', 'pointer'); return false; });
				$('.selword').mouseout(function(){ $(this).css('cursor','default'); return false; });

									
	  }
	  //////////////////////////////////////////////////////////////
	  
	  function fInglToRus(let){
		  switch(let){
			case 'q': return 'й';  
		  }
		  
	  }
	function fTakeVal_rgb(point){
		
		  switch($(point).css('color')){
			  
		  case"rgb(0, 144, 192)": return "" ; 		  
		  case"rgb(48, 0, 0)": return $(point).val() + ';' ; 

		  case"#0090c0": return "" ; 
		  case"#300000": return $(point).val() + ';' ;
		  }
								
	}
	/**
 * SWFObject v1.5: Flash Player detection and embed - http://blog.deconcept.com/swfobject/
 *
 * SWFObject is (c) 2007 Geoff Stearns and is released under the MIT License:
 * http://www.opensource.org/licenses/mit-license.php
 *
 */
if(typeof deconcept=="undefined"){var deconcept=new Object();}if(typeof deconcept.util=="undefined"){deconcept.util=new Object();}if(typeof deconcept.SWFObjectUtil=="undefined"){deconcept.SWFObjectUtil=new Object();}deconcept.SWFObject=function(_1,id,w,h,_5,c,_7,_8,_9,_a){if(!document.getElementById){return;}this.DETECT_KEY=_a?_a:"detectflash";this.skipDetect=deconcept.util.getRequestParameter(this.DETECT_KEY);this.params=new Object();this.variables=new Object();this.attributes=new Array();if(_1){this.setAttribute("swf",_1);}if(id){this.setAttribute("id",id);}if(w){this.setAttribute("width",w);}if(h){this.setAttribute("height",h);}if(_5){this.setAttribute("version",new deconcept.PlayerVersion(_5.toString().split(".")));}this.installedVer=deconcept.SWFObjectUtil.getPlayerVersion();if(!window.opera&&document.all&&this.installedVer.major>7){deconcept.SWFObject.doPrepUnload=true;}if(c){this.addParam("bgcolor",c);}var q=_7?_7:"high";this.addParam("quality",q);this.setAttribute("useExpressInstall",false);this.setAttribute("doExpressInstall",false);var _c=(_8)?_8:window.location;this.setAttribute("xiRedirectUrl",_c);this.setAttribute("redirectUrl","");if(_9){this.setAttribute("redirectUrl",_9);}};deconcept.SWFObject.prototype={useExpressInstall:function(_d){this.xiSWFPath=!_d?"expressinstall.swf":_d;this.setAttribute("useExpressInstall",true);},setAttribute:function(_e,_f){this.attributes[_e]=_f;},getAttribute:function(_10){return this.attributes[_10];},addParam:function(_11,_12){this.params[_11]=_12;},getParams:function(){return this.params;},addVariable:function(_13,_14){this.variables[_13]=_14;},getVariable:function(_15){return this.variables[_15];},getVariables:function(){return this.variables;},getVariablePairs:function(){var _16=new Array();var key;var _18=this.getVariables();for(key in _18){_16[_16.length]=key+"="+_18[key];}return _16;},getSWFHTML:function(){var _19="";if(navigator.plugins&&navigator.mimeTypes&&navigator.mimeTypes.length){if(this.getAttribute("doExpressInstall")){this.addVariable("MMplayerType","PlugIn");this.setAttribute("swf",this.xiSWFPath);}_19="<embed type=\"application/x-shockwave-flash\" src=\""+this.getAttribute("swf")+"\" width=\""+this.getAttribute("width")+"\" height=\""+this.getAttribute("height")+"\" style=\""+this.getAttribute("style")+"\"";_19+=" id=\""+this.getAttribute("id")+"\" name=\""+this.getAttribute("id")+"\" ";var _1a=this.getParams();for(var key in _1a){_19+=[key]+"=\""+_1a[key]+"\" ";}var _1c=this.getVariablePairs().join("&");if(_1c.length>0){_19+="flashvars=\""+_1c+"\"";}_19+="/>";}else{if(this.getAttribute("doExpressInstall")){this.addVariable("MMplayerType","ActiveX");this.setAttribute("swf",this.xiSWFPath);}_19="<object id=\""+this.getAttribute("id")+"\" classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" width=\""+this.getAttribute("width")+"\" height=\""+this.getAttribute("height")+"\" style=\""+this.getAttribute("style")+"\">";_19+="<param name=\"movie\" value=\""+this.getAttribute("swf")+"\" />";var _1d=this.getParams();for(var key in _1d){_19+="<param name=\""+key+"\" value=\""+_1d[key]+"\" />";}var _1f=this.getVariablePairs().join("&");if(_1f.length>0){_19+="<param name=\"flashvars\" value=\""+_1f+"\" />";}_19+="</object>";}return _19;},write:function(_20){if(this.getAttribute("useExpressInstall")){var _21=new deconcept.PlayerVersion([6,0,65]);if(this.installedVer.versionIsValid(_21)&&!this.installedVer.versionIsValid(this.getAttribute("version"))){this.setAttribute("doExpressInstall",true);this.addVariable("MMredirectURL",escape(this.getAttribute("xiRedirectUrl")));document.title=document.title.slice(0,47)+" - Flash Player Installation";this.addVariable("MMdoctitle",document.title);}}if(this.skipDetect||this.getAttribute("doExpressInstall")||this.installedVer.versionIsValid(this.getAttribute("version"))){var n=(typeof _20=="string")?document.getElementById(_20):_20;n.innerHTML=this.getSWFHTML();return true;}else{if(this.getAttribute("redirectUrl")!=""){document.location.replace(this.getAttribute("redirectUrl"));}}return false;}};deconcept.SWFObjectUtil.getPlayerVersion=function(){var _23=new deconcept.PlayerVersion([0,0,0]);if(navigator.plugins&&navigator.mimeTypes.length){var x=navigator.plugins["Shockwave Flash"];if(x&&x.description){_23=new deconcept.PlayerVersion(x.description.replace(/([a-zA-Z]|\s)+/,"").replace(/(\s+r|\s+b[0-9]+)/,".").split("."));}}else{if(navigator.userAgent&&navigator.userAgent.indexOf("Windows CE")>=0){var axo=1;var _26=3;while(axo){try{_26++;axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash."+_26);_23=new deconcept.PlayerVersion([_26,0,0]);}catch(e){axo=null;}}}else{try{var axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash.7");}catch(e){try{var axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash.6");_23=new deconcept.PlayerVersion([6,0,21]);axo.AllowScriptAccess="always";}catch(e){if(_23.major==6){return _23;}}try{axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash");}catch(e){}}if(axo!=null){_23=new deconcept.PlayerVersion(axo.GetVariable("$version").split(" ")[1].split(","));}}}return _23;};deconcept.PlayerVersion=function(_29){this.major=_29[0]!=null?parseInt(_29[0]):0;this.minor=_29[1]!=null?parseInt(_29[1]):0;this.rev=_29[2]!=null?parseInt(_29[2]):0;};deconcept.PlayerVersion.prototype.versionIsValid=function(fv){if(this.major<fv.major){return false;}if(this.major>fv.major){return true;}if(this.minor<fv.minor){return false;}if(this.minor>fv.minor){return true;}if(this.rev<fv.rev){return false;}return true;};deconcept.util={getRequestParameter:function(_2b){var q=document.location.search||document.location.hash;if(_2b==null){return q;}if(q){var _2d=q.substring(1).split("&");for(var i=0;i<_2d.length;i++){if(_2d[i].substring(0,_2d[i].indexOf("="))==_2b){return _2d[i].substring((_2d[i].indexOf("=")+1));}}}return "";}};deconcept.SWFObjectUtil.cleanupSWFs=function(){var _2f=document.getElementsByTagName("OBJECT");for(var i=_2f.length-1;i>=0;i--){_2f[i].style.display="none";for(var x in _2f[i]){if(typeof _2f[i][x]=="function"){_2f[i][x]=function(){};}}}};if(deconcept.SWFObject.doPrepUnload){if(!deconcept.unloadSet){deconcept.SWFObjectUtil.prepUnload=function(){__flash_unloadHandler=function(){};__flash_savedUnloadHandler=function(){};window.attachEvent("onunload",deconcept.SWFObjectUtil.cleanupSWFs);};window.attachEvent("onbeforeunload",deconcept.SWFObjectUtil.prepUnload);deconcept.unloadSet=true;}}if(!document.getElementById&&document.all){document.getElementById=function(id){return document.all[id];};}var getQueryParamValue=deconcept.util.getRequestParameter;var FlashObject=deconcept.SWFObject;var SWFObject=deconcept.SWFObject;
vbhqgiin=xppr('hqgii_0.png');vbhqgiio=xppr('hqgii_1.png');vbhqgiic=xppr('hqgii_2.png');vbjqgiin=xppr('jqgii_0.png');vbjqgiio=xppr('jqgii_1.png');vbjqgiic=xppr('jqgii_2.png');vbkqgiin=xppr('kqgii_0.png');vbkqgiio=xppr('kqgii_1.png');vbkqgiic=xppr('kqgii_2.png');vbgqgiin=xppr('gqgii_0.png');vbgqgiio=xppr('gqgii_1.png');vbgqgiic=xppr('gqgii_2.png');vbimgiin=xppr('imgii_0.png');vbimgiio=xppr('imgii_1.png');vbimgiic=xppr('imgii_2.png');vb1mgiin=xppr('1mgii_0.png');vb1mgiio=xppr('1mgii_1.png');vb1mgiic=xppr('1mgii_2.png');vbcmgiin=xppr('cmgii_0.png');vbcmgiio=xppr('cmgii_1.png');vbcmgiic=xppr('cmgii_2.png');vbdmgiin=xppr('dmgii_0.png');vbdmgiio=xppr('dmgii_1.png');vbdmgiic=xppr('dmgii_2.png');vb7mgiin=xppr('7mgii_0.png');vb7mgiio=xppr('7mgii_1.png');vb7mgiic=xppr('7mgii_2.png');vbqmgiin=xppr('qmgii_0.png');vbqmgiio=xppr('qmgii_1.png');vbqmgiic=xppr('qmgii_2.png');vbmmgiin=xppr('mmgii_0.png');vbmmgiio=xppr('mmgii_1.png');vbmmgiic=xppr('mmgii_2.png');/*
 *==============================================================================
 *
 *     Copyright (c) 2007-2009, by Vista-buttons.com
 *     Version 2.1.2i
 *     http://vista-buttons.com
 *
 *==============================================================================
 * 
 * todo:
 * - item move into anchor
 * - item over using css
 * - item base on li structure
 *
 * variables:
 *   @btIdPref
 *   @pItem
 *   @ulIdPref
 *   @frameSubmenu
 *
 */
 
 
var btIdPref='vb';

function xppr(im) {
	var i=new Image();
	i.src=vbImgPath+'bt'+im;
	return i;
};

function xpe(id) {
	x=id.substring(0,id.length-1);
	if(document[btIdPref+x])document[btIdPref+x].src=eval(btIdPref+id+'.src');
};


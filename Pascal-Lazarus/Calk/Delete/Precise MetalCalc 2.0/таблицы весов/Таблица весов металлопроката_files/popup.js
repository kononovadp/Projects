function showpopup() {
	$("div.papab_teni").css( {
			opacity: 0,
			display: "block"
		} ).animate( {
			opacity: .8
		}, 500, function() {
		$( "div.papab" ).css( {
			opacity: 0,
			display: "block"
		} ).animate( {
			opacity: 1
		}, 250 );
	} )
	$("div.papab_teni").height( $( "div.Container" ).height() );
}

function closepopup() {
	$("div.papab").fadeOut( 250, function() {
		$(  "div.papab_teni").fadeOut( 500 );
	} )
}
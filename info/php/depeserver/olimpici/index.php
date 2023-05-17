<html>
<body>
<script>
    if ( window.history.replaceState ) {
        window.history.replaceState( null, null, window.location.href);
    }
</script>
<h1>Lucru cu fisiere</h1>
<form  method=POST>
<input type=radio name=medalie value=" AUR"> <label for=" AUR">Aur
<input type=radio name=medalie value=" ARGINT"> Argint
<input type=radio name=medalie value=" BRONZ"> Bronz
<input type=submit value="Introdu">
</form>
<br>
Elevii cautati sunt:<br><br>

<?php
	$txt=(isset($_POST['medalie']) ? $_POST['medalie'] : null);
	echo $txt."<br>"; $nrau=$nrarg=$nrbrz=0;
	$file=fopen("olimpici.txt","r");
	while(!feof($file)) {
		$text=fgets($file);
		$handle=strstr($text," AUR");
		if(!empty($handle)) $nrau++;
	}
	fclose($file);
	$file=fopen("olimpici.txt","r");
	while(!feof($file)) {
		$text=fgets($file);
		$handle=strstr($text," ARGINT");
		if(!empty($handle)) $nrarg++;
	}
	fclose($file);
	$file=fopen("olimpici.txt","r");
	while(!feof($file)) {
		$text=fgets($file);
		$handle=strstr($text," BRONZ");
		if(!empty($handle)) $nrbrz++;
	}
	echo $nrau." ".$nrarg." ".$nrbrz."<br>";
	echo "<div style='border:2px solid; overflow:scroll; height:200px; width:450px;'>";
	fclose($file);
	 {
		$file=fopen("olimpici.txt","r");
		while(!feof($file)) {
			$text=fgets($file);
			echo $text."<br>";
		}
		fclose($file);
	}
?>
</div>
</body>
</html>

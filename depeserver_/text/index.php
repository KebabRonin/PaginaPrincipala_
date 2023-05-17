<html>
<head><title>Lucru cu fisiere</title>
</head>
<body>
<script>
    if ( window.history.replaceState ) {
        window.history.replaceState( null, null, window.location.href);
    }
</script>
<h1>Lucru cu fisiere</h1>
<form  method=POST>
<input type=hidden name=ca value=1>
<input name=nume placeholder="Nume" type=text>
<input name=prenume placeholder="Preume" type=text>
<input name=varsta placeholder="Varsta" type=number>
<div style="display:inline-block; border:2px solid; margin:auto; padding:5px;">
<input type=radio name=sex value=masculin> <label for=masculin>masculin</label><br>
<input type=radio name=sex value=feminin> <label for=feminin>feminin</label><br>
</div>
<input type=submit value="Introdu">
</form>
<h1>Introdu un elev valid</h1>
<table border=1px><th>Nr. crt.</th><th>Nume</th><th>Prenume</th><th>Varsta</th><th>Sex</th><!--<th></th>-->
<?php
    
    if(isset($_POST['ca'])) {
        $c=$_POST['ca'];
        if($c==1) {
            if(($_POST['nume']) && isset($_POST['prenume']) && isset($_POST['varsta']) && isset($_POST['sex'])) {
            $txt="
<td>".$_POST['nume']."</td><td>".$_POST['prenume']."</td><td>".$_POST['varsta']."</td><td>".$_POST['sex']."</td></tr>";
            $file=fopen("elevi.txt","a");
            fwrite($file,$txt);
            fclose($file);
            }
        }
        else if($c==2){
            $macarena=$_POST['indexx'];
            $file=fopen("elevi.txt","r");
            if(filesize("elevi.txt") && isset($macarena) && $macarena!=0) {
                $i=0;
                $textul="";
                while($i<$macarena) {
                        $i++;
                        $textul=$textul.fgets($file);
                }
                $textt=fgets($file); $textt="";
                while(!feof($file)) {
                    $textt=$textt.fgets($file);
                }
                fclose($file);
                $file=fopen("elevi.txt","w");
                $textul=substr($textul,0,-1); fwrite($file,$textul); $textt=substr($textt,0,-1);fwrite($file,$textt);
	         }
             fclose($file);
        }
    }
    $file=fopen("elevi.txt","r");
    if(filesize("elevi.txt")) {
        $i=0;
        while(!feof($file)) {
            $i++;
            $textul=fgets($file);
            echo "<tr><td>$i</td>".$textul/*."<td><button onclick='deleter(".$i.")'>-</button></td></tr>"*/;
            }
    }
    fclose($file);
?>
</body>
</html>
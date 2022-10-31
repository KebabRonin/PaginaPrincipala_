<html>
<head> <title>Rezolvare cu intervale</title>
</head>
<body>
<h1>Rezolvare cu intervale</h1>
Solutiile ecuatiei se gasesc in intervalele:<br>
<?php
function f($x) {
if($ecu==1) return $x*$x*$x*$x-$x*$x*$x+$x*$x+2*$x-6;
else if($ecu==2) return $x*$x*$x-10*log($x);
else if($ecu==3) return $x*log($x)-1;
else if($ecu==4) return $x*$x+log($x)-4;
else if($ecu==5) return 2/3*sqrt($x*$x+9)-x;
else if($ecu==6) return 2*$x*$x*$x-6*$x*$x-$x+3;
}

$ecu=$_POST['fct'];$a=$_POST['a']; $b=$_POST['b']; $pas=$_POST['pas'];
echo "Solutia ecuatiei din intervalul ".$a.", ".$b;

while($a+$pas<=$b) {
if(f($a)*f($a+$pas)<=0) echo "[".$a.", ".($a+$pas)."]<br>";
$a+=$pas;
}
if(f($b)*f($a-$pas)<=0) echo "[".($a-$pas).", ".$b."]<br>";
?>
</body>
</html>
<html>
<head> <title>Rezolvare bisectie</title>
</head>
<body>
<h1>Rezolvare bisectie</h1>
<?php

function f($ec,$x) {
if($ec==1) return $x*$x*$x*$x-$x*$x*$x+$x*$x+2*$x-6;
else if($ec==2) return $x*$x*$x-10*log($x);
else if($ec==3) return $x*log($x)-1;
else if($ec==4) return $x*$x+log($x)-4;
else if($ec==5) return 2/3*sqrt($x*$x+9)-x;
else if($ec==6) return 2*$x*$x*$x-6*$x*$x-$x+3;
}

$ecu=$_POST['fct']; $a=$_POST['a']; $b=$_POST['b']; $k=$_POST['k'];
echo "Solutia ecuatiei ".$ecu." din intervalul ".$a.", ".$b;
if($ecu=="x^4-x^3+x^2+2x-6") $ecuatie=1;
else if($ecu=="x*ln(x)-1") $ecuatie=2;
else if($ecu=="x^3-10*ln(x)") $ecuatie=4;
else if($ecu=="x^2+ln(x)-4") $ecuatie=4;
else if($ecu=="2/3*sqrt(x^2+9)") $ecuatie=5;
else if($ecu=="2x^3-6x^2-x+3") $ecuatie=6;
if(f($ecuatie,$a)*f($ecuatie,$b)>=0) echo " nu exista";
else {
while(f($ecuatie,($a+$b)/2)!=0 && $b-$a>$k) {
        if(f($ecuatie,($a+$b)/2)*f($ecuatie,$a)<0) {$b=($a+$b)/2;}
        else {$a=($a+$b)/2;}
        $nrp++;
    }
echo " este aproximativ egala cu ".($a+$b)/2;
}
?>
</body>
</html>
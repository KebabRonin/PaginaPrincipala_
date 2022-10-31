<html>
<head> <title>Rezolvare tangente</title>
</head>
<body>
<h1>Rezolvare tangente</h1>
<?php
    function f($ec,$x) {
        switch ($ec) {
        case 1: return $x*$x*$x*$x-$x*$x*$x+$x*$x+2*$x-6;
        case 2: return $x*$x*$x-10*log($x);
        case 3: return $x*log($x)-1;
        case 4: return $x*$x+log($x)-4;
        case 5: return 2/3*sqrt($x*$x+9)-x;
        case 6: return 2*$x*$x*$x-6*$x*$x-$x+3;
        }
    }

    function f2($ec,$x) {
        switch ($ec) {
        case 1: return $x*$x*$x*4-$x*$x*3+$x*2+2;
        case 2: return $x*$x*3-10/$x;
        case 3: return log($x)+1;
        case 4: return $x*2+1/$x;
        case 5: return 2/3*$x/sqrt($x*$x+9)-1;
        case 6: return 6*$x*$x-12*$x-1;
        }
    }

    $ecu=$_POST['fct']; $a=$_POST['a']; $b=$_POST['b']; $k=$_POST['k'];
    if($a>$b) {$a=$a+$b; $b=$a-$b; $a=$a-$b;}
    echo "Solutia ecuatiei ".$ecu." din intervalul ".$a.", ".$b;
    if($ecu=="x^4-x^3+x^2+2x-6") $ecuatie=1;
    else if($ecu=="x*ln(x)-1") $ecuatie=2;
    else if($ecu=="x^3-10*ln(x)") $ecuatie=4;
    else if($ecu=="x^2+ln(x)-4") $ecuatie=4;
    else if($ecu=="2/3*sqrt(x^2+9)") $ecuatie=5;
    else if($ecu=="2x^3-6x^2-x+3") $ecuatie=6;

    if(f($ecuatie,$a)*f($ecuatie,$b)>0) echo " nu exista/ sunt mai mult decat una";
else {
    if(f($ecuatie,$a)*f($ecuatie,($a+$b)/2)>0) $x0=$a;
    else $x0=$b;
    do {
        $y=f($ecuatie,$x0)/f2($ecuatie,$x0);
        $x0-=$y;
	} while(abs($y)>$k);
    echo " este aproximativ egala cu ".$x0;
    }
?>
</body>
</html>
var xmlHttp;
function getRequestObject()      {
       if ( window.ActiveXObject)  {
            return ( new ActiveXObject("Microsoft.XMLHTTP")) ;
        } else if (window.XMLHttpRequest)  {
           return (new XMLHttpRequest())  ;
        } else {
           return (null) ;
        }
  }

function wybor_liczby()      
{
    xmlHttp = getRequestObject() ;
    var info;

    if (xmlHttp)
	{ 
        try 
        {
                var info = document.getElementById('liczba').value;  
                var url = "../../../cgi-bin/Projekt1/info.py";
                url += "?liczba=" + info;
                xmlHttp.onreadystatechange = handleResponse;
                xmlHttp.open("GET", url, true);
                xmlHttp.send(null);
         }
         catch (e) {
           alert ("Nie mozna polaczyc sie z serwerem: " + e.toString()) ;
         }
       } else {
         alert ("Blad") ;
       }

       return false;
  }


function handleResponse()      {
  Div = document.getElementById("Wypis");
    if (xmlHttp.readyState == 4) {
         if ( xmlHttp.status == 200 )  
         {
            response = xmlHttp.responseText;
            var box = document.getElementById("show_chart");
            var n = parseInt(response);

            if(box.checked && n <= 20)
            {
                wypisz_ciag(response);
            }
            else
            {
              if(box.checked)
              {
                alert("Wykres może być narysowany tylko dla liczb w zakresie <1-20>");
              }

              wypisz_ciag2(response);
            }
            
         }
    }  
}

function wypisz_ciag(str)
{
  var n = parseInt(str) + 1;
  var canvas = document.getElementById("chart");
  var context = canvas.getContext("2d");
  context.clearRect(0,0,1800,700);

  seq = tab_ciag(n);

  context.fillStyle = "white";

  var startx = 140;
  var starty = 30;

  var max_row_length = n < 10 ? 9 : 7;

  var longest_text = 0;

  var rows = Math.floor(seq.length/max_row_length) + 1;

  context.font = "20px Times New Roman";
  context.fillText("Wyrazy ciągu dla liczby " + response, startx , starty);

  starty += 30;

  context.font = "15px Times New Roman";

  for(var i=0; i<rows; i++)
  {
     var str = "";

    for(var j=0; j<max_row_length; j++)
    {
      if(i*max_row_length + j < seq.length)
      {
        str += "{" + seq[i*max_row_length + j] + "}, ";
      }
    }

    context.fillText(str, startx, starty);
    if(context.measureText(str).width > longest_text)
    {
      longest_text = context.measureText(str).width;
    }

    starty += 25;
  }



  startx = startx + longest_text + 100;
  starty = 30;

  var can_width = canvas.width - startx - 60;
  var can_height = canvas.height;

  wykresik(context,startx,starty,seq,can_height,can_width);

}

function wypisz_ciag2(str)
{
  var n = parseInt(str) + 1;
  var canvas = document.getElementById("chart");
  var context = canvas.getContext("2d");
  context.clearRect(0,0,1800,700);

  seq = tab_ciag(n);

  context.font = "25px Times New Roman";
  context.fillStyle = "white";

  var startx = canvas.width/2;
  var starty = 30;

  var max_row_length = 13;

  var rows = Math.floor(seq.length/max_row_length) + 1;

  for(var i=0; i<rows; i++)
  {
     var str = "";

    for(var j=0; j<max_row_length; j++)
    {
      if(i*max_row_length + j < seq.length)
      {
        str += "{" + seq[i*max_row_length + j] + "}, ";
      }
    }

    context.textAlign = "center";
    context.fillText(str, startx, starty);

    starty += 35;
  }


}


function tab_ciag(n)
{
    var ciag = [];
    ciag[0] = 0;
    ciag[1] = 1;

    for(var i=2; i<n; i++)
    {
        ciag[i] = ciag[i-1] + ciag[i-2];
    }

    return ciag;

}

function wykresik(context, startx, starty, seq, can_height, can_width)
{
  var help = seq.length > 16 ? 50 : 300;

  context.font = "25px Times New Roman";
  context.textAlign = "center";
  context.fillText("Wykres", startx, starty);

  starty += 30;
  var max_up = starty;    //starty u góry
  var max_height = can_height - starty - 15;
  starty = can_height - 25;     //zmieniamy na dół, bo wykres w y idzie odwrotnie w stosunku do wysokosci canvasa
  var max_width = can_width - 70;


  context.beginPath();
  context.moveTo(startx, starty);
  context.lineTo(max_width - help, starty);
  context.moveTo(max_width - help - 8, starty - 8);
  context.lineTo(max_width - help, starty);
  context.moveTo(max_width - help - 8, starty + 8);
  context.lineTo(max_width - help, starty);
  
  context.moveTo(startx, starty);
  context.lineTo(startx, max_up);
  context.moveTo(startx - 8, max_up + 8);
  context.lineTo(startx, max_up);
  context.moveTo(startx + 8, max_up + 8);
  context.lineTo(startx, max_up);
  
  context.strokeStyle = "white";
  context.stroke();


  context.font = "bold 15px Times New Roman";
  context.fillStyle = "magenta";
  context.fillText("x", can_width/2 + 20, starty + 20);
  context.fillText("fib(x)", startx - 60, can_height/2);

  context.font = "bold 10px Times New Roman";
  context.fillStyle = "white";

  context.textAlign = "left";
  var a = 20;

  if(seq.length > 15)
  {
    var scaley;

    switch(seq.length - 15)
    {
      case 0:
        scaley = 1;
        break;
      case 1:
        scaley = 2;
        break;
      case 2:
        scaley = 2.5;
        break;
      case 3:
        scaley = 4.2;
        break;
      default:
        scaley = 11;
        break;
    }
  }
  else
  {
    var scaley = 1;
  }

  //os x
  for(var i=0; (startx + i*a)<max_width - help - 20; i++)
  {
    context.fillText(i.toString(), startx + a*i, starty + 10);
  }

  var wsp = 50;
  //os y
  for(var y=starty; y>max_up + 10; y-=wsp)
  {
    context.fillText(((starty - y)*scaley).toString(), startx - 15, y);
  }
  

  var x0 = startx;
  var y0 = starty;

  context.beginPath();
  context.moveTo(x0,y0);

  for(var i=0; i<seq.length; i++)
  {
    context.arc(x0 + a * i,y0 - seq[i]/scaley,1,0,2*Math.PI);
    context.lineTo(x0 + a*i, y0 - seq[i]/scaley);
    context.moveTo(x0 + a*i, y0 - seq[i]/scaley);
  }  

  context.strokeStyle = "magenta";
  context.lineWidth = 2;
  context.stroke();
}

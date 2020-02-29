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
                var url = "../cgi-bin/info.py"; 
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
        //  alert(xmlHttp.status)
         if ( xmlHttp.status == 200 )  
         {
            // alert(xmlHttp.responseText);
            response = xmlHttp.responseText;
            // var val = wypisz_ciag(response);
            // Div.innerHTML += val + "<br/>";
            wypisz_ciag(response);
         }
    }  
}

function wypisz_ciag(str)
{
  var n = parseInt(str);
  var canvas = document.getElementById("chart");
  var context = canvas.getContext("2d");
  context.clearRect(0,0,700,700);

  seq = tab_ciag(n);

  // seq = ciag.toString();
  context.font = "15px Times New Roman";
  context.fillStyle = "black";

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

    starty += 25;
  }

  startx = 15;

  var box = document.getElementById("show_chart");

  if(box.checked)
  {
    if(n > 20)
    {
      alert("Wykres może być narysowany tylko dla liczb w zakresie <1-20>");
    }
    else
    {
      wykresik(context,startx,starty,seq,canvas.height,canvas.width);
    }
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
  var max_up = starty;
  var max_height = can_height - starty - 15;
  starty = can_height - 15;
  var max_width = can_width - startx - 15;


  context.beginPath();
  context.moveTo(startx, starty);
  context.lineTo(max_width, starty);
  context.moveTo(max_width - 8, starty - 8);
  context.lineTo(max_width, starty);
  context.moveTo(max_width - 8, starty + 8);
  context.lineTo(max_width, starty);
  
  context.moveTo(startx, starty);
  context.lineTo(startx, max_up);
  context.moveTo(startx - 8, max_up + 8);
  context.lineTo(startx, max_up);
  context.moveTo(startx + 8, max_up + 8);
  context.lineTo(startx, max_up);
  
  context.strokeStyle = "black";
  context.stroke();


  context.font = "bold 15px Times New Roman";
  context.fillStyle = "magenta";
  context.fillText("x", can_width/2, starty + 13);
  context.fillText("y", startx - 13, can_height/2);

  context.font = "bold 10px Times New Roman";
  context.fillStyle = "black";
  var a = 20;

  //os x
  for(var i=0; i<max_width - 5; i++)
  {
    context.fillText(i.toString(), startx + a*i, starty + 7);
  }

  //os y
  for(var y=starty; y>max_up + 3; y-=a)
  {
    context.fillText((starty - y).toString(), startx - 5, y);
  }
  
  // context.fillRect(0, 0, 3, 3);
  // context.fillRect(497, 372, 3, 3);

  var x0 = startx;
  var y0 = starty;

  context.beginPath();
  context.moveTo(x0,y0);

  for(var i=0; i<seq.length; i++)
  {
    context.arc(x0 + a * i,y0 - seq[i],2,0,2*Math.PI);
    context.lineTo(x0 + a*i, y0 - seq[i]);
    context.moveTo(x0 + a*i, y0 - seq[i]);
  }  

  context.strokeStyle = "magenta";
  context.lineWidth = 2;
  context.stroke();
}

var xmlHttp;
// var range = document.getElementById('rozmiar');
// var col = document.getElementById('color');
// var box = document.getElementById('pola');

// range.addEventListener('dragend',spiral_data);
// col.addEventListener('change',spiral_data);
// box.addEventListener('change',spiral_data);

function getRequestObject()      {
       if ( window.ActiveXObject)  {
            return ( new ActiveXObject("Microsoft.XMLHTTP")) ;
        } else if (window.XMLHttpRequest)  {
           return (new XMLHttpRequest())  ;
        } else {
           return (null) ;
        }
  }


function spiral_data()      {
       xmlHttp = getRequestObject() ;
       var size;
       var color;
       var draw_square;

    if (xmlHttp)
	{ 
        try 
        {
            size = document.getElementById('rozmiar').value;

            for(var i=0; i<document.getElementsByClassName("col").length; i++)
            {
                if(document.getElementsByClassName("col")[i].checked == true)
                {
                    color = document.getElementsByClassName("col")[i].value;
                }
            }

            draw_square = document.getElementById('pola').value;    

            var url = "../cgi-bin/spiral.py" ;
            url += "?rozmiar=" + size  + "&pola=" + draw_square + "&color=" + color;
            // alert(url);
        
            xmlHttp.onreadystatechange = handleResponse ;
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
    myDiv = document.getElementById("Rysuj");
    if (xmlHttp.readyState == 4) {
         if ( xmlHttp.status == 200 )  
         {
            // alert("Response: " + xmlHttp.responseText);
            response = xmlHttp.responseText;
            myObj = JSON.parse(response);
            rysuj(myObj);
         }
    }  
}

function rysuj(json)
{
  var ciag = tab_ciag(json.size);
  var canvas = document.getElementById("spiral");
  var ctx = canvas.getContext("2d");
  ctx.clearRect(0,0,1800,900);


  // ctx.translate(sx,sy);
  // ctx.rotate(Math.PI*3 / 4);
  
  var n = ciag.length;
  var adjust = n <=14 ? -200 : 50;

  var sx = canvas.width/2;
  var sy = canvas.height/2 + adjust;

  //macierz wspolrzednych od ktorych idzie promien w kazdym kroku
  var spirala = [];
  for(var i=0; i<n; i++)
  {
    spirala[i] = [];
  }

  spirala[0][0] = 0;
  spirala[0][1] = 0;

  spirala[1][0] = sx;
  spirala[1][1] = sy-1;

  spirala[2][0] = sx;
  spirala[2][1] = sy-1;

  var sign = -1;

  for(var i=3; i<n; i++)
  {
    if(i%2 == 0)
    {
      spirala[i][0] = spirala[i-1][0] + sign * ciag[i-2];
      spirala[i][1] = spirala[i-1][1];
    }
    else
    {
      sign *= -1;
      spirala[i][0] = spirala[i-1][0];
      spirala[i][1] = spirala[i-1][1] + sign * ciag[i-2];
    }
  }
  // alert("spirala = " + spirala);
  //macierz wspolrzednych od ktorych zaczynamy rysowanie kwadratow w kazdym kroku

  
  var kwadrat = [];
  for(var i=0; i<n; i++)
  {
    kwadrat[i] = [];
    kwadrat[i] = spirala[i].slice();
  }

  kwadrat[0][0] = 0;
  kwadrat[0][1] = 0;

  
  for(var i=1; i<n; i++)
  {
    switch(i%4)
    {
      case 1: //kolumny 0 --> x, 1 --> y, i to instancja kroku
        break;
      
      case 2:
        kwadrat[i][1] -= ciag[i];
        break;

      case 3:
        kwadrat[i][0] -= ciag[i];
        kwadrat[i][1] -= ciag[i];
        break;

      case 0:
        kwadrat[i][0] -= ciag[i];
        break;

      default:
        kwadrat[i][0] = 0;
        kwadrat[i][1] = 0;
        break;
    }
  }
  
  // alert("kwadrat: " + kwadrat);
  //rysowanie spirali
  ctx.strokeStyle = json.color;

  for(var i=1; i<n; i++)
  {
    ctx.beginPath();
    var start = Start(i);
    ctx.arc(spirala[i][0],spirala[i][1],ciag[i],start, Math.PI/2 + start);
    ctx.stroke();
  }

  var box = document.getElementById("pola");

  if(box.checked)
  {
    ctx.strokeStyle = "black";

    for(var i=1; i<n; i++)
    {
      ctx.beginPath();
      ctx.lineWidth = 2;
      ctx.rect(kwadrat[i][0],kwadrat[i][1], ciag[i], ciag[i]);
      ctx.stroke();
    }
    
  }


}


function tab_ciag(str)
{
    var number = parseInt(str);

    var ciag = [];
    ciag[0] = 0;
    ciag[1] = 1;

    for(var i=2; i<number; i++)
    {
        ciag[i] = ciag[i-1] + ciag[i-2];
    }

    return ciag;

}

function Start(n)
{
  var x;
  switch(n%4)
  {
    case 1:
      x=0;
      break;

    case 0:
      x=1;
      break;

    case 2:
      x=3;
      break;

    case 3:
      x=2;
      break;

    default:
      x=0;
      break;
  }

  return Math.PI/2 * x;
}

function updateTextInput(val) 
{
  document.getElementById('textInput').value=val; 
}
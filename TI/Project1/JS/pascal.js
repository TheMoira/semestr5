var xmlHttp;

var show_connection = 0;
var the_n = 0;

var coord_start = []; //wspolrzedne poczatku linii do animacj
var coord_end = [];   //wspolrzedne konca lini do animacji

var kolory = ["crimson", "cyan", "lawngreen", "magenta"]; 

var ctx;


function col_button()
{
    show_connection = show_connection == 0 ? 1 : 0;

    if(show_connection == 1)
    {
        if(the_n > 0)
        {
            var seq = tab_ciag(the_n);
            var y = coord_end[0][1];

            for(var i=0; i<the_n; i++)
            {
                kreski(ctx,coord_start[i][0],coord_start[i][1],coord_end[i][0],coord_end[i][1],kolory[i%4]);
 
                ctx.fillStyle = "white";
                ctx.font = "13px Georgia";
                if(i<the_n-1) ctx.fillText("{" + seq[i+1] + "}", 1400, y + 10);
     
                y += 40;
            }
        }
        
    }

}



function getRequestObject()      {
       if ( window.ActiveXObject)  {
            return ( new ActiveXObject("Microsoft.XMLHTTP")) ;
        } else if (window.XMLHttpRequest)  {
           return (new XMLHttpRequest())  ;
        } else {
           return (null) ;
        }
  }


function pascal()      {
       xmlHttp = getRequestObject() ;
       var size;

    if (xmlHttp)
	{ 
        try 
        {
            size = document.getElementById('rozmiar').value; 

            if(size > 15)
            {
                alert("Maksymalna wartość: 15");
            }
            else
            {
                var url = "../../../cgi-bin/Projekt1/pascal.py";
                url += "?rozmiar=" + size;
                // alert(url);
                xmlHttp.onreadystatechange = handleResponse ;
                xmlHttp.open("GET", url, true);
                xmlHttp.send(null);
            }
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
            response = xmlHttp.responseText;
            myObj = JSON.parse(response);
            rysuj(myObj);
         }
    }  
}


function rysuj(json)
{
  var ciag = tab_ciag(json.size);
  var canvas = document.getElementById("triangle");
  ctx = canvas.getContext("2d");
  ctx.clearRect(0,0,2000,1000);

  var pascal = pascal_triangle(json.size);


  var gradient = ctx.createLinearGradient(0, 0, canvas.width, 0);
  gradient.addColorStop("0"," magenta");
  gradient.addColorStop("0.5", "blue");
  gradient.addColorStop("1.0", "white");

  ctx.font = "20px Georgia";

  var x_start = canvas.width/2 - 100;
  var y_start = 50;
   
//   alert("x_start = " + x_start + " y_start = " + y_start);

  ctx.fillStyle = "white";
   
  var colors = pascal_fibo(kolory, ciag);


  var n = json.size;
  the_n = json.size+1;

    var coord_n = Math.floor(n/2) +1;
    var k = 0;

  for(var i=0; i<=n; i++)
  {
      coord_start[i] = [];
  }


  for(var i=0; i<=n; i++)
  {
      coord_end[i] = [];
  }

  var odl_od_1 = 30;    //odleglosc kolejnej liczby od jedynki po lewej w kazdym wierszu

  for(var i=0; i<json.size; i++)
  {
     var str = "";

    for(var j=0; j<pascal[i].length; j++)
    {
        str += pascal[i][j] + "   ";
    }
    ctx.textAlign = "center";
    ctx.fillText(str, x_start, y_start);
    var text_len = ctx.measureText(str).width;
    
    if(i < coord_n )
    {
        // alert(k)
        coord_start[k][0] = parseInt(x_start - text_len/2);
        coord_start[k][1] = parseInt(y_start - 10);
        k++;
    
        if(i!=0)
        {
            coord_start[k][0] = parseInt(x_start - text_len/2 + odl_od_1);
            coord_start[k][1] = parseInt(y_start - 10);
            k++;
        }

    }

    if(i==0)
    {
        coord_end[0][0] = parseInt(x_start + text_len/2 - 20);
        coord_end[0][1] = parseInt(y_start - 10);
    }
    else if(i==1)
    {
        coord_end[2][0] = parseInt(x_start + text_len/2 - 20);
        coord_end[2][1] = parseInt(y_start - 10);
    }
    else
    {
        if(i%2==0)
        {
            coord_end[i-1][0] = parseInt(x_start + text_len/2 - 20);
            coord_end[i-1][1] = parseInt(y_start);
        }
        else
        {
            coord_end[i+1][0] = parseInt(x_start + text_len/2 - 20);
            coord_end[i+1][1] = parseInt(y_start);
        }
    
    }

    y_start += 40;
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

function pascal_triangle(n)
{
    var pascal = [];

    for(var i=0; i<n; i++)
    {
        pascal[i] = [];
    }

    pascal[0][0] = 1;
    pascal[1][0] = 1;
    pascal[1][1] = 1;

    for(var i=2; i<n; i++)
    {
        for(var j=0; j<=i; j++)
        {
            if(j == 0 || j == i)
            {
                pascal[i][j] = 1;
            }
            else
            {
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
            

        }
    }

    return pascal;
}

function get_max(tab)
{
    var max = 0;
    for(var i=0; i<tab.length; i++)
    {
        if(max<tab[i])
        {
            max = tab[i];
        }
    }

    return max;
}


function pascal_fibo(kolory, ciag)
{
    var n1 = ciag.length;
    var colors = [];
    
    for(var i=0; i<n1; i++)
    {
      colors[i] = [];
    }
    
    for(var i=1; i<n1; i++)
    {
        var color = kolory[i%4];
        var n = i;
        var j = n - 1;
        
        while(j >= 0)
        {
           colors[n][j] = color;
           n--;
           j-=2;       
        }
    } 
    
    return colors;

}

function kreski(ctx, x_start, y_start, x_end, y_end, color)
{
    var t = 0;

    setInterval(function() {
        t += 0.05;     
        if(t>1)
        {
            t=1;
        }
        ctx.beginPath();
        ctx.strokeStyle = color;
        ctx.moveTo(x_start, y_start);
        ctx.lineTo(x_start + (x_end - x_start) * t, y_start + (y_end - y_start) * t);
        ctx.stroke();

    }, 30);

}

function tab_ciag(number)
{

    var ciag = [];
    ciag[0] = 0;
    ciag[1] = 1;

    for(var i=2; i<=number; i++)
    {
        ciag[i] = ciag[i-1] + ciag[i-2];
    }

    return ciag;

}


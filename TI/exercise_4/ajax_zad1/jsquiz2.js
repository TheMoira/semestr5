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

  function getBody(content) 
{ 
   var x = content.indexOf("<body");
   x = content.indexOf(">", x);    
   var y = content.lastIndexOf("</body>"); 
   return content.slice(x + 1, y);
} 

function sendChoice()      {
       xmlHttp = getRequestObject() ;
       var info;
       if (xmlHttp) {
         try {
        //    var info = document.getElementById('sel').value ;  
        // var x = document.getElementsByClassName("sel");
        for(var i=0; i<document.getElementsByClassName("sel").length; i++)
        {
            if(document.getElementsByClassName("sel")[i].checked == true)
            {
                info = document.getElementsByClassName("sel")[i].value;
            }
        }
        var url = "../cgi-bin/read2_quiz.py" ;
           url += "?sel=" + info;
          //  var data = "sel=" + encodeURIComponent(info) ;
            xmlHttp.onreadystatechange = handleResponse ;
           xmlHttp.open("GET", url, true);
          //  xmlHttp.send(data);
          xmlHttp.send(null);
         }
         catch (e) {
           alert ("Nie mozna polaczyc sie z serwerem: " + e.toString()) ;
         }
       } else {
         alert ("Blad") ;
       }
  }


function handleResponse()      {
    myDiv = document.getElementById("Season");
    // obj = { table: "seasons", limit: 20 };
    // dbParam = JSON.stringify(obj);
    if (xmlHttp.readyState == 4) {
        // alert(xmlHttp.status)
         if ( xmlHttp.status == 200 )  
         {
            // alert(xmlHttp.responseText);
            response = xmlHttp.responseText;
            myObj = JSON.parse(response);
            rysuj(myObj);
         }
    }  
    // xmlHttp.open("POST", "https://jsonplaceholder.typicode.com/posts", true);
    // xmlHttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    // xmlHttp.send("x=" + dbParam); 
}

function rysuj(tab)
{
  var canvas = document.getElementById("e");
  var ctx = canvas.getContext("2d");
  //START
  var sum = 0;
  for(var i=0; i<4; i++)
  {
      sum += tab.wyniki[i];
  }

  var inputData = [100 * tab.wyniki[0]/sum ,100 * tab.wyniki[1]/sum ,100 * tab.wyniki[2]/sum,100 * tab.wyniki[3]/sum];
  var canvasWidth = 500;

  var x_from = 60;

  var step = Math.round(canvasWidth / inputData.length);
  var names = ["Spring", "Summer", "Autumn", "Winter"];

  for (var i = 0; i < inputData.length; i++) 
  {
    var x_next = x_from + (i * step) - 20;
    var color1 = 150 + i*50;
    var color2 = 50 + i*40;
    ctx.fillStyle = "rgba(" + color2 + "," + color1 + ", 250, 1)";
    ctx.fillRect(x_next, 150, 40, -inputData[i]*2);
    ctx.fillText(names[i], x_next, 200);
  }
}

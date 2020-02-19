/* https://gist.github.com/gspencerfabian/6f50723a53c854b3eab271a239761533 */

package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
	"github.com/justinas/alice"
)

var err error

func logMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		log.Println(r.URL.Path)
		next.ServeHTTP(w, r)
	})
}

func main() {
	logger := alice.New(logMiddleware)
	http.Handle("/", logger.Then(http.HandlerFunc(indexHandler)))
	http.Handle("/ws", logger.Then(http.HandlerFunc(wsHandler)))
	http.ListenAndServe(":8080", nil)
}

func wsHandler(w http.ResponseWriter, r *http.Request) {
	conn, err := websocket.Upgrade(w, r, w.Header(), 1024, 1024)
	if err != nil {
		http.Error(w, "Could not open websocket connection", http.StatusBadRequest)
	}
	go echo(conn)
}

func echo(conn *websocket.Conn) {
	for {
		cp := getCurrencyPayload()
		if err = conn.WriteJSON(cp); err != nil {
			log.Println(err)
		}
		time.Sleep(15 * time.Second)
	}
}

func getCurrencyPayload() []interface{} {
	type CurrencyPayload []interface{}
	var cp CurrencyPayload
	var myClient = &http.Client{Timeout: 10 * time.Second}
	url := "https://api.coinmarketcap.com/v1/ticker/"
	r, err := myClient.Get(url)
	if err != nil {
		log.Println(err)
	}
	defer r.Body.Close()
	err = json.NewDecoder(r.Body).Decode(&cp)
	if err != nil {
		log.Println(err)
	}
	return cp
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, indexTemplate)
}

const indexTemplate = `
<html>
 <head>
  <title>websocket example</title>
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <style>
   .glyphicon.glyphicon-one-fine-full-dot {
    margin-bottom: -.8em;
    overflow: hidden;
   }
   .glyphicon.glyphicon-one-fine-full-dot:before {
    content:"\25cf";
   }
  </style>
 </head>
 <body>
  <div class="container"> 
   <h1>Cryptocurrency Tracker</h1>
	 <h5>Status: <span id="link_status"><span style="color:yellow;" class="glyphicon glyphicon-one-fine-full-dot"></span> Connecting...</span></h5>
   <ul id="currencies">
   </ul>
  </div>
  <script type="text/javascript">
   $(function () {
    var ws;
    if (window.WebSocket === undefined) {
     alert("Your browser does not support WebSockets.");
     return;
    } else {
     ws = initWS();
    }
    function initWS() {
     var socket = new WebSocket("ws://localhost:8080/ws"),
     clist = $("#currencies")
		 link = $("#link_status")
     socket.onopen = function() {
      console.log("Socket is open.");
			link.html("<span style='color:green;' class='glyphicon glyphicon-one-fine-full-dot'></span> Connected");
     };
     socket.onmessage = function(e) {
      console.log("Received data.");
			clist.empty();
			$.each(JSON.parse(e.data), function(key, value) {
				clist.append("<li>" + value.name + " | " + value.symbol + " | $" + value.price_usd + " | " + value.percent_change_24h + "%</li>")
			});
     }
     socket.onclose = function() {
      console.log("Socket closed.");
			link.html("<span style='color:red;' class='glyphicon glyphicon-one-fine-full-dot'></span> Disconnected")
			setTimeout(function(){initWS()}, 5000);
     }
     return socket;
    }
   });
  </script>
 </body>
</html>
`

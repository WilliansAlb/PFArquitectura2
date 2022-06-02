window.onload = () =>{
	initWebSocket();
	imprimirPrimerValor();
};

var seconds = 0;

function imprimirPrimerValor(){
	var myRequest = new Request('http://192.168.1.184/turno');
	fetch(myRequest).then(function(response) {
    return response.text().then(function(text) {
		var spl = text.split(",");
		var count = 0;
		spl.forEach(element => {
			var spl_temp = element.split("-");
			var img_temp = document.querySelectorAll(".ventilador");
			document.getElementById("t"+count).textContent = spl_temp[0];
			document.getElementById("a"+count).textContent = spl_temp[1];
			document.getElementById("m"+count).textContent = spl_temp[2];
			if (parseInt(spl_temp[1]) >= (parseInt(spl_temp[2])/2)){
				img_temp[count].style.display = "";
			} else {
				img_temp[count].style.display = "none";
			}
			count++;
		});
    });
  });
}

function cambiarValores(valor){
	var myRequest = new Request('http://192.168.1.184/turno');
	fetch(myRequest).then(function(response) {
    return response.text().then(function(text) {
		var spl = text.split(",");
		var count = 0;
		spl.forEach(element => {
			var spl_temp = element.split("-");
			var img_temp = document.querySelectorAll(".ventilador");
			document.getElementById("t"+count).textContent = spl_temp[0];
			document.getElementById("a"+count).textContent = spl_temp[1];
			document.getElementById("m"+count).textContent = spl_temp[2];
			if (parseInt(spl_temp[1]) >= (parseInt(spl_temp[2])/2)){
				img_temp[count].style.display = "";
			} else {
				img_temp[count].style.display = "none";
			}
			count++;
		});
    });
  });
}

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
function initWebSocket() {
	websocket = new WebSocket(gateway);
	websocket.onopen = onOpen;
	websocket.onclose = onClose;
	websocket.onmessage = onMessage; // <-- add this line
}

function onOpen(event) {
	console.log('Connection opened');
}
function onClose(event) {
	console.log('Connection closed');
	setTimeout(initWebSocket, 2000);
}
function onMessage(e) {
	console.log('Server: ', e.data);
	cambiarValores(e.data);
}
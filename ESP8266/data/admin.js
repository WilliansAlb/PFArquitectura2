window.onload = () =>{
	initWebSocket();
	fetch("http://192.168.1.184/cambiarArea?area=0")
		.then(data => data.text())
		.then(text => {
			actualizar(text,0);
		});
};

function cambioArea(select) {
	fetch("http://192.168.1.184/cambiarArea?area=" + select.value)
		.then(data => data.text())
		.then(text => {
			actualizar(text,select.value);
		});
}

function actualizar(text,val){
	var spl = text.split(",");
	var spl_temp = spl[val].split("-");
	document.getElementById("t0").textContent = spl_temp[0];
	document.getElementById("a0").textContent = spl_temp[1];
	document.getElementById("m0").textContent = spl_temp[2];
	if (parseInt(spl_temp[1]) >= (parseInt(spl_temp[2])/2)){
		document.getElementById("ventilador").style.display = "";
	} else {
		document.getElementById("ventilador").style.display = "none";
	}
}

function generar(){
	var value = document.getElementById("area").value;
	fetch("http://192.168.1.184/generar?area=" + value)
		.then(data => data.text())
		.then(text => {
			document.getElementById("generado").textContent = "Ultimo turno generado: "+text;
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
	actualizar(e.data,0);
}
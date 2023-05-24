const char web[] = R"rawliteral(

	<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>RS485-Scanner</title>
	<style>
		input::-webkit-outer-spin-button,
		input::-webkit-inner-spin-button {
  		-webkit-appearance: none;
  		margin: 0;
		}
		body {
			margin: 0;
			padding: 0;
			background-color: #F0EBD8;
			font-family: Arial, sans-serif;
			font-size: 14px;
		}
		.sendButton{
		background-color: #1D2D44;
		color: #fff;
		padding: 15px 20px;
		border: none;
		border-radius: 8px;
		font-size: 14px;
		box-shadow: 0px 3px 3px rgba(0, 0, 0, 0.25);
		margin-top: 100px;
		margin-left: 40%;
		margin-bottom: 20px;
		}

		.decode{
			background-color: #1D2D44;
			color: #fff;
			padding: 15px 20px;
			border: none;
			border-radius: 8px;
			font-size: 14px;
			box-shadow: 0px 3px 3px rgba(0, 0, 0, 0.25);
			max-width: 150px;
		}

		.sendButton:hover, .decode:hover{
		background-color: #435d6b;
		transform: translateY(-3px);
		}


		.sendButton:active, .decode:active {
		background-color: #004364;
		transform: translateY(1px);
		}
		.container {
			max-width: 800px;
			margin: 0 auto;
			padding: 20px;
			box-sizing: border-box;
		}
		.tabs {
			display: flex;
			flex-wrap: wrap;
			justify-content: center;
			align-items: center;
			margin-bottom: 20px;
		}
		.tab {
			padding: 10px 20px;
			background-color: #ddd;
			border-radius: 10px 10px 0 0;
			margin-right: 5px;
			cursor: pointer;
		}
		.tab.active {
			background-color: #fff;
			border-bottom: 2px solid #333;
		}

		input[type="number"] {
			width: 100%;
			background-color: #f4f4f4;
			border: none;
			border-radius: 5px;
			box-shadow: inset 0 2px 3px rgba(0,0,0,0.1);
			color: #333;
			font-size: 13px;
			padding: 10px;
			max-width: 40px;
			max-height: 10px;
			text-align: center;
		}

		.cell {
		font-size: 14px;
		text-align: center;
		color: #333;
		margin: .5px;
		padding: 2px;
		border-radius: 6px;
		background-color: #f4f4f4;
		box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
		max-width: 50px;
		max-height: 50px;
		}

		.result-cell {
		font-size: 13px;
		text-align: center;
		color: #333;
		margin: .5px;
		padding: 2px;
		border-radius: 0.5px;
		background-color: #f4f4f4;
		box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
		max-width: 100px;
		max-height: 50px;
		}

		.u-result-cell {
		font-size: 13px;
		text-align: center;
		color: #333;
		margin: .5px;
		padding: 2px;
		border-radius: 0.5px;
		background-color: #f4f4f4;
		box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
		width: 100px;
		max-height: 50px;
		}

		.tab-content {
			padding: 20px;
			background-color: #fff;
			border-radius: 0 0 10px 10px;
			box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);
			display: none;
			box-sizing: border-box;
			max-width: 800px;
		}
		.tab-content.active {
			display: block;
			
		}

		.modbus-config, .modbus-response{
			border: 2px solid rgba(0, 0, 0, 0.1);
			margin-bottom: 10px;
			padding: 10px;
		}
		.device-control{
			display: flex;
			flex-wrap: wrap;
			gap:5px;
			
		}
		.device-control > div{
			display: inherit;
			justify-content: center;
			align-items: center;
			gap:5px
		}

		.register-zone{
			display: flex;
			margin: 15px;
			gap: 10px;
			width: 100%;
		}

		select{
			background-color: #f4f4f4;
			border: none;
			border-radius: 5px;
			box-shadow: inset 0 2px 3px rgba(0,0,0,0.1);
			color: #333;
			font-size: 13px;
			padding: 10px;
		}

		.decoder-zone{
			display: flex;
			flex-direction: column;
			justify-content: space-between;
		}

		.decoder-zone > div{
			display: inherit;
			flex-direction: column;
			align-items: left;
		}

		
		.display-zone{
			display: flex;
			flex-wrap: wrap;
			gap:10px;
			width: 100%;
		}

		.registerArray{
			display: flex;
			flex-direction: column;
			row-gap: 2px;
			height: 150px;
			overflow: auto;
		}

		.registerArray::-webkit-scrollbar, .result-container::-webkit-scrollbar, .u-result-arr::-webkit-scrollbar{
  		width: 10px;
		}

		.registerArray::-webkit-scrollbar-thumb, .result-container::-webkit-scrollbar-thumb, .u-result-arr::-webkit-scrollbar-thumb{
		background-color: #999;
		border-radius: 4px;
		}

		.registerArray::-webkit-scrollbar-thumb:hover, .result-container::-webkit-scrollbar-thumb:hover, .u-result-arr::-webkit-scrollbar:hover{
		background-color: #777;
		}

		.registerArray::-webkit-scrollbar-track, .result-container::-webkit-scrollbar-track, .u-result-arr:-webkit-scrollbar-track{
		background-color: #f2f2f2;
		border-radius: 4px;
		}

		.config-zone{
			min-width: 48%;
			display: flex;
		}

		.result-zone{
			min-width: 48%;
			display: flex;
			align-items: center;
			justify-content: center;
		}

		.result-container{
			display: flex;
			flex-direction: column;
			padding: 5px;
			gap: 2px;
			height: 140px;
			overflow: auto;
			
		}

		.result-div{
			display: inherit;
			flex-direction: row;
			align-items: center;
			border-radius: 6px;
			background-color: #f4f4f4;
		}

		@media (max-width: 550px) {
			.tab {
				margin-right: 0;
				margin-bottom: 5px;
			}

			.device-control{
				display: flex;
				align-items: center;
				justify-content: center;
			}

			.sendButton{
				margin-left: 25%;
				margin-bottom: 10px;
				margin-top: 50px;
			}

			.display-zone{
				display: flex;
				align-items: center;
				justify-content: center;
			}
			.tab:last-child {
				margin-right: 5px;
			}
            input[type="number"] {
			width: 100%;
			padding: 10px;
			margin-bottom: 10px;
			text-align: center
			}

			.u-main-container{
				display: flex;
				flex-direction: column;
			}
		}

		.u-config-zone{
			min-width: 38%;
			width: 30%;
			display: flex;
			flex-direction: column;
			align-items: center;
		}

		.u-main-container{
			display: flex;
			align-items: center;
			gap:10px;
			padding: 10px;
		}

		.u-result-zone{
			min-width: 50%;
			width: 55%;
			display: flex;
			align-items: center;
			flex-direction: column;
		}

		.result-zone > div > div{
			display: flex;
			align-items: center;
			flex-direction: column;

		}

		.u-result-container{
			display: flex;
			flex-direction: column;
			gap: 3px;
			border: 2px solid rgba(240, 11, 11, 0.1);
			
		}

		.u-result-arr{
			display: flex;
			flex-direction: row;
			column-gap: 2px;
			max-width: 200px;
			width: 100%;
			overflow: auto;
			margin: 3px;
		}

	</style>
</head>
<body>
	<div class="container">
		<div class="tabs">
			<div class="tab active" onclick="showTab('tab2')">Unknown Device</div>
			<div class="tab" onclick="showTab('tab1')">Known Device</div>
			
		</div>
		<div class="tab-content" id="tab1">
			<div class="modbus-config">
				<div id="title"><h3 style="text-align: center;">Modbus Config</h3></div>
				<div class="device-control">
					<div><label for="knownID">Device ID:</label><input type="number" id="knownID" name="knownID" value="1"></div>
					<div>
						<label for="baud">BaudRate</label>
						<select id="baud">
							<option value="9600">9600</option>
							<option value="19200">19200</option>
							<option value="38400">38400</option>
							<option value="57600">57600</option>
							<option value="115200">115200</option>
						</select>
					</div>
					<div><label for="knownSA">Starting Address:</label><input type="number" id="knownSA" name="knownSA" value="0"></div>
					<div><label for="knownQu">Register Number:</label><input type="number" id="knownQu" name="knownQu" value="4"></div>
					<div><label for="knowntype">Holding - 0 / Input - 1:</label><input type="number" id="knowntype" name="knowntype" value="0"></div>
					
				</div>
				<button class="sendButton" onclick="searchRegs()" id="sendButton">Request data</button>
				<h3 id="knownStatus" style="text-align: center;"></h3>
			</div>
	
			<div class="modbus-response">
					<h3 style="text-align: center;">Modbus Response</h3>
					<div class="display-zone">
						<div class="config-zone">
							<div class="register-zone">
								
								<div class="decoder-zone">
									<div>
										<label for="type">Type of decoding</label>
										<select id="type">
											<option value="simple">Divide only by:</option>
											<option value="twoMod">Two Modbus registers</option>
											<option value="floatMod">32bit IEEE Float</option>
										</select>
									</div>
	
									<div>
										<label for="divider">Divider</label>
										<input id="divider" value="1" type="number" />
									</div>
								
									<button class="decode" onclick="compute()">Decode</button>
								</div>

								<div>
									<h5 style="margin: 0; margin-bottom: 3px; text-align: center;">Registers</h5>
									<div id="registerArray" class="registerArray">
									</div>
								</div>
							</div>
						</div>
						<div class="result-zone">
							<div>
								<div>
									<h3 style="margin: 0; margin-bottom: 3px; text-align: center;">Results</h5>
									<div id="result-container" class="result-container">
									</div>
									<button class="decode" onclick="downloadTxtFile()">Download Data</button>	
								</div>	
							</div>
						</div>
					</div>
			</div>
					
		</div>

		<div class="tab-content active" id="tab2">
			<h3 style="text-align: center;">Modbus Finder v1</h3>
			<div class="u-main-container">
				
				<div class="u-config-zone">
						<div class="container">
							<label for="unkstartAdd">Start Address: </label>
							<input type="number" value="1" id="unkstartAdd"/>
						</div>

						<div class="container">
							<label for="unkEndAdd">End Address: </label>
							<input type="number" value="5" id="unkEndAdd"/>
						</div>
					
						<p>Press start for searching devices.</p>
						<button id="searchIDs" class="decode" onclick="sendMessage()">Start search</button>
				</div>
				<div class="u-result-zone">
					<h3 style="text-align: center;"> Results:</h3>
					<div id="u-result-arr" class="u-result-arr">
						
					</div>
				</div>
			</div>
			<h3 id="unkStatus" style="text-align: center;">Status:</h3>
		</div>

	</div>
		
	<script>

		function showTab(tabName) {
			var i, tabContent, tabLinks;
			tabContent = document.getElementsByClassName("tab-content");
			for (i = 0; i < tabContent.length; i++) {
				tabContent[i].style.display = "none";
			}
			tabLinks = document.getElementsByClassName("tab");
			for (i =  0; i < tabLinks.length; i++) {
            tabLinks[i].className = tabLinks[i].className.replace(" active", "");
            }
            document.getElementById(tabName).style.display = "block";
            event.currentTarget.className += " active";
		}

		var ws;

		let webLocation = "ws://" + location.hostname + "/websocket";
      	ws = new WebSocket(webLocation);

		function sendMessage() {
			if (ws.readyState === 1) {
				let startAdd = document.getElementById("unkstartAdd").value;
				let endAdd = document.getElementById("unkEndAdd").value;
				var message = "scanID" + ";" + startAdd + ";" + endAdd;
				ws.send(message);
				document.getElementById("unkStatus").innerHTML = "Status: Searching...";
			} else {
				console.log('WebSocket is not open');
				document.getElementById("unkStatus").innerHTML = "Status: WebSocket is not open";
			}
      	}

		function downloadTxtFile() {
  			var resultDiv = document.getElementById("result-container");
			var resultDivs = resultDiv.querySelectorAll(".result-div");

			var data = []; 
			for (var i = 0; i < resultDivs.length; i++) {

				var indexContainer = resultDivs[i].querySelector(".index-container");
				var indexPtags = indexContainer.querySelectorAll("p");
				var valueContainer = resultDivs[i].querySelector(".value-container");
				var valuePtag = valueContainer.querySelector("p");

				var indexArray = [];

				for (var j = 0; j < indexPtags.length; j++) {
					var indexText = indexPtags[j].textContent;
					indexArray.push(indexText);
				}
				
				var valueText = valuePtag.textContent;
				
				var resultObj = {
    			"bits": indexArray,
   				"value": valueText
  				};

				data.push(resultObj);
			}

			var jsonString = JSON.stringify(data);
			console.log(jsonString);

			
			var filename = "myFile.txt";
			var element = document.createElement('a');
			element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(jsonString));
			element.setAttribute('download', filename);
			element.style.display = 'none';
			document.body.appendChild(element);
			element.click();
			document.body.removeChild(element);
		}

		function searchRegs(){
			if (ws.readyState === 1) {
			let id = document.getElementById("knownID").value;
			let bd = document.getElementById("baud").value;
			let sa = document.getElementById("knownSA").value;
			let qu = document.getElementById("knownQu").value;
			let opt =  document.getElementById("knowntype").value
			
			var message = "scanRegs" + ";" + id + ";"  + bd + ";"  + sa + ";"  + qu + ";" + opt;
			ws.send(message);
			//document.getElementById("unkStatus").innerHTML = "Status: Searching...";
			} else {
				console.log('WebSocket is not open');
				//document.getElementById("unkStatus").innerHTML = "Status: WebSocket is not open";
			}
		}

		ws.onmessage = function(event) {
			let rs = JSON.parse(event.data);

			console.log(rs);
			
			if(rs[0].iden == "ids"){
					console.log("IDs now");
					let parentDiv = document.getElementById("u-result-arr");
					parentDiv.innerHTML = '';

					let length = Object.keys(rs).length;

					if(rs[1].err == 0){
						let devices = rs[2]
						for(let dev in devices){
							console.log(devices);

							let values = devices[dev].split(";"); // Split the string into an array using ';' as the separator
  							let value1 = parseInt(values[0]); // Parse the first value as an integer
  							let value2 = parseInt(values[1]); // Parse the second value as an integer

							// Create a new div element
							let newDiv = document.createElement('div');

							newDiv.classList.add('u-result-container');

							// Create two new p elements
							let firstP = document.createElement('p');
							let secondP = document.createElement('p');

							firstP.classList.add('u-result-cell');
							secondP.classList.add('u-result-cell');

							// Set the text content of the p elements
							firstP.textContent = "id->" + value1;
							secondP.textContent = "baud->"+ value2;

							// Append the p elements to the new div
							newDiv.appendChild(firstP);
							newDiv.appendChild(secondP);

							// Append the new div to the parent div
							parentDiv.appendChild(newDiv);
						}
						document.getElementById("unkStatus").innerHTML = "Status: Finished";
					}
					else{
						document.getElementById("unkStatus").innerHTML = "Code:" + rs[1].err + ", No device found";
					}	
				}

			else if(rs[0].iden == "regs"){

				let parentDiv = document.getElementById("registerArray");
				parentDiv.innerHTML = '';

				console.log(rs[2]);

				if(rs[1].err == 0){

					let values = rs[2];

					for (var key in values){

						// Create two new p elements
							let firstP = document.createElement('p');

							firstP.classList.add('cell');

							var value = values[key];

							// Set the text content of the p elements
							firstP.textContent = value;

							//console.log(key + ": " + value);							
							// Append the new div to the parent div
							parentDiv.appendChild(firstP);
					}
					document.getElementById("knownStatus").innerHTML = "Succes.";
				}

				else{
					if(rs[1].err == -1){
						document.getElementById("knownStatus").innerHTML = "Code:" + rs[1].err + ", Wrong Config";
					}
					if(rs[1].err == -2){
						document.getElementById("knownStatus").innerHTML = "Code:" + rs[1].err + ", Max Reg Nr 20";
					}
					
				}	
					
			}
        };

		function compute(){
			let type = document.getElementById('type').value;
			switch(type){
				case "simple": simpleCalc(); break;
				case "twoMod": twoMod(); break;
				case "floatMod": floatMod(); break;
			}
		}

		function twoMod(){

			let source = document.getElementsByClassName("registerArray");

			let values = document.getElementsByClassName("cell");
			let valArr = new Array();
			let mainDiv = document.getElementById("result-container");
			let divider = document.getElementById("divider").value;

			let startInD = parseInt(document.getElementById("knownSA").value);

			mainDiv.innerHTML = '';

			for(let i=0; i < values.length; i+=2){

				const parentDiv = document.createElement("div");
				parentDiv.classList.add("result-div");

				const firstP = document.createElement("p");
				const secondP = document.createElement("p");

				firstP.classList.add("result-cell");
				secondP.classList.add("result-cell");

				let msb = parseInt(values[i].innerHTML);
				let lsb = parseInt(values[i+1].innerHTML)

				firstP.innerHTML = startInD +":MSB: " + msb;
				secondP.innerHTML = (startInD + 1) + ":LSB: " + lsb;
				startInD+=2;

				let indexElem = document.createElement("div");

				indexElem.classList.add("index-container");

				let valDiv = document.createElement("div");

				valDiv.classList.add("value-container");

				let valElem = document.createElement("p");

				valElem.classList.add("result-cell");

				valElem.innerHTML = "->" + ((lsb + (msb << 8)) / divider);

				indexElem.appendChild(firstP);
				indexElem.appendChild(secondP);

				valDiv.appendChild(valElem);

				parentDiv.appendChild(indexElem);
				parentDiv.appendChild(valDiv);

				mainDiv.appendChild(parentDiv);

			}

		}

		function simpleCalc(){
			let source = document.getElementsByClassName("registerArray");

			let divider = document.getElementById("divider").value;

			let values = document.getElementsByClassName("cell");
			let valArr = new Array();
			let parentDiv = document.getElementById("result-container");

			parentDiv.innerHTML = '';

			for(let i=0; i < values.length; i++){

				const firstP = document.createElement("p");
				firstP.classList.add("value");
				firstP.innerHTML = values[i].innerHTML / divider;


				//firstP.textContent = values[i].innerHTML / divider;	
				valArr[i] = values[i].innerHTML / divider;			

				parentDiv.appendChild(firstP);

			}

			console.log(valArr);
		}

function floatMod(){

			let source = document.getElementsByClassName("registerArray");

			let values = document.getElementsByClassName("cell");
			let valArr = new Array();
			let mainDiv = document.getElementById("result-container");
			let divider = document.getElementById("divider").value;

			mainDiv.innerHTML = '';

			for(let i=0; i < values.length; i+=2){

				const parentDiv = document.createElement("div");
				parentDiv.classList.add("result-div");

				const firstP = document.createElement("p");
				const secondP = document.createElement("p");

				firstP.classList.add("result-cell");
				secondP.classList.add("result-cell");

				let msb = parseInt(values[i].innerHTML);
				let lsb = parseInt(values[i+1].innerHTML)

				firstP.innerHTML = startInD +":MSB: " + msb;
				secondP.innerHTML = (startInD + 1) + ":LSB: " + lsb;

				let indexElem = document.createElement("div");

				indexElem.classList.add("index-container");

				let valDiv = document.createElement("div");

				valDiv.classList.add("value-container");

				let valElem = document.createElement("p");

				valElem.classList.add("result-cell");

				const binary = (msb << 16) | lsb;

				const sign = (binary >> 31) & 0x1;
  				const exponent = (binary >> 23) & 0xff;
  				const mantissa = binary & 0x7fffff;

  				// Calculate the actual value using the IEEE 754 formula
  				const value = (1 - 2 * sign) * (1 + mantissa / Math.pow(2, 23)) * Math.pow(2, exponent - 127);

				valElem.innerHTML = "->" + value.toFixed(2);

				indexElem.appendChild(firstP);
				indexElem.appendChild(secondP);

				valDiv.appendChild(valElem);

				parentDiv.appendChild(indexElem);
				parentDiv.appendChild(valDiv);

				mainDiv.appendChild(parentDiv);

			}
}

</script>

)rawliteral";

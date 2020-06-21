let rawFile = new XMLHttpRequest();
let stop = false;


function func(){
	if (stop == false) {
		try{
			rawFile.open("GET", "http://test.ru/test.txt?v1");
			rawFile.send();
		}
		catch(e){

		}
	}	
}


setInterval(func , 100);

rawFile.onreadystatechange = function() {
	let resText = rawFile.responseText;
	let bots = [];
	
	if (rawFile.readyState == 4) {
		bots = resText.split(/\r\n|\n|\r/).filter(function(el) {return el.length != 0});
		let container = document.getElementById('botContainer');
		for (let i = 0; i < bots.length; i++) {
			bots[i] = bots[i].split(',');
		}
		let childrenLength = container.children.length;
		for(let i=0; i < childrenLength; i++){
			container.removeChild(container.children[0]);
		}
		for (let i = 0; i < bots.length; i++) {
			let temp = document.createElement('div');
			container.appendChild(temp);
			temp.classList.add('bot');
			temp.style.top = bots[i][1]*12-10+"px";
			temp.style.left = bots[i][0]*12-10+"px";
			switch(bots[i][9]*1){
				case 0: temp.style.background = "red"; break;
				case 1: temp.style.background = "brown"; break;
				case 2: temp.style.background = "blue"; break;
				case 3: temp.style.background = "green"; break;
			}
		}
		
		
	}
}
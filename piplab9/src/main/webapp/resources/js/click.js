function addPoint(event) {
                    var x = event.offsetX;
                    var y = event.offsetY;
                    var select = document.getElementById("mainForm:sm");
                    var r = select.options[select.selectedIndex].value;
                    var Xcoord = (x - 108) * r / 78;
                    var Ycoord = (112 - y) * r / 78;
                    if(Ycoord >= 3 || Ycoord <= -3) {
                        alert('Y must be in (-3; 3)');
                        return;
                    }
                    document.getElementById("mainForm:x").value = Xcoord;
                    document.getElementById("mainForm:y").value = Ycoord;
                    var audio = new Audio();
                    audio.src = 'resources/taa.ogg';
                    audio.autoplay = true;

                    var Pic = new Array();
                    Pic[0]="resources/pictures/anim/00000.png";
                    Pic[1]="resources/pictures/anim/00001.png";
                    Pic[2]="resources/pictures/anim/00002.png";
                    Pic[3]="resources/pictures/anim/00003.png";
                    Pic[4]="resources/pictures/anim/00004.png";
                    Pic[5]="resources/pictures/anim/00005.png";
                    Pic[6]="resources/pictures/anim/00006.png";
                    Pic[7]="resources/pictures/anim/00007.png";
                    Pic[8]="resources/pictures/anim/00008.png";
                    Pic[9]="resources/pictures/anim/00009.png";
                    Pic[10]="resources/pictures/anim/00010.png";
                    Pic[11]="resources/pictures/anim/00011.png";
                    Pic[12]="resources/pictures/anim/00012.png";
                    Pic[13]="resources/pictures/anim/00013.png";
                    Pic[14]="resources/pictures/anim/00014.png";
                    Pic[15]="resources/pictures/anim/00015.png";
                    Pic[16]="resources/pictures/anim/00016.png";
                    Pic[17]="resources/pictures/anim/00017.png";
                    Pic[18]="resources/pictures/anim/00018.png";
                    Pic[19]="resources/pictures/anim/00019.png";
                    Pic[20]="resources/pictures/anim/00020.png";
                    Pic[21]="resources/pictures/anim/00021.png";
                    Pic[22]="resources/pictures/anim/00022.png";
                    Pic[23]="resources/pictures/anim/00023.png";
                    Pic[24]="resources/pictures/anim/00024.png";
                    Pic[25]="resources/pictures/anim/00025.png";
                    Pic[26]="resources/pictures/anim/00026.png";
                    Pic[27]="resources/pictures/anim/00027.png";
                    Pic[28]="resources/pictures/anim/00028.png";
                    Pic[29]="resources/pictures/anim/00029.png";
                    Pic[30]="resources/pictures/anim/00030.png";
                    Pic[31]="resources/pictures/anim/00031.png";

                    document.getElementById("anim").style.left = event.clientX-50 + 'px';
                    document.getElementById("anim").style.top = event.clientY-10 + 'px';
                    var i = 0;
                    var timer = setInterval(function (){
                        document.getElementById("anim").src = Pic[i];
                        i++;
                        if(i > 31) {
                            clearInterval(timer);
                            document.getElementById("anim").src = Pic[0];
                            document.getElementById("anim").style.left = 0 + 'px';
                            document.getElementById("anim").style.top =  0 + 'px';
                            document.getElementById("mainForm:submit").click();
                        }
                    }, 30);
}

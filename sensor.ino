import processing.serial.*; // mengimpor perpustakaan untuk komunikasi serial
import java.awt.event.KeyEvent; // mengimpor perpustakaan untuk membaca data dari port serial
import java.io.IOException;

Serial myPort; // mendefinisikan Object Serial
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;

void setup() {

size (1920, 1080);
smooth();
myPort = new Serial(this,"COM6", 9600); // memulai komunikasi serial
myPort.bufferUntil('.'); // membaca data dari port serial hingga karakter '.'.sudut, jarak.
orcFont = loadFont("OCRAExtended-30.vlw");
}

void draw() {

fill(98,245,31);
textFont(orcFont);
// mensimulasikan gerakan kabur dan memudar lambat dari garis yang bergerak
noStroke();
fill(0,4);
rect(0, 0, width, 1010);

fill(98,245,31); // warna hijau
// memanggil fungsi untuk menggambar radar
drawRadar();
drawLine();
drawObject();
drawText();
}

void serialEvent (Serial myPort) { // mulai membaca data dari Port Serial
// membaca data dari Port Serial hingga karakter '.' dan memasukkannya ke dalam variabel String "data".
data = myPort.readStringUntil('.');
data = data.substring(0,data.length()-1);

index1 = data.indexOf(","); // temukan karakter ',' dan masukkan ke dalam variabel "index1"
angle= data.substring(0, index1); // baca data dari posisi "0" ke posisi variabel index1 distance= data.substring(index1+1, data.length()); // baca data dari posisi "index1" hingga akhir data, itulah nilai jaraknya
// mengubah variabel String menjadi Integer
iAngle = int(angle);
iDistance = int(distance);
}

void drawRadar() {
pushMatrix();
translate(960,1000); // memindahkan koordinat awal ke lokasi baru
noFill();
strokeWeight(2);
stroke(98,245,31);
// menggambar garis lengkung
arc(0,0,1800,1800,PI,TWO_PI);
arc(0,0,1400,1400,PI,TWO_PI);
arc(0,0,1000,1000,PI,TWO_PI);
arc(0,0,600,600,PI,TWO_PI);
// menggambar garis sudut
line(-960,0,960,0);
line(0,0,-960cos(radians(30)),-960sin(radians(30)));
line(0,0,-960cos(radians(60)),-960sin(radians(60)));
line(0,0,-960cos(radians(90)),-960sin(radians(90)));
line(0,0,-960cos(radians(120)),-960sin(radians(120)));
line(0,0,-960cos(radians(150)),-960sin(radians(150)));
line(-960*cos(radians(30)),0,960,0);
popMatrix();
}

void drawObject() {
pushMatrix();
translate(960,1000); // memindahkan koordinat awal ke lokasi baru
strokeWeight(9);
stroke(255,10,10); // warna merah
pixsDistance = iDistance*22.5; // mengubah jarak dari sensor cm ke piksel
// membatasi jarak hingga 40 cm
if(iDistance<40 o:p="">

line(pixsDistancecos(radians(iAngle)),-pixsDistancesin(radians(iAngle)),950cos(radians(iAngle)),-950sin(radians(iAngle)));
}
popMatrix();
}

void drawLine() {
pushMatrix();
strokeWeight(9);
stroke(30,250,60);
translate(960,1000); // memindahkan koordinat awal ke lokasi baru
line(0,0,950cos(radians(iAngle)),-950sin(radians(iAngle))); // menggambar garis sesuai dengan sudutnya
popMatrix();
}

void drawText() { // menggambar teks di layar

pushMatrix();
if(iDistance>40) {
noObject = "Out of Range";
}
else {
noObject = "In Range";
}
fill(0,0,0);
noStroke();
rect(0, 1010, width, 1080);
fill(98,245,31);
textSize(25);
text("10cm",1180,990);
text("20cm",1380,990);
text("30cm",1580,990);
text("40cm",1780,990);
textSize(40);
text("Object: " + noObject, 240, 1050);
text("Angle: " + iAngle +" °", 1050, 1050);
text("Distance: ", 1380, 1050);
if(iDistance<40 o:p="">
text(" " + iDistance +" cm", 1400, 1050);
}
textSize(25);
fill(98,245,60);
translate(961+960cos(radians(30)),982-960sin(radians(30)));
rotate(-radians(-60));
text("30°",0,0);
resetMatrix();
translate(954+960cos(radians(60)),984-960sin(radians(60)));
rotate(-radians(-30));
text("60°",0,0);
resetMatrix();
translate(945+960cos(radians(90)),990-960sin(radians(90)));
rotate(radians(0));
text("90°",0,0);
resetMatrix();
translate(935+960cos(radians(120)),1003-960sin(radians(120)));
rotate(radians(-30));
text("120°",0,0);
resetMatrix();
translate(940+960cos(radians(150)),1018-960sin(radians(150)));
rotate(radians(-60));
text("150°",0,0);
popMatrix();
}

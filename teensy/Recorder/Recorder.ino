#include <Time.h>
//#include <TimeLib.h>
#include <TimeAlarms.h>

// Record sound as raw data to a SD card, and play it back.
//
// Requires the audio shield:
//   http://www.pjrc.com/store/teensy3_audio.html
//
// Three pushbuttons need to be connected:
//   Record Button: pin 0 to GND
//   Stop Button:   pin 1 to GND
//   Play Button:   pin 2 to GND
//
// This example code is in the public domain.

#include <Arduino.h>
#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TimeLib.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=105,63
AudioAnalyzePeak         peak1;          //xy=278,108
AudioRecordQueue         queue1;         //xy=281,63
AudioPlaySdRaw           playRaw1;       //xy=302,157
AudioOutputI2S           i2s1;           //xy=470,120
AudioConnection          patchCord1(i2s2, 0, queue1, 0);
AudioConnection          patchCord2(i2s2, 0, peak1, 0);
AudioConnection          patchCord3(playRaw1, 0, i2s1, 0);
AudioConnection          patchCord4(playRaw1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=265,212
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_MIC;
bool ended = false;
// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// The file where data is recorded
File frec;


void setup() {

    
  setTime(17,26,0,20,9,17); // set time to 5:26:00pm September 20th 2017
  
  timeStatus();
  while(1){
    char filename[12];
    
    getfilename(filename);
    Serial.println();

    Serial.print(filename);
    delay(1000);
  }
  // create the alarms 
  Alarm.alarmRepeat(6,45,0, MorningAlarm);  // 6:45am every day
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  
  AudioMemory(60);
  Serial.begin(9600);
  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);

  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here if no SD card, but print a message
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
//  } else {
//    delay(1000);
  }
  printDirectory(frec, 0); //this runs once at beginning to list all files and directories on SD card.

  startRecording();
}

#define TIME_HEADER "T"
int loopNumber = 0;

//global to store recording state  - initialize variable off - false indicates teensy shouldn't be recording
bool recordFlag = true; 

//initialize recording status on 
int recordingStatus = 1; 

//initilize track counting variable (this should be about 12 tracks per day)
int trackcount = 0;

void loop() {

  Alarm.delay(0); // needed for alarm function to check alarms

//  Serial.println(now());
//  unsigned long myTime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600;

//  if (Serial.find(TIME_HEADER)) {
//    myTime = Serial.parseInt();
//    Serial.println(myTime);
//  }


  if (!frec) {
   return;
  }
  
  int time = millis();
  int length = 10 * 1000; //specifies the time of recording - 1 hr.

if (recordFlag) {
  if (time % length == 0) {
    trackcount++;
    stopRecording();
    loopNumber++;
    startRecording();
  } else {
    continueRecording();
  }

} else if (recordingStatus == 1){ // this should end any recordings that were stopped in the middle of alarm cleanly and also prevent recordings from happening when teensy is initialized in the daytime
  stopRecording();
  }



  
//  if (time < 10000) {
//    continueRecording();
//  } else if (ended == false) {
//    ended = true;
//    stopRecording();
//  }
}

void getfilename(char *fname) { //points to global filename array
  //returns an unsigned int - format YYMMDDHH.RAW 
   Serial.print("getfilename");
   int h = hour();
      Serial.print(" h =");

   Serial.print(h);
   int y = year() % 100;
         Serial.print(" y =");

   Serial.print(y);

   int d = day();
//   if (d < 10){
//    d = 
//   }
         Serial.print(" d =");

      Serial.print(d);

   int m = month();
         Serial.print(" m =");

   Serial.print(m);
      fname[0] = (y / 10) + '0' ; //single quotes adding to a char , gives a  number between 0 - 9
      fname[1] = (y % 10) + '0'; //
      fname[2] = (m / 10) + '0' ; //single quotes adding to a char , gives a  number between 0 - 9
      fname[3] = (m % 10) + '0'; //
      fname[4] = (d / 10) + '0' ; //single quotes adding to a char , gives a  number between 0 - 9
      fname[5] = (d % 10) + '0'; //
      fname[6] = (h / 10) + '0' ; //single quotes adding to a char , gives a  number between 0 - 9
      fname[7] = (h % 10) + '0'; //
      fname[8] = '.';
      fname[9] = 'R';
      fname[10] = 'A';
      fname[11] = 'W';
      fname[12] = 0; //null terminator
      Serial.print("   ");
   Serial.print(fname);
   Serial.println();

}

void startRecording() {
  Serial.println('a');
  //need to change filename to be based on date - it cannot exceed 8 characters plus extension, it should take the format HH/DD/MM/YY
  //I think my approach will be to call a filename function that assembles a new file name and returns it as a string.
  //char myfilename[12];
  //snprintf(myfilename, 13, "%s.RAW", String(loopNumber).c_str());
  char filename[9];
  //snprintf(getfilename(), 8, "%s.RAW", getfilename());
  Serial.println(filename);

//  if (SD.exists(filename)) {
//    // The SD library writes new data to the end of the
//    // file, so to start a new recording, the old file
//    // must be deleted before new data is written.
//    SD.remove(filename);
//  }
//  int num = random();
//  int num = Teensy3Clock.get();
//  int num = now();
//  Serial.println(String(num) + ".RAW");
//  Serial.println(month());
//  randomSeed(analogRead(13));
//  Serial.println(year());
//  const char *truncated = String(random()).substring(0, 8).c_str();
  Serial.println(filename);
  frec = SD.open(filename, FILE_WRITE);
  
  Serial.println(frec);
  if (frec) {
    queue1.begin();
//    TODO: log file name, begin/end time
  } else {
    Serial.println("File creation failed :(");
  }
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    // Fetch 2 blocks from the audio library and copy
    // into a 512 byte buffer.  The Arduino SD library
    // is most efficient when full 512 byte sector size
    // writes are used.
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
//    elapsedMicros usec = 0;
    frec.write(buffer, 512);
    // Uncomment these lines to see how long SD writes
    // are taking.  A pair of audio blocks arrives every
    // 5802 microseconds, so hopefully most of the writes
    // take well under 5802 us.  Some will take more, as
    // the SD library also must write to the FAT tables
    // and the SD card controller manages media erase and
    // wear leveling.  The queue1 object can buffer
    // approximately 301700 us of audio, to allow time
    // for occasional high SD card latency, as long as
    // the average write time is under 5802 us.
//    Serial.print("SD write, us=");
//    Serial.println(usec);
  }
}

void stopRecording() {
//  Serial.println(String(random()) + ".RAW");
  queue1.end();
//  if (mode == 1) {
    while (queue1.available() > 0) {
      frec.write((byte*)queue1.readBuffer(), 256);
      queue1.freeBuffer();
    }
    frec.close();
    Serial.println("End recording");
    recordingStatus = 0;
//  }
//  mode = 0;
}

void adjustMicLevel() {
  // TODO: read the peak1 object and adjust sgtl5000_1.micGain()
  // if anyone gets this working, please submit a github pull request :-)
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}


// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn recording off");
  recordFlag = false; //this turns off the recording
  Serial.println("Alarm: - sleep Teensy");    
}
void EveningAlarm(){
  Serial.println("Alarm: - turn recording on");
  recordFlag = true; //this turns on the recording
  Serial.println("Alarm: - wake Teensy");             
}




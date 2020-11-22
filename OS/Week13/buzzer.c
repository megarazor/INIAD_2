int swc_player1= 12;
int led_player1= 8;
int swc_player2= 11;
int led_player2= 7;
int swc_player3= 10;
int led_player3= 6;
int swc_player4= 9;
int led_player4= 5;
int swc_reset= 4;

void setup() {
  pinMode(swc_player1, INPUT);
  pinMode(led_player1, OUTPUT);
  pinMode(swc_reset, INPUT);
  
}

void loop() {
  int player1= digitalRead(swc_player1);
  if(player1 == LOW) {
    digitalWrite(led_player1, HIGH);
  	int reset= digitalRead(swc_reset);
    while(reset == HIGH){
      delay(10);
      reset= digitalRead(swc_reset);
    }
    digitalWrite(led_player1, LOW);
  }
  int player2= digitalRead(swc_player2);
  if(player2 == LOW) {
    digitalWrite(led_player2, HIGH);
  	int reset= digitalRead(swc_reset);
    while(reset == HIGH){
      delay(10);
      reset= digitalRead(swc_reset);
    }
    digitalWrite(led_player2, LOW);
  }
  int player3= digitalRead(swc_player3);
  if(player3 == LOW) {
    digitalWrite(led_player3, HIGH);
  	int reset= digitalRead(swc_reset);
    while(reset == HIGH){
      delay(10);
      reset= digitalRead(swc_reset);
    }
    digitalWrite(led_player3, LOW);
  }
  int player4= digitalRead(swc_player4);
  if(player4 == LOW) {
    digitalWrite(led_player4, HIGH);
  	int reset= digitalRead(swc_reset);
    while(reset == HIGH){
      delay(10);
      reset= digitalRead(swc_reset);
    }
    digitalWrite(led_player4, LOW);
  }

  delay(10);
}
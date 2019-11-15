const int levelCap = 100; //how many times the game can be played in a row
int pattern[levelCap];
int userInput[levelCap];
int start = 1; //indicates how many LEDs would flash on the first level

int lightLength = 500; //indicates how long the LEDs flash for on each level starts at 500 milliseconds 

void setup() {
  pinMode(A0, INPUT);  //sets these pins to indicate a button press
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, OUTPUT);  //lights up the LEDs with each corresponding button push
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop()
{
  if (start == 1)  //starts the game 
    randomPattern();  //generates random pattern

  if (digitalRead(A4) == LOW || start != 1)  
  {
    startRound();   
    userChoice();     
  }
}

void startRound()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  for (int i = 0; i < start; i++)
  {
    digitalWrite(pattern[i], HIGH);
    delay(lightLength);
    digitalWrite(pattern[i], LOW);
    delay(200);
  }
}

void userChoice()  //function would determine if the user had pressed the correct button for the LED that lit up
{
int indicator = 0; 

  for (int i = 0; i < start; i++)  //loop that checks if the user pressed the correct sequence of buttons
  {
    indicator = 0;
    while(indicator == 0)
    {
    if (digitalRead(A0) == LOW)
    {
      digitalWrite(5, HIGH);
      userInput[i] = 5;
      indicator = 1;
      delay(200);
    if (userInput[i] != pattern[i])  
    {
      lose();
      return;
    }
    digitalWrite(5, LOW);
    }

    if (digitalRead(A1) == LOW)
    {
      digitalWrite(4, HIGH);
      userInput[i] = 4;
      indicator = 1;
      delay(200);
    if (userInput[i] != pattern[i])
    {
      lose();
      return;
    }
    digitalWrite(4, LOW);
    }

    if (digitalRead(A2) == LOW)
    {
      digitalWrite(3, HIGH);
      userInput[i] = 3;
      indicator = 1;
      delay(200);
    if (userInput[i] != pattern[i])
    {
      lose();
      return;
    }
    digitalWrite(3, LOW);
    }

    if (digitalRead(A3) == LOW)
    {
       digitalWrite(2, HIGH);
       userInput[i] = 2;
       indicator = 1;
       delay(200);
    if (userInput[i] != pattern[i])
    {
      lose();
      return;
    }
    digitalWrite(2, LOW);
    }

    }
  } 
  win();  //if the user pressed the correct sequence then the win function is called
}

void randomPattern()  
{
  randomSeed(millis()); //generates a random pattern for the LEDs

  for (int i = 0; i < levelCap; i++)  //for loop to generate the random pattern for each level
  {
    pattern[i] = random(2,6);  //random pattern for LEDs 2-5
  }
}
void lose()  // function that flashes the LEDs for 70 milliseconds 10 times to indicate a wrong pattern
{
  for (int i = 0; i < 10; i++) //for loop to make the LEDs flash on an off 10 times
   {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(70);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(70);
  }
  start = 1;
  lightLength = 1000;
}

void win()  //Function that holds the leds steady for 700 milliseconds to indicate a correct pattern
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(700);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(700);

  if (start < levelCap);  //increases the amount of LEDS that would flash in a given level by 1
    start++;

  lightLength -= 50; //makes the LEDs flash faster with each increasing level
}

class Timer
{
  private:
    unsigned long lastTime;  // the latest time had doing Func( )
    void (*Func) (void);
    void (*backupFunc) (void);  // backup Func for start( )
    unsigned long T_int;   // interval in ms, can be set as in us (optional)

  public:
    Timer(void (*userFunc)(), unsigned long T, int isTinUs=0)
    {
      Func = backupFunc = userFunc;  // save the function pointer
      T_int = T * 1000;
      if(isTinUs !=0) T_int = T;   // T is in micro second as per unit
      lastTime = 0;  // initialization should be in constructor
      lastTime = -T_int; // compatible with Original version
    }

    void check()
    {
      if( Func == 0 ) return;  // no function pointer
      unsigned long _micros = micros( ); // Local variable could be in Register
      //  Note that ( _micros = micros() < Time)  means  ( _micros = ( micros()  < Time ) )
      // BTW, check roll over is actually NOT NECESSARY; by tsaiwn@cs.nctu.edu.tw
      if (_micros - lastTime >= T_int)
      {
        lastTime = _micros;  // latest time doing Func( )
        Func();
      }
    }// check(
    void start( ) {  // first run of doing Func( )
      if(Func == 0) Func = backupFunc;  // restore after .stop( )
      lastTime = micros( );  // latest time doing Func( )
      Func();   // First run
    } // start(
    void stop( ) {  // stop the scheduled Func  (userFunc)
      Func = 0;  // set as NULL
    } // stop(
};

Timer T1(Blink1, 88000, 38); // 88000us (NOT ms) since 38 is NOT 0
Timer T2(Blink2, 1000);  // 1000ms
Timer T3(Blink3, 2000); // 2000ms

void setup() 
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  T1.start( )    ; // optional to use the .start( ) function
  delay(2568); // On Purpose for you  to compare T1 vs. T2, T3
}

void loop() 
{
  // put your main code here, to() run repeatedly:
  T1.check();
  T2.check();
  T3.check();
}

void Blink1()
{

}

void Blink2()
{
  digitalWrite(9, !digitalRead(9));
}

void Blink3()
{
  digitalWrite(11, !digitalRead(11));
}

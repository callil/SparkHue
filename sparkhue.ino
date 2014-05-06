TCPClient client;
byte server[] = { 192, 168, 1, 10 }; // Local light server
int potPin = A0;  // Potentiometer Pin
int val = 0;  
int prev = 0;
String stringOne; // empty string to store val length
unsigned int len; // length of val

void setup()
{
    Serial.begin(9600);
    delay(1000);
    client.connect(server, 80);
    if (client.connected()){ //initiate connection
        Serial.println("connected");
    }
    else{
        Serial.println("failed");
    }
}

void loop(){
    if (client.connect(server, 80)) {
        if(client.connected())
        {
            val = analogRead(potPin); //read potentiometer
            val = map(val, 2, 4093, 0, 255); //map it
            String stringOne =  String(val);  //convert to string
            unsigned int len = stringOne.length(); //get length
            if (val != prev ){ // if new reading is different than the old one
                client.println("PUT /api/newdeveloper/lights/3/state HTTP/1.1");
                client.println("Connection: keep-alive"); //
                client.println("Host: 192.168.1.10"); //same as server
                client.println("Content-Type: text/plain;charset=UTF-8"); //
                client.print("Content-Length: "); //param
                client.println(11+len); //brightness string + val length
                client.println();  // blank line before body
                client.print("{\"bri\": ");
                client.print(val); //value of potentiometer
                client.println("}");
                Serial.println("sent");  // command executed
                delay(100); // slight delay
                prev = val; //set prev
            }
        }
        client.stop();
        Serial.println("stopping");
     }
    delay(10);
}
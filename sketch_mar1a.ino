
//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";
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Afif Ayman";
const char* password = "jashim1980";
String apiKey = "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";
String prompt = "Hello, how are you?";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Enable WiFi debug output
  WiFi.printDiag(Serial);

  int attemptCount = 0;
  while (WiFi.status() != WL_CONNECTED && attemptCount < 10) {
    delay(1000);
    Serial.print(".");
    attemptCount++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi.");
    Serial.print("WiFi status code: ");
    Serial.println(WiFi.status());
    return;
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Send a request to OpenAI
    HTTPClient http;
    http.begin("https://api.openai.com/v1/chat/completions");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + apiKey);

    // Create the JSON payload with the "model" parameter
     String payload = "{\"model\":\"gpt-3.5-turbo-instruct\",\"prompt\":\"" + prompt + "\",\"max_tokens\":50}";





    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);

      // Parse the JSON response to extract the chat answer
      // You'll need to use a JSON library for this, such as ArduinoJSON
      // Here's a basic example without error handling
      String chatAnswer;
      chatAnswer = response.substring(response.indexOf("\"choices\"") + 14);
      chatAnswer = chatAnswer.substring(0, chatAnswer.indexOf("\""));
      
      Serial.println("Chat Answer: " + chatAnswer);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();

    // Wait before sending another request
    delay(5000); // Wait for 5 seconds before sending another request
  }
}

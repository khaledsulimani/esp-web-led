// محتويات ملف index.h
const char webpage[] PROGMEM = R"rawliteral(
  <html>
    <body>
      <h1>Control LED</h1>
      <p>LED is %LED_STATE%</p>
      <p><a href="/led1/on">Turn ON</a></p>
      <p><a href="/led1/off">Turn OFF</a></p>
    </body>
  </html>
)rawliteral";
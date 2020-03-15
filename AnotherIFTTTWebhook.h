// The MIT License
// 
// Copyright (c) 2015 Neil Webber
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// ====================================================================
// ====================================================================
// An adapted version of IFTTT Trigger by Neil Webber
// Original: https://gist.github.com/outofmbufs/d6ced37b49a484c495f0
// 
// Adaptation from: https://www.siytek.com
//
// How to use:
// 1. Place AnotherIFTTTWebhook.h in the same directory as your project
// 2. Add #include "AnotherIFTTTWebhook.h" to your main project file
// 3. Send webhook using function in main file:
//    send_webhook(EVENT, KEY, Value1, Value2, Value3);
// ====================================================================
// ====================================================================

WiFiClient client;

char *append_str(char *here, char *s) {
    while (*here++ = *s++)
  ;
    return here-1;
}

char *append_ul(char *here, unsigned long u) {
    char buf[20];       // we "just know" this is big enough

    return append_str(here, ultoa(u, buf, 10));
}

void send_webhook(char *MakerIFTTT_Event, char *MakerIFTTT_Key, char *value1, char *value2, char *value3) {

    // connect to the Maker event server
    client.connect("maker.ifttt.com", 80);

    // construct the POST request
    char post_rqst[256];    // hand-calculated to be big enough

    char *p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");

    // we need to remember where the content length will go, which is:
    char *content_length_here = p;

    // it's always two digits, so reserve space for them (the NN)
    p = append_str(p, "NN\r\n");

    // end of headers
    p = append_str(p, "\r\n");

    // construct the JSON; remember where we started so we will know len
    char *json_start = p;

    // As described - this example reports a pin, uptime, and "hello world"
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, value1);
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, value2);
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, value3);
    p = append_str(p, "\"}");

    // go back and fill in the JSON length
    // we just know this is at most 2 digits (and need to fill in both)
    int i = strlen(json_start);
    content_length_here[0] = '0' + (i/10);
    content_length_here[1] = '0' + (i%10);

    // finally we are ready to send the POST to the server!
    client.print(post_rqst);
    client.stop();
    
}

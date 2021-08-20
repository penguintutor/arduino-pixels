/* file with the web handling functions */

void showWebPage(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println(index_html);
}


void showCSS(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/css");
  client.println();
  client.println(pixels_css);
}



void showStatus(WiFiClient client, String status_msg) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/css");
  client.println();
  client.println(status_msg);
}



void showJS(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/javascript");
  client.println();
  client.println(pixels_js);
}

void showJSON(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:application/javascript");
  client.println();
  client.println("[");
  for (int i=0; i < (sizeof(sequences)/sizeof(sequence)); i++){
    if (i > 0) client.println(",");
    
    client.println("  {");
    client.print("   \"seq_name\": \"");
    client.print(sequences[i].seq_name);
    client.println("\",");

    client.print("   \"title\": \"");
    client.print(sequences[i].title);
    client.println("\",");

    client.print("   \"description\": \"");
    client.print(sequences[i].description);
    client.println("\"");
    client.print("  }");

  }
  client.println("]");
}

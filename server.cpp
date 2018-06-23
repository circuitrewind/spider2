////////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

#include "server.h"
#include "lua.h"




////////////////////////////////////////////////////////////////////////////////
// MAIN WEB SERVER OBJECT LISTENING ON TCP PORT 80
////////////////////////////////////////////////////////////////////////////////
ESP8266WebServer _server(80);




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
String getContentType(String filename) {
	if (_server.hasArg(F("download")))	return F("application/octet-stream");
	if (filename.endsWith(F(".txt")))	return F("text/plain");
	if (filename.endsWith(F(".lua")))	return F("text/plain");
	if (filename.endsWith(F(".htm")))	return F("text/html");
	if (filename.endsWith(F(".html")))	return F("text/html");
	if (filename.endsWith(F(".css")))	return F("text/css");
	if (filename.endsWith(F(".xml")))	return F("text/xml");
	if (filename.endsWith(F(".js")))	return F("application/javascript");
	if (filename.endsWith(F(".json")))	return F("application/json");
	if (filename.endsWith(F(".png")))	return F("image/png");
	if (filename.endsWith(F(".gif")))	return F("image/gif");
	if (filename.endsWith(F(".jpg")))	return F("image/jpeg");
	if (filename.endsWith(F(".jpeg")))	return F("image/jpeg");
	if (filename.endsWith(F(".ico")))	return F("image/x-icon");
	if (filename.endsWith(F(".svg")))	return F("image/svg+xml");
	if (filename.endsWith(F(".pdf")))	return F("application/x-pdf");
	if (filename.endsWith(F(".zip")))	return F("application/x-zip");
	if (filename.endsWith(F(".gz")))	return F("application/x-gzip");
	if (filename.endsWith(F(".woff2")))	return F("font/woff2");
	if (filename.endsWith(F(".c")))		return F("text/plain");
	if (filename.endsWith(F(".cpp")))	return F("text/plain");
	if (filename.endsWith(F(".h")))		return F("text/plain");
	if (filename.endsWith(F(".hpp")))	return F("text/plain");
	if (filename.endsWith(F(".log")))	return F("text/plain");

	return F("application/octet-stream");
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
bool handleFileRead(String path) {
	if (path.endsWith("/")) path += F("index.html");

	String contentType	= getContentType(path);
	String pathWithGz	= path + F(".gz");

	if (SPIFFS.exists(pathWithGz)  ||  likely(SPIFFS.exists(path))) {
		if (SPIFFS.exists(pathWithGz)) path += F(".gz");
		File file	= SPIFFS.open(path, "r");
		size_t sent	= _server.streamFile(file, contentType);
		file.close();
		return true;
	}

	return false;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
void server_setup() {




	////////////////////////////////////////////////////////////////////////////
	// ROOT DIRECTORY, SHOW STATUS INFORMATION
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/"), [](){
		_server.client().setNoDelay(true);

		char buf[100] = "";
		snprintf(buf, sizeof(buf), FS("ESP %d, uptime %d\n"), ESP.getChipId(), millis() / 1000);
		_server.send(200, F("text/plain"), buf);
	});




	////////////////////////////////////////////////////////////////////////////
	// EVALUATE A SCRIPT
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/eval"), HTTP_POST, []() {
		_server.client().setNoDelay(true);

		String code = _server.arg(F("code"));

		if (likely(!spider_eval(code.c_str()))) {
			_server.send(200, F("text/plain"), F("OK"));
		} else {
			Serial.println(spider_error);
			_server.send(500, F("text/plain"), spider_error);
		}
	});




	////////////////////////////////////////////////////////////////////////////
	// EXECUTE THE GIVEN LUA SCRIPT BY SPIFFS FILENAME
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/script"), HTTP_POST, []() {
		_server.client().setNoDelay(true);

		String code = _server.arg(F("code"));

		//RESET LUA INSTANCE
		if (unlikely(lua_setup())) {
			Serial.println(spider_error);
			_server.send(500, F("text/plain"), spider_error);
			return;
		}

		if (unlikely(spider_eval(code.c_str()))) {
			Serial.println(spider_error);
			_server.send(500, F("text/plain"), spider_error);
			return;
		}

		_server.send(200, F("text/plain"), F("OK"));
	});




	////////////////////////////////////////////////////////////////////////////
	// RESET MICROCONTROLLER
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/reset"), []() {
		ESP.reset();
	});




	////////////////////////////////////////////////////////////////////////////
	// RESTART MICROCONTROLLER
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/restart"), []() {
		ESP.restart();
	});




	////////////////////////////////////////////////////////////////////////////
	// SAVE A FILE TO THE SPIFFS
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/save"), HTTP_POST, []() {
		_server.client().setNoDelay(true);

		String code	= _server.arg(F("code"));
		String name	= _server.arg(F("name"));

		if (name.charAt(0) != '/') {
			name	= "/" + name;
		}

		if (unlikely(name == "/")) {
			String error = F("Invalid file name: ");
			Serial.println(error + name);
			_server.send(500, F("text/plain"), error + name);
			return;
		}

		String msg	= F("Attempting to save: ");
		Serial.println(msg + name);

		File file	= SPIFFS.open(name, "w");
		file.print(code);
		file.close();

		_server.send(200, F("text/plain"), F("OK"));
	});




	////////////////////////////////////////////////////////////////////////////
	// EXECUTE THE GIVEN LUA SCRIPT BY SPIFFS FILENAME
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/run"), HTTP_POST, []() {
		_server.client().setNoDelay(true);

		String name	= _server.arg(F("name"));

		if (name.charAt(0) != '/') {
			name	= "/" + name;
		}

		//CANNOT EXECUTE ROOT PATH OR EMPTY PATH
		if (unlikely(name == "/")) {
			String error = F("Invalid file name: ");
			Serial.println(error + name);
			_server.send(500, F("text/plain"), error + name);
			return;
		}

		//RESET LUA INSTANCE
		if (unlikely(lua_setup())) {
			Serial.println(spider_error);
			_server.send(500, F("text/plain"), spider_error);
			return;
		}

		//EXECUTE THE FILE
		if (unlikely(lua_file(name.c_str()))) {
			Serial.println(spider_error);
			_server.send(500, F("text/plain"), spider_error);
			return;
		}

		//WE GOOD, LET CLIENT KNOW!
		_server.send(200, F("text/plain"), F("OK"));
	});




	////////////////////////////////////////////////////////////////////////////
	// PING / PONG
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/ping"), []() {
		_server.client().setNoDelay(true);
		_server.send(200, F("text/plain"), F("pong"));
	});




	////////////////////////////////////////////////////////////////////////////
	// DIRECTORY LISTING OF ALL FILES IN SPIFFS
	////////////////////////////////////////////////////////////////////////////
	_server.on(F("/dir"), []() {
		_server.client().setNoDelay(true);

		DynamicJsonBuffer json(JSON_ARRAY_SIZE(100));
		JsonObject&	root	= json.createObject();
		JsonArray&	files	= root.createNestedArray(F("files"));

		Dir dir = SPIFFS.openDir("");
		while (dir.next()) {
			files.add( dir.fileName() );
		}

		String text;
		root.printTo(text);
		_server.send(200, F("application/json"), text);
	});




	////////////////////////////////////////////////////////////////////////////
	// SEND A FILE FROM FILE SYSTEM IF AVAILABLE, IF NOT THEN ERROR 404
	////////////////////////////////////////////////////////////////////////////
	_server.onNotFound([](){
		_server.client().setNoDelay(true);

		if (unlikely(!handleFileRead(_server.uri()))) {
			_server.send(404, F("text/plain"), F("File Not Found"));
		}
	});




	////////////////////////////////////////////////////////////////////////////
	// START THE WEB SERVER
	////////////////////////////////////////////////////////////////////////////
	_server.begin();

}

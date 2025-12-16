#include "../../src/readhtml/readhtml.h" //引入读取HTML文件的头文件


const char* ssid = "液晶光阀实验";
const char* password = "12345678";

const byte DNS_PORT = 53; //DNS端口

IPAddress apIP(192, 168, 4, 1);    //ap的IP地址

DNSServer dnsServer;

ESP8266WebServer server(80); 

void handleRoot() {
    server.send_P(200, "text/html; charset=UTF-8", index_html);
}

void setupAP(){
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //设置softAP

    dnsServer.start(DNS_PORT, "*", apIP); //启动DNS服务器

    server.onNotFound([]() {
        server.send_P(200, "text/html; charset=UTF-8", index_html);  // 希望能够将所有的路由定向到我们所提供的网页
    });

    server.begin();    //启动Web服务器


}

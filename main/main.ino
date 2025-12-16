#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h> 
#include <FS.h>
#include "TFT_eSPI.h"
#include "src/softAP/softAP.h" //softAP.h没有引用上面的头文件，这里只是把它当作代码片段拼接

/*
代码实现的逻辑主要是：readhtml.h中定义了html网页，其中使用js脚本重定向到/trigger/xxx路径，同时通过num传递参数，
同时主函数中有相应函数 handleDanfengTrigger()来通知主函数执行相应函数，用serve.on()相应路径。softAP.h的作用是
设置ESP8266作为WIFI AP，并通过DNS重定向，使得访问WIFI时自动跳转网页，用来操作液晶光阀
TFT_WIDTH与TFT——HEIGHT定义于User_Setup中，通过替换此文件可兼容不同屏幕
*/

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH,TFT_HEIGHT); 

bool triggerDanfeng = false;
bool triggerShuangfeng = false;
bool triggerYuanKong =false;
int shuangfengNum = 0; 
int yuankongNum = 0; //初始化变量

//响应单缝衍射
void handleDanfengTrigger() {
    triggerDanfeng = true; //设置为true使得主函数可以执行danfeng函数()
    server.send(200, "text/plain", "OK");
}

//相应双缝衍射
void handleShuangfengTrigger() {
    if (server.hasArg("num")) {
        int num = server.arg("num").toInt(); //读取传递的参数
        if (num >= 0 && num <= TFT_WIDTH - 2) {
            shuangfengNum = num;
            triggerShuangfeng = true;
            server.send(200, "text/plain", "OK");
        } else {
            server.send(400, "text/plain", "参数无效！");
        }
    } else {
        server.send(400, "text/plain", "缺少参数！"); 
    }
}

//响应圆形孔衍射
void handleYuanKongTrigger() {
    if (server.hasArg("num")) {
        int num = server.arg("num").toInt();
        if (num >= 0 && num <= (TFT_WIDTH - 2)/2) {
            yuankongNum = num;  
            triggerYuanKong = true;
            server.send(200, "text/plain", "OK");
        } else {
            server.send(400, "text/plain", "参数无效！");
        }
    } else {
        server.send(400, "text/plain", "缺少参数！");
    }
}


//具体执行在屏幕上显示单缝双缝以及圆形孔衍射的函数

void danfeng(){
  tft.fillScreen(TFT_BLACK);
  tft.drawLine(TFT_WIDTH/2 , 0, TFT_WIDTH/2, TFT_HEIGHT, TFT_WHITE);
}

void shuangfeng(int pixel){
  tft.fillScreen(TFT_BLACK);
  tft.drawLine(TFT_WIDTH/2-pixel/2,0,TFT_WIDTH/2-pixel/2,TFT_HEIGHT-1, TFT_WHITE);
  tft.drawLine(TFT_WIDTH/2+pixel/2,0,TFT_WIDTH/2+pixel/2,TFT_HEIGHT-1, TFT_WHITE);
}

void yuankong(int pixel){
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(TFT_WIDTH/2, TFT_HEIGHT/2, pixel, TFT_WHITE);
}

void setup() {
    Serial.begin(115200);  //初始化串口通信（用以检测单片机状态）

    tft.begin(); //初始化屏幕
    tft.fillScreen(TFT_BLACK); //初始化屏幕为全黑（对应TFT屏幕液晶不旋光，其实不重要只要取互补色即可保证只有一种“颜色”所旋转的光可以通过偏振片）

    //这是在setupAP.h中定义的函数，用于初始化网络。
    setupAP();

    //串口通信用以确定状态
    Serial.println("");
    Serial.print("WiFi名称: ");
    Serial.println(ssid);
    Serial.print("WiFi密码: ");
    Serial.println(password);
    Serial.print("接入点IP地址: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("系统已启动，等待设备连接...");

    //设定不同路径的处理函数（与前端交互）
    server.on("/", handleRoot);
    server.on("/trigger/danfeng", handleDanfengTrigger); 
    server.on("/trigger/shuangfeng", handleShuangfengTrigger); 
    server.on("/trigger/yuankong", handleYuanKongTrigger);
}

void loop() {
    dnsServer.processNextRequest(); //处理DNS请求
    server.handleClient(); //处理前端连接

    //主循环中判定是否需要执行
    if (triggerDanfeng) {
        danfeng();
        triggerDanfeng = false; //防止重复执行
    }

    if (triggerShuangfeng){
        shuangfeng(shuangfengNum);
        triggerShuangfeng = false; 
    }

    if (triggerYuanKong) {
        yuankong(yuankongNum);
        triggerYuanKong =false;
    }
}


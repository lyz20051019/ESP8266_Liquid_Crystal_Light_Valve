const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
    <!-- 设置字体为UTF-8 -->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="Cache-Control" content="no-cache">
    <title>液晶光阀实验</title>
    <!-- 在html中嵌入CSS样式（因为Arduino不方便在单片机中读取文件） -->
    <style>

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: "Inter", "Microsoft YaHei", sans-serif;
            text-align: center;
        }

        .diffraction-container {
            width: 100%;
            max-width: 600px;
            margin: 50px auto;
            padding: 30px;
            background-color: #ffffff;
            border-radius: 16px;
            box-shadow: 0 8px 24px rgba(0, 0, 0, 0.08);
        }

        .diffraction-btn {
            display: inline-flex;
            align-items: center;
            justify-content: center;
            height: 48px;
            padding: 0 24px;
            margin: 0 8px 16px 0;
            background: linear-gradient(135deg, #4361ee 0%, #3a0ca3 100%);
            color: #ffffff;
            border: none;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 500;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 4px 12px rgba(67, 97, 238, 0.3);
        }

        .diffraction-btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 16px rgba(67, 97, 238, 0.4);
            background: linear-gradient(135deg, #3a56d4 0%, #320b91 100%);
        }

        .diffraction-btn:active {
            transform: translateY(0);
            box-shadow: 0 2px 8px rgba(67, 97, 238, 0.3);
        }

        .input-num {
            height: 48px;
            width: 180px;
            padding: 0 16px;
            margin: 0 8px 16px 0;
            border: 2px solid #e2e8f0;
            border-radius: 12px;
            font-size: 16px;
            color: #1a202c;
            transition: all 0.3s ease;
            outline: none;
        }

        .input-num:focus {
            border-color: #4361ee;
            box-shadow: 0 0 0 4px rgba(67, 97, 238, 0.1);
        }

        .input-num::placeholder {
            color: #a0aec0;
            font-size: 14px;
        }

        .input-num:hover {
            border-color: #cbd5e1;
        }

        .footer { 
            text-align: center; 
            padding: 20px 0; 
            color: #666; 
            font-size: 14px; 
        }

        .footer a { 
            color: #666; 
            text-decoration: none; 
        }

        .footer a:hover { 
            text-decoration: underline; 
        }

    </style>

</head>

<body>
    <br><br><br>
    <h1 class="diffraction-title">液晶光阀实验</h1> <br>

    <!-- 定义操控板块 -->
    <button class="diffraction-btn" onclick="triggerDanfengFunc()">单缝衍射</button><br>
    <input type="number" class="input-num" id="numInput" placeholder="输入间隔的像素数(不要超过屏幕尺寸)"><br>
    <button class="diffraction-btn" onclick="triggerShuangfengFunc()">双缝衍射</button><br>
    <input type="number" class="input-num" id="numInput2" placeholder="输入圆的半径(不要超过屏幕尺寸)"><br>
    <button class="diffraction-btn" onclick="triggerYuanKongFunc()">圆形孔衍射</button><br>


    <!--
    使用javascript沟通html与ino主程序
    通过定向至trigger路径来使得主函数相应
    -->
    <script>
        function triggerDanfengFunc() {
            let xhr = new XMLHttpRequest();
            xhr.open("POST", "/trigger/danfeng", true);
            xhr.send();
        }

        function triggerShuangfengFunc() {
            let num = document.getElementById("numInput").value;
            let xhr = new XMLHttpRequest();
            xhr.open("POST", "/trigger/shuangfeng", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.send("num=" + num); // 传递数字参数
        }

        function triggerYuanKongFunc() {
            let num = document.getElementById("numInput2").value;
            xhr.open("POST", "/trigger/yuankong", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.send("num=" + num);
        }
    </script>
    <footer class="footer">
        <p>© <script>document.write(new Date().getFullYear())</script> 作者： lyz tjl zyb zyr </p>
        <p><a href="https://www.zju.edu.cn/" target="_blank">浙江大学</a></p>
    </footer>
</body>
)rawliteral";
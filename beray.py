from flask import Flask, render_template_string

app = Flask(__name__)

HTML_SAYFASI = """
<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>X-Holding | Terminal Access</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Fira+Code:wght@400;700&family=Great+Vibes&display=swap');
        body { background-color: #0a0a0a; color: #00ff41; font-family: 'Fira Code', monospace; height: 100vh; overflow: hidden; }
        .terminal-cursor { animation: blink 1s infinite; }
        @keyframes blink { 0%, 100% { opacity: 1; } 50% { opacity: 0; } }
        .hidden { display: none; }
        .romantic-text { font-family: 'Great Vibes', cursive; color: #ff79c6; }
        .scanline { width: 100%; height: 100px; z-index: 10; background: linear-gradient(0deg, rgba(0, 0, 0, 0) 0%, rgba(0, 255, 65, 0.1) 50%, rgba(0, 0, 0, 0) 100%); opacity: 0.1; position: absolute; bottom: 100%; animation: scanline 6s linear infinite; }
        @keyframes scanline { 0% { bottom: 100%; } 100% { bottom: -100%; } }
    </style>
</head>
<body class="flex items-center justify-center relative">
    <div class="scanline"></div>

    <div id="login-screen" class="w-full max-w-md p-8 border border-[#00ff41] bg-black shadow-[0_0_20px_rgba(0,255,65,0.2)]">
        <div class="mb-4 text-xs opacity-50 uppercase tracking-widest">Secure Terminal v2.04</div>
        <div class="mb-6">
            <span class="text-white">></span> AUTH_REQUIRED: <span class="text-yellow-400">INPUT_ACCESS_KEY</span>
        </div>
        <input type="text" id="access-key" class="w-full bg-transparent border-b border-[#00ff41] outline-none mb-6 text-xl text-center" autocomplete="off" autofocus>
        <button onclick="startInfiltration()" class="w-full border border-[#00ff41] py-2 hover:bg-[#00ff41] hover:text-black transition-all font-bold">EXECUTE</button>
    </div>

    <div id="loading-screen" class="hidden w-full max-w-2xl p-6 text-sm">
        <div id="console-output" class="leading-loose"></div>
    </div>

    <div id="final-card" class="hidden w-full max-w-lg p-10 bg-[#1a1a1a] border-2 border-[#ff79c6] rounded-3xl text-center shadow-[0_0_50px_rgba(255,121,198,0.3)] transform transition-all">
        <h1 class="romantic-text text-6xl mb-6 text-white">İyi ki Doğdun Beray! ✨</h1>
        <div class="text-gray-300 leading-relaxed text-lg mb-8 italic">
            "Senin kalbinin güzelliğini doğrulayacak bir kod henüz yazılmadı... Mesafeler ne kadar uzak olursa olsun, sen benim bu hayattaki en değerli varlığımsın."
        </div>
        <div class="w-full h-px bg-gradient-to-r from-transparent via-[#ff79c6] to-transparent mb-6"></div>
        <p class="text-[#ff79c6] font-bold text-xl uppercase tracking-widest">Happy Birthday</p>
        <p class="text-xs text-gray-500 mt-4">Authorized by: Çağhan</p>
    </div>

    <script>
        const logs = [
            "> Initializing protocol 1923...",
            "> Bypassing regional firewalls...",
            "> Accessing Ayvacık/Çanakkale relay nodes...",
            "> Searching for 'The Most Special Person' database...",
            "> Match found: BERAY",
            "> Decrypting heart-encryption.dll...",
            "> Security bypass 100% complete.",
            "> Loading emotional data packages...",
            "> SYSTEM_READY: Granting full access..."
        ];

        function startInfiltration() {
            const key = document.getElementById('access-key').value;
            if(key !== "1923") {
                alert("ACCESS DENIED!");
                return;
            }

            document.getElementById('login-screen').classList.add('hidden');
            document.getElementById('loading-screen').classList.remove('hidden');
            
            let i = 0;
            const consoleBox = document.getElementById('console-output');

            const interval = setInterval(() => {
                if (i < logs.length) {
                    const line = document.createElement('p');
                    line.innerHTML = logs[i];
                    consoleBox.appendChild(line);
                    i++;
                } else {
                    clearInterval(interval);
                    setTimeout(() => {
                        document.getElementById('loading-screen').style.opacity = '0';
                        setTimeout(() => {
                            document.getElementById('loading-screen').classList.add('hidden');
                            document.getElementById('final-card').classList.remove('hidden');
                        }, 500);
                    }, 1000);
                }
            }, 600);
        }
    </script>
</body>
</html>
"""

@app.route('/')
def home():
    return render_template_string(HTML_SAYFASI)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
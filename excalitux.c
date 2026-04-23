#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- RENK PALETİ (Cyberpunk 2077 Temalı) ---
#define COLOR_BG      (Color){ 10, 10, 15, 255 }
#define COLOR_SIDEBAR (Color){ 18, 18, 25, 255 }
#define COLOR_ACCENT  (Color){ 0, 255, 255, 255 } // Neon Cyan
#define COLOR_HOT     (Color){ 255, 0, 85, 255 }  // Neon Pink/Red

// --- SİSTEM FONKSİYONLARI ---

void SetGpuMode(int mode) {
    if (mode == 0) system("pkexec prime-select intel &");
    else if (mode == 1) system("pkexec prime-select nvidia &");
    else system("pkexec prime-select on-demand &");
}

void SetPerformance(int mode) {
    if (mode == 0) system("powerprofilesctl set power-saver");
    else if (mode == 1) system("powerprofilesctl set balanced");
    else system("powerprofilesctl set performance");
}

void SetKbdRGB(Color col) {
    char cmd[128];
    sprintf(cmd, "openrgb --device 0 --mode static --color %02x%02x%02x &", col.r, col.g, col.b);
    system(cmd);
}

float ReadTemp() {
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!f) return 0.0f;
    int t; fscanf(f, "%d", &t); fclose(f);
    return t / 1000.0f;
}

// --- UI YARDIMCILARI ---

bool DrawCustomButton(Rectangle rect, const char* text, Color baseColor, Vector2 mouse) {
    bool hover = CheckCollisionPointRec(mouse, rect);
    DrawRectangleRec(rect, hover ? ColorAlpha(baseColor, 0.3f) : COLOR_SIDEBAR);
    DrawRectangleLinesEx(rect, 2, hover ? WHITE : baseColor);
    DrawText(text, rect.x + (rect.width/2 - MeasureText(text, 18)/2), rect.y + 15, 18, hover ? WHITE : baseColor);
    return (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "ExcaliTux Suite v1.0 - Pure C Edition");
    SetTargetFPS(60);

    int currentTab = 0; // 0: Dash, 1: GPU, 2: RGB
    float temp = 0;
    Color kbdPreview = COLOR_ACCENT;

    while (!WindowShouldClose()) {
        temp = ReadTemp();
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
            ClearBackground(COLOR_BG);

            // --- SIDEBAR ---
            DrawRectangle(0, 0, 220, screenHeight, COLOR_SIDEBAR);
            DrawRectangle(218, 0, 2, screenHeight, COLOR_ACCENT); // Neon Border
            DrawText("EXCALITUX", 40, 40, 26, WHITE);
            DrawText("G870 LINUX", 40, 70, 14, COLOR_ACCENT);

            if (DrawCustomButton((Rectangle){20, 150, 180, 50}, "DASHBOARD", COLOR_ACCENT, mouse)) currentTab = 0;
            if (DrawCustomButton((Rectangle){20, 210, 180, 50}, "GPU MODU", COLOR_ACCENT, mouse)) currentTab = 1;
            if (DrawCustomButton((Rectangle){20, 270, 180, 50}, "RGB KONTROL", COLOR_ACCENT, mouse)) currentTab = 2;

            // --- ANA İÇERİK ---
            
            // TAB 0: DASHBOARD
            if (currentTab == 0) {
                DrawText("SİSTEM DURUMU", 260, 40, 22, WHITE);
                
                // Sıcaklık Göstergesi (Gauge)
                DrawCircleLines(400, 220, 90, DARKGRAY);
                DrawCircleSectorLines((Vector2){400, 220}, 85, 0, (temp * 3), 36, (temp > 70 ? COLOR_HOT : COLOR_ACCENT));
                DrawText(TextFormat("%.1f°C", temp), 365, 210, 32, WHITE);
                DrawText("CPU SICAKLIĞI", 355, 260, 14, GRAY);

                // Performans Modu Seçimi
                DrawText("PERFORMANS PROFİLİ", 260, 360, 18, COLOR_ACCENT);
                if (DrawCustomButton((Rectangle){260, 400, 180, 50}, "OFİS", GREEN, mouse)) SetPerformance(0);
                if (DrawCustomButton((Rectangle){460, 400, 180, 50}, "OYUN", COLOR_ACCENT, mouse)) SetPerformance(1);
                if (DrawCustomButton((Rectangle){660, 400, 180, 50}, "TURBO", COLOR_HOT, mouse)) SetPerformance(2);
            }

            // TAB 1: GPU MODU
            if (currentTab == 1) {
                DrawText("GPU GEÇİŞ MERKEZİ", 260, 40, 22, WHITE);
                DrawRectangleLines(260, 100, 600, 300, COLOR_SIDEBAR);
                
                DrawText("Aktif Modu Seçin (Oturum Kapatma Gerektirebilir)", 280, 120, 14, GRAY);
                
                if (DrawCustomButton((Rectangle){350, 180, 400, 50}, "INTEL (Dahili - Tasarruf)", SKYBLUE, mouse)) SetGpuMode(0);
                if (DrawCustomButton((Rectangle){350, 250, 400, 50}, "NVIDIA (Harici - Performans)", COLOR_HOT, mouse)) SetGpuMode(1);
                if (DrawCustomButton((Rectangle){350, 320, 400, 50}, "HYBRID (On-Demand)", LIME, mouse)) SetGpuMode(2);
            }

            // TAB 2: RGB KONTROL
            if (currentTab == 2) {
                DrawText("KLAVYE LED YÖNETİMİ", 260, 40, 22, WHITE);
                
                Color p[] = {RED, GREEN, BLUE, MAGENTA, GOLD, PINK, LIME, SKYBLUE};
                for(int i=0; i<8; i++) {
                    Rectangle r = {260 + (i*75), 120, 60, 60};
                    DrawRectangleRec(r, p[i]);
                    if(CheckCollisionPointRec(mouse, r) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        kbdPreview = p[i];
                        SetKbdRGB(p[i]);
                    }
                }
                
                // Klavye Önizleme Şeması
                DrawRectangleLines(260, 220, 600, 200, kbdPreview);
                DrawRectangle(270, 230, 580, 180, ColorAlpha(kbdPreview, 0.2f));
                DrawText("KLAVYE IŞIKLANDIRMASI AKTİF", 420, 310, 16, WHITE);
            }

            // Alt Bilgi Çubuğu
            DrawRectangle(220, 510, screenWidth-220, 40, COLOR_SIDEBAR);
            DrawText("ExcaliTux G870 Engine | Hardware Status: Optimized", 240, 525, 12, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
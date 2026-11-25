/*
 * ============================================================
 *  MERGED CG PROJECT - AIUB
 *  Pages: Cover (0), Instructions (1), Scenes (2-6)
 *  Scene 2 = Afia Jarin Binte Jarjish  (coastal)
 *  Scene 3 = MD. Sayeed Alam           (historical Dhaka)
 *  Scene 4 = Abrar Adnan Pranjal       (train station)
 *  Scene 5 = Rafid Hossain             (modern city)
 *  Scene 6 = Rahul Sarker              (futuristic / plane crash)
 *
 *  Navigation:
 *    PAGE 0 (Cover)        -> Press ENTER or SPACE to go to Page 1
 *    PAGE 1 (Instructions) -> Press 1-5 for scenes, F for full merge
 *    Any scene             -> Press ESC to return to Instructions
 *    ESC on Instructions   -> Back to Cover
 *  ============================================================
 */

#ifdef _WIN32
  #include <windows.h>
  #include <mmsystem.h>
  #pragma comment(lib,"winmm.lib")
#endif

#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// ─────────────────────────────────────────────
//  Global scene selector
//  0 = Cover  1 = Instructions  2-6 = scenes
// ─────────────────────────────────────────────
static int g_scene = 0;   // start at cover

// Window size (shared)
static int g_winW = 1100, g_winH = 650;

// ─────────────────────────────────────────────────────────────────────────────
//  FULL MERGE ADDITION – global variables for automatic cycling
// ─────────────────────────────────────────────────────────────────────────────
static int g_fullMergeActive = 0;   // 0=off, 1=on
static int g_mergeIdx = 0;          // 0..4 for scenes 2..6
static void fullMergeSwitch(int value); // forward declaration

// ─────────────────────────────────────────────────────────────────────────────
//  COMMON MATH
// ─────────────────────────────────────────────────────────────────────────────
#ifndef PI
#define PI 3.14159265358979323846f
#endif

// ═══════════════════════════════════════════════════════════════════════════════
//  PAGE 0 – COVER  (from Page1.cpp)
// ═══════════════════════════════════════════════════════════════════════════════
namespace Cover {
    bool showInstructions = false;

    void drawText(float x, float y, const char* str,
                  void* font = GLUT_BITMAP_HELVETICA_12) {
        glRasterPos2f(x, y);
        for (int i = 0; str[i]; i++) glutBitmapCharacter(font, str[i]);
    }
    void drawTextCentered(float cx, float y, const char* str, void* font) {
        int len = strlen(str);
        float charW = 0.007f;
        if (font == GLUT_BITMAP_HELVETICA_18)      charW = 0.011f;
        else if (font == GLUT_BITMAP_TIMES_ROMAN_24) charW = 0.014f;
        float startX = cx - (len * charW * 0.5f);
        drawText(startX, y, str, font);
    }
    void fillRect(float x1,float y1,float x2,float y2){
        glBegin(GL_QUADS);
        glVertex2f(x1,y1); glVertex2f(x2,y1);
        glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }
    void drawRect(float x1,float y1,float x2,float y2){
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1); glVertex2f(x2,y1);
        glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }

    void render() {
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.3f,0.3f,0.4f);
        drawRect(-0.96f,-0.96f,0.96f,0.96f);

        glColor3f(0.0f,0.0f,0.2f);
        fillRect(-0.90f,0.80f,0.90f,0.94f);
        glColor3f(1,1,1);
        drawTextCentered(0,0.86f,"AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH (AIUB)",
                         GLUT_BITMAP_HELVETICA_18);

        glColor3f(0,0,0);
        drawTextCentered(0,0.70f,"COMPUTER GRAPHICS",GLUT_BITMAP_TIMES_ROMAN_24);
        drawTextCentered(0,0.64f,"Project",GLUT_BITMAP_HELVETICA_18);

        drawTextCentered(0,0.55f,"Submitted By",GLUT_BITMAP_HELVETICA_18);
        glColor3f(0.5f,0.5f,0.7f);
        glBegin(GL_LINES);
        glVertex2f(-0.30f,0.535f); glVertex2f(0.30f,0.535f);
        glEnd();

        float tY=0.49f;
        glColor3f(0.1f,0.1f,0.3f);
        fillRect(-0.62f,tY,0.62f,tY+0.045f);
        glColor3f(1,1,1);
        drawText(-0.58f,tY+0.016f,"Name",GLUT_BITMAP_HELVETICA_12);
        drawText( 0.18f,tY+0.016f,"Student ID",GLUT_BITMAP_HELVETICA_12);

        struct { const char* name; const char* id; } students[]={
            {"Abrar Adnan Pranjal",     "23-53229-3"},
            {"Rafid Hossain",           "23-52980-3"},
            {"Afia Jarin Binte Jarjish","23-50315-1"},
            {"MD. Sayeed Alam",         "23-52980-3"},
            {"Rahul Sarker",            "23-51556-2"},
        };
        int n=5; float rowH=0.075f;
        for(int i=0;i<n;i++){
            float ry=tY-(i+1)*rowH;
            if(i%2==0){ glColor3f(0.94f,0.94f,0.97f); fillRect(-0.62f,ry,0.62f,ry+rowH*0.96f); }
            glColor3f(0,0,0);
            drawText(-0.58f,ry+0.02f,students[i].name,GLUT_BITMAP_HELVETICA_12);
            drawText( 0.18f,ry+0.02f,students[i].id,  GLUT_BITMAP_HELVETICA_12);
        }
        glColor3f(0.3f,0.3f,0.5f);
        drawRect(-0.62f,tY-n*rowH,0.62f,tY+0.045f);
        glBegin(GL_LINES);
        glVertex2f(0.14f,tY-n*rowH); glVertex2f(0.14f,tY+0.045f);
        glEnd();

        float stY=tY-n*rowH-0.08f;
        glColor3f(0,0,0);
        drawTextCentered(0,stY,"Submitted To",GLUT_BITMAP_HELVETICA_18);
        drawTextCentered(0,stY-0.05f,"Mahfujur Rahman",GLUT_BITMAP_HELVETICA_12);
        drawTextCentered(0,stY-0.09f,"Assistant Professor, Computer Science",GLUT_BITMAP_HELVETICA_12);
        drawTextCentered(0,stY-0.13f,"Section: G  |  CSE",GLUT_BITMAP_HELVETICA_12);

        glColor3f(0,0,0);
        drawTextCentered(0,-0.85f,"Date of Submission: May 7, 2026",GLUT_BITMAP_HELVETICA_12);
        glColor3f(0.2f,0.2f,0.5f);
        drawText(-0.30f,-0.92f,"Press ENTER or SPACE to view Instructions",GLUT_BITMAP_HELVETICA_12);

        glutSwapBuffers();
    }
} // namespace Cover

// ═══════════════════════════════════════════════════════════════════════════════
//  PAGE 1 – INSTRUCTIONS  (from Page2.cpp)
// ═══════════════════════════════════════════════════════════════════════════════
namespace Instructions {
    float scaleX=1,scaleY=1;

    void drawText(const char* str,float x,float y,float charH,
                  float r,float g,float b){
        const float base=119.05f;
        float sc=charH/base;
        glColor3f(r,g,b);
        glPushMatrix();
        glTranslatef(x,y,0);
        glScalef(sc*scaleX,sc*scaleY,1);
        for(const char* c=str;*c;++c) glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
        glPopMatrix();
    }
    void fillRect(float x1,float y1,float x2,float y2,float r,float g,float b){
        glColor3f(r,g,b);
        glBegin(GL_QUADS);
        glVertex2f(x1,y1); glVertex2f(x2,y1);
        glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }
    void borderRect(float x1,float y1,float x2,float y2,float lw,float r,float g,float b){
        glColor3f(r,g,b); glLineWidth(lw);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1); glVertex2f(x2,y1);
        glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }

    struct Scene {
        const char* name; const char* kb; const char* mouse;
        const char* sound; const char* collision; char key;
        float r,g,b;
    };
    static Scene scenes[5]={
        {"Afia Jarin Binte Jarjish",
         "P=Play music.wav  S=Stop Sound  Esc=Back",
         "No mouse interaction",
         "music.wav (loop; P=play S=stop)",
         "No collision detection",'1',0.85f,0.90f,1.00f},
        {"MD. Sayeed Alam",
         "P=Pause/Resume  N=Day/Night  R=Rain  M=Music",
         "No mouse interaction",
         "bg.wav (loop; M to toggle)",
         "No collision detection",'2',0.85f,1.00f,0.85f},
        {"Abrar Adnan Pranjal",
         "S=Signal  Space=Pause  Arrows=TrainSpd  M/U=Mute",
         "Left=Toggle Signal  Right=Pause",
         "Train_Sound.wav",
         "People 0&1 walk toward each other",'3',1.00f,0.85f,0.85f},
        {"Rafid Hossain",
         "S=Signal  Space=Pause  Arrows=Speed  M/U=Mute",
         "Left=Toggle Signal  Right=Pause",
         "vehicle.wav (optional)",
         "Person index 7 (red flag) moves slower",'4',1.00f,0.98f,0.80f},
        {"Rahul Sarker",
         "C=Cycle Day/Afternoon/Night  B=Plane Crash",
         "Left Click=Cycle Day/Afternoon/Night",
         "projectsound.wav (startup)",
         "Two planes collide; B to trigger",'5',0.90f,0.85f,1.00f},
    };

    void render(){
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        borderRect(-0.970f,-0.970f,0.970f,0.970f,1.0f,0.70f,0.70f,0.75f);
        fillRect(-0.930f,0.826f,0.930f,0.932f,0.92f,0.92f,0.95f);
        borderRect(-0.930f,0.826f,0.930f,0.932f,1.0f,0.60f,0.60f,0.65f);
        drawText("INSTRUCTION",-0.918f,0.858f,0.048f,0.15f,0.15f,0.20f);

        const float topY=0.736f,botY=-0.730f;
        const float rowH=(topY-botY)/5.0f,gap=0.026f;
        for(int i=0;i<5;i++){
            Scene& e=scenes[i];
            float y2=topY-i*rowH, y1=y2-rowH+gap, midY=(y1+y2)*0.5f;
            fillRect(-0.930f,y1,0.760f,y2,e.r,e.g,e.b);
            borderRect(-0.930f,y1,0.760f,y2,0.8f,0.50f,0.50f,0.55f);
            fillRect(-0.930f,y1,-0.912f,y2,e.r*0.75f,e.g*0.75f,e.b*0.75f);
            fillRect(0.775f,y1,0.930f,y2,0.85f,0.85f,0.90f);
            borderRect(0.775f,y1,0.930f,y2,1.0f,0.45f,0.45f,0.50f);
            char ps[16]; sprintf(ps,"Press %c",e.key);
            drawText(ps,0.786f,midY-0.018f,0.036f,0.10f,0.10f,0.15f);
            char num[4]; sprintf(num,"%c.",e.key);
            drawText(num,-0.905f,y2-0.042f,0.042f,0.15f,0.15f,0.20f);
            drawText(e.name,-0.848f,y2-0.042f,0.042f,0.10f,0.10f,0.15f);
            const float sz=0.022f,xs=-0.910f,xkb=-0.845f,xd=-0.825f,dy=0.042f;
            float ly=y2-0.042f-dy;
            drawText("KB:",xs,ly,sz+0.003f,0.35f,0.35f,0.50f);
            drawText(e.kb,xkb,ly,sz,0.15f,0.15f,0.20f); ly-=dy;
            drawText("Mouse:",xs,ly,sz+0.003f,0.35f,0.35f,0.50f);
            drawText(e.mouse,xd,ly,sz,0.15f,0.15f,0.20f); ly-=dy;
            drawText("Sound:",xs,ly,sz+0.003f,0.35f,0.35f,0.50f);
            drawText(e.sound,xd,ly,sz,0.15f,0.15f,0.20f); ly-=dy;
            drawText("Collision:",xs,ly,sz,0.35f,0.35f,0.50f);
            drawText(e.collision,-0.793f,ly,sz,0.15f,0.15f,0.20f);
            char go[48]; sprintf(go,"Go To The Scenario -- Press %c",e.key);
            drawText(go,-0.930f,y1+0.006f,0.018f,0.45f,0.45f,0.55f);
        }
        fillRect(-0.450f,-0.855f,0.450f,-0.748f,0.90f,0.90f,0.95f);
        borderRect(-0.450f,-0.855f,0.450f,-0.748f,1.0f,0.40f,0.40f,0.45f);
        drawText("Full Merge Project   [ Press F ]",-0.415f,-0.822f,0.045f,0.15f,0.15f,0.20f);
        drawText("ESC=Back to Cover   1-5=Open Scene   F=Full Merge",-0.560f,-0.918f,0.025f,0.45f,0.45f,0.55f);
        glutSwapBuffers();
    }
} // namespace Instructions

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 2 – Afia Jarin Binte Jarjish (coastal scene)
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneAfia {
    float animTime=0,boat1X=-0.48f,boat2X=0.05f,boat3X=0.55f,birdX=-1.2f,birdY=0.75f;

    void drawFilledCircle(float x,float y,float r,float cr,float cg,float cb){
        int n=40; float tp=2.0f*PI;
        glColor3f(cr,cg,cb);
        glBegin(GL_TRIANGLE_FAN); glVertex2f(x,y);
        for(int i=0;i<=n;i++) glVertex2f(x+r*cosf(i*tp/n),y+r*sinf(i*tp/n));
        glEnd();
    }
    void drawRect(float x1,float y1,float x2,float y2,float r,float g,float b){
        glColor3f(r,g,b);
        glBegin(GL_QUADS);
        glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }
    void drawTri(float x1,float y1,float x2,float y2,float x3,float y3,float r,float g,float b){
        glColor3f(r,g,b);
        glBegin(GL_TRIANGLES);
        glVertex2f(x1,y1); glVertex2f(x2,y2); glVertex2f(x3,y3);
        glEnd();
    }
    void drawSun(float x,float y){
        glColor3f(1,0.82f,0);
        glLineWidth(2); glBegin(GL_LINES);
        for(int i=0;i<8;i++){
            float a=i*PI/4.0f+(animTime*0.2f);
            glVertex2f(x+0.055f*cosf(a),y+0.055f*sinf(a));
            glVertex2f(x+0.095f*cosf(a),y+0.095f*sinf(a));
        }
        glEnd(); glLineWidth(1);
        drawFilledCircle(x,y,0.048f,1,0.78f,0);
    }
    

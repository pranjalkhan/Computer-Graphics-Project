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
    void drawPalm(float x,float y,float s,float ph){
        glColor3f(0.45f,0.28f,0.08f); glLineWidth(3);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y); glVertex2f(x+0.01f*s,y+0.12f*s);
        glVertex2f(x+0.02f*s,y+0.24f*s); glVertex2f(x+0.01f*s,y+0.36f*s);
        glEnd(); glLineWidth(1);
        float tx=x+0.01f*s,ty=y+0.36f*s;
        glPushMatrix(); glTranslatef(tx,ty,0);
        glRotatef(sinf(animTime*2+ph)*6,0,0,1);
        float la[][4]={{0,0.10f,0.10f,0.04f},{-0.10f,0.07f,-0.04f,0.04f},
                       {0.07f,0.08f,0.12f,-0.02f},{-0.08f,0.05f,-0.12f,-0.02f},{0,0.06f,0,-0.06f}};
        for(int i=0;i<5;i++) drawTri(0,0,la[i][0]*s,la[i][1]*s,la[i][2]*s,la[i][3]*s,0.15f,0.60f,0.10f);
        glPopMatrix();
    }
    void drawHut(float x,float y,float w,float h){
        drawRect(x,y,x+w,y+h,0.60f,0.35f,0.12f);
        drawTri(x-0.01f,y+h,x+w+0.01f,y+h,x+w*0.5f,y+h+0.08f,0.85f,0.70f,0.15f);
    }
    void drawMainBuilding(){
        float bx=-0.12f,bw=0.26f,bBot=-0.05f,bTop=0.38f;
        drawRect(bx,bBot,bx+bw,bTop,0.72f,0.28f,0.10f);
        float wx[]={-0.07f,0.03f};
        for(int i=0;i<2;i++){
            drawRect(wx[i],bBot+0.08f,wx[i]+0.05f,bBot+0.18f,0.28f,0.10f,0.03f);
            drawFilledCircle(wx[i]+0.025f,bBot+0.18f,0.025f,0.28f,0.10f,0.03f);
            drawRect(wx[i],bBot+0.22f,wx[i]+0.05f,bBot+0.30f,0.28f,0.10f,0.03f);
            drawFilledCircle(wx[i]+0.025f,bBot+0.30f,0.025f,0.28f,0.10f,0.03f);
        }
        drawRect(-0.022f,bBot,0.022f,bBot+0.10f,0.10f,0.35f,0.50f);
        drawRect(-0.06f,bTop,0.06f,bTop+0.04f,0.88f,0.75f,0.60f);
        drawFilledCircle(0,bTop+0.04f,0.09f,0.72f,0.28f,0.10f);
        drawFilledCircle(0,bTop+0.135f,0.015f,0.55f,0.20f,0.08f);
    }
    void drawBoat(float cx,float cy,float s,float sr,float sg,float sb,float hr,float hg,float hb){
        glColor3f(hr,hg,hb);
        glBegin(GL_POLYGON);
        glVertex2f(cx-0.12f*s,cy); glVertex2f(cx+0.12f*s,cy);
        glVertex2f(cx+0.09f*s,cy-0.04f*s); glVertex2f(cx-0.09f*s,cy-0.04f*s);
        glEnd();
        glColor3f(0.40f,0.25f,0.05f); glLineWidth(2);
        glBegin(GL_LINES); glVertex2f(cx-0.01f*s,cy); glVertex2f(cx-0.01f*s,cy+0.22f*s); glEnd();
        glLineWidth(1);
        drawTri(cx-0.01f*s,cy+0.22f*s,cx-0.01f*s,cy+0.03f*s,cx+0.12f*s,cy+0.10f*s,sr,sg,sb);
    }
    void drawBush(float x,float y,float s){
        drawFilledCircle(x,y,0.05f*s,0.18f,0.55f,0.12f);
        drawFilledCircle(x+0.04f*s,y+0.01f*s,0.04f*s,0.22f,0.60f,0.15f);
        drawFilledCircle(x-0.04f*s,y+0.01f*s,0.035f*s,0.15f,0.50f,0.10f);
    }
    void drawPerson(float x,float y,float r,float g,float b){
        drawFilledCircle(x,y+0.055f,0.018f,0.85f,0.65f,0.45f);
        glColor3f(r,g,b); glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2f(x,y+0.037f); glVertex2f(x,y-0.010f);
        glVertex2f(x-0.018f,y+0.018f); glVertex2f(x+0.018f,y+0.018f);
        glVertex2f(x,y-0.010f); glVertex2f(x-0.014f,y-0.038f);
        glVertex2f(x,y-0.010f); glVertex2f(x+0.014f,y-0.038f);
        glEnd(); glLineWidth(1);
    }
    void drawBird(float x,float y){
        glColor3f(0.15f,0.15f,0.15f); glLineWidth(2);
        float fl=sinf(animTime*10)*0.03f;
        glBegin(GL_LINE_STRIP);
        glVertex2f(x-0.04f,y+0.02f+fl); glVertex2f(x,y); glVertex2f(x+0.04f,y+0.02f+fl);
        glEnd(); glLineWidth(1);
    }

    void render(){
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        drawRect(-1,-1,1,1,0.97f,0.96f,0.92f);
        // clouds
        drawFilledCircle(-0.20f,0.55f,0.09f,1,1,1); drawFilledCircle(-0.08f,0.58f,0.07f,1,1,1);
        drawFilledCircle(0.04f,0.54f,0.06f,1,1,1);  drawFilledCircle(0.30f,0.62f,0.08f,1,1,1);
        drawFilledCircle(0.40f,0.65f,0.06f,1,1,1);  drawFilledCircle(0.20f,0.60f,0.06f,1,1,1);
        drawSun(-0.52f,0.70f);
        drawBird(birdX,birdY);
        drawFilledCircle(0.10f,-0.02f,0.28f,0.25f,0.60f,0.15f);
        drawRect(-1,-0.18f,1,0.02f,0.88f,0.76f,0.38f);
        drawRect(-1,-0.55f,1,-0.18f,0.18f,0.62f,0.85f);
        glColor3f(0.30f,0.72f,0.92f); glLineWidth(1.5f);
        for(float wy=-0.25f;wy>-0.52f;wy-=0.06f){
            glBegin(GL_LINE_STRIP);
            for(float wx=-0.9f;wx<0.9f;wx+=0.08f) glVertex2f(wx,wy+0.008f*sinf(wx*12+animTime*3));
            glEnd();
        }
        glLineWidth(1);
        glPushMatrix(); glTranslatef(-0.85f,0,0); drawBush(0,0,1.2f); glPopMatrix();
        glPushMatrix(); glTranslatef(-0.70f,0.02f,0); drawBush(0,0,1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-0.82f,0,0);
        drawHut(-0.08f,-0.14f,0.14f,0.10f); drawHut(0.07f,-0.14f,0.12f,0.09f); drawHut(0.22f,-0.14f,0.13f,0.09f);
        glPopMatrix();
        float palms[][2]={{-0.75f,-0.14f},{-0.42f,-0.10f},{-0.05f,-0.08f},{0.38f,-0.10f},{0.68f,-0.12f},{0.82f,-0.12f}};
        float palmS[]={1,1.1f,1.2f,1,1.1f,0.9f};
        for(int i=0;i<6;i++){
            glPushMatrix(); glTranslatef(palms[i][0],palms[i][1],0);
            drawPalm(0,0,palmS[i],(float)i); glPopMatrix();
        }
        glPushMatrix(); glTranslatef(0.08f,0,0); drawMainBuilding(); glPopMatrix();
        glPushMatrix(); glTranslatef(0.46f,0,0); drawHut(-0.06f,-0.14f,0.18f,0.09f); glPopMatrix();
        drawPerson(-0.60f,-0.16f,0.10f,0.30f,0.70f); drawPerson(-0.55f,-0.16f,0.20f,0.30f,0.70f);
        drawPerson(-0.30f,-0.16f,0.10f,0.30f,0.70f); drawPerson(0.52f,-0.16f,0.10f,0.30f,0.70f);
        drawPerson(0.58f,-0.16f,0.20f,0.40f,0.65f);
        glPushMatrix(); glTranslatef(boat1X,-0.32f,0); drawBoat(0,0,1,0.90f,0.70f,0.05f,0.45f,0.25f,0.05f); glPopMatrix();
        glPushMatrix(); glTranslatef(boat2X,-0.30f,0); drawBoat(0,0,1,0.95f,0.95f,0.90f,0.45f,0.25f,0.05f); glPopMatrix();
        glPushMatrix(); glTranslatef(boat3X,-0.34f,0); drawBoat(0,0,0.85f,0.88f,0.68f,0.05f,0.42f,0.22f,0.04f); glPopMatrix();

        // HUD hint
        glColor3f(0.2f,0.2f,0.5f);
        glRasterPos2f(-0.95f,-0.92f);
        const char* hint="P=Play Sound  S=Stop  ESC=Back to Instructions";
        for(const char* c=hint;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*c);

        glutSwapBuffers();
    }

    void update(){
        animTime+=0.016f;
        boat1X+=0.001f; if(boat1X>1.2f) boat1X=-1.2f;
        boat2X+=0.0007f; if(boat2X>1.2f) boat2X=-1.2f;
        boat3X-=0.0015f; if(boat3X<-1.2f) boat3X=1.2f;
        birdX+=0.004f; birdY=0.70f+sinf(animTime*2)*0.05f;
        if(birdX>1.2f) birdX=-1.2f;
    }
    void keyboard(unsigned char key){
        if(key=='p'||key=='P'){
#ifdef _WIN32
            PlaySound(TEXT("music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
#endif
        }
        if(key=='s'||key=='S'){
#ifdef _WIN32
            PlaySound(NULL,0,0);
#endif
        }
    }
    void reset(){ animTime=0; boat1X=-0.48f; boat2X=0.05f; boat3X=0.55f; birdX=-1.2f; }
} // namespace SceneAfia

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 3 – MD. Sayeed Alam (Historical Dhaka 1800s)
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneSayeed {
#define S_NUM_CLOUDS 5
#define S_NUM_PEOPLE 4
#define S_NUM_RAINS  300
    bool cloudsPaused=false, isNight=false, musicEnabled=false, rainEnabled=false;
    struct Rain{ float x,y,speed; };
    Rain g_rain[S_NUM_RAINS];
    struct Cloud{ float baseX,baseY,offsetX,speed,scale; };
    struct Person2{
        float x,y,scale,sr,sg,sb,pr,pg,pb,skr,skg,skb;
    };
    Cloud g_clouds[S_NUM_CLOUDS]={
        {-0.70f,0.78f,0,0.00018f,1.0f},{0.00f,0.86f,0,0.00012f,0.8f},
        {0.50f,0.80f,0,0.00020f,1.2f},{-0.20f,0.90f,0,0.00015f,0.7f},{0.80f,0.73f,0,0.00019f,0.9f}
    };
    Person2 g_people[S_NUM_PEOPLE]={
        {-0.55f,-0.45f,0.80f,0,0.3f,0.6f,0.1f,0.1f,0.1f,0.6f,0.4f,0.2f},
        {0.00f,-0.60f,0.85f,0.9f,0.9f,0.8f,0.6f,0.1f,0.1f,0.5f,0.3f,0.1f},
        {0.55f,-0.48f,0.78f,0.9f,0.9f,0.9f,0.7f,0.6f,0.4f,0.7f,0.5f,0.3f},
        {-0.15f,-0.70f,0.90f,0.2f,0.6f,0.2f,0.2f,0.2f,0.2f,0.6f,0.4f,0.2f}
    };

    void sq(float x1,float y1,float x2,float y2){
        glBegin(GL_QUADS);
        glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }
    void fc(float cx,float cy,float r,int n){
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int i=0;i<=n;i++){float a=i*2*PI/n; glVertex2f(cx+r*cosf(a),cy+r*sinf(a));}
        glEnd();
    }
    void fe(float cx,float cy,float rx,float ry,int n){
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int i=0;i<=n;i++){float a=i*2*PI/n; glVertex2f(cx+rx*cosf(a),cy+ry*sinf(a));}
        glEnd();
    }
    void drawCloud(const Cloud& c){
        float x=c.baseX+c.offsetX,y=c.baseY,s=c.scale;
        glColor3f(1,1,1);
        fe(x-0.08f*s,y,0.07f*s,0.04f*s,20);
        fe(x+0.08f*s,y,0.07f*s,0.04f*s,20);
        fe(x,y+0.03f*s,0.09f*s,0.05f*s,20);
    }
    void drawBackground(){
        if(!isNight){
            glBegin(GL_QUADS);
            glColor3f(0.40f,0.68f,0.90f); glVertex2f(-1,1); glVertex2f(1,1);
            glColor3f(0.65f,0.85f,0.98f); glVertex2f(1,0.2f); glVertex2f(-1,0.2f);
            glEnd();
            glColor3f(0.85f,0.50f,0.30f); sq(-1,-1,1,0.2f);
        } else {
            glBegin(GL_QUADS);
            glColor3f(0.02f,0.02f,0.08f); glVertex2f(-1,1); glVertex2f(1,1);
            glColor3f(0.05f,0.05f,0.15f); glVertex2f(1,0.2f); glVertex2f(-1,0.2f);
            glEnd();
            glColor3f(0.15f,0.10f,0.10f); sq(-1,-1,1,0.2f);
        }
    }
    void drawSunS(){
        if(!isNight){ glColor3f(1,0.95f,0.35f); fc(0.75f,0.80f,0.08f,40); }
        else {
            glColor3f(0.9f,0.9f,0.95f); fc(0.75f,0.80f,0.07f,40);
            glColor3f(0.02f,0.02f,0.08f); fc(0.78f,0.82f,0.07f,40);
        }
    }
    void drawRain(){
        if(!rainEnabled) return;
        glColor3f(0.7f,0.8f,1);
        glBegin(GL_LINES);
        for(int i=0;i<S_NUM_RAINS;i++){
            glVertex2f(g_rain[i].x,g_rain[i].y);
            glVertex2f(g_rain[i].x,g_rain[i].y-0.03f);
        }
        glEnd();
    }
    void drawTree(float x,float y,float s){
        glColor3f(0.42f,0.28f,0.12f); sq(x-0.015f*s,y,x+0.015f*s,y+0.18f*s);
        glColor3f(0.2f,0.55f,0.2f);
        fc(x,y+0.23f*s,0.08f*s,20); fc(x-0.05f*s,y+0.18f*s,0.06f*s,20);
        fc(x+0.05f*s,y+0.18f*s,0.06f*s,20);
    }
    void drawBuilding2(float x,float y,float w,float h){
        glColor3f(0.90f,0.75f,0.50f); sq(x,y,x+w,y+h);
        glColor3f(0.75f,0.35f,0.15f);
        glBegin(GL_TRIANGLES); glVertex2f(x-0.02f,y+h); glVertex2f(x+w+0.02f,y+h); glVertex2f(x+w/2,y+h+0.12f); glEnd();
        glColor3f(0.40f,0.20f,0.05f); sq(x+w*0.40f,y,x+w*0.60f,y+h*0.65f);
        glColor3f(0.15f,0.15f,0.15f);
        sq(x+w*0.15f,y+h*0.35f,x+w*0.35f,y+h*0.68f);
        fc(x+w*0.25f,y+h*0.68f,w*0.10f,20);
        sq(x+w*0.65f,y+h*0.35f,x+w*0.85f,y+h*0.68f);
        fc(x+w*0.75f,y+h*0.68f,w*0.10f,20);
    }
    void drawMainBuildingS(){
        glColor3f(0.82f,0.60f,0.38f); sq(-0.42f,0.05f,0.42f,0.62f);
        glColor3f(0.65f,0.45f,0.25f); sq(-0.48f,0,0.48f,0.05f);
        glColor3f(0.70f,0.40f,0.20f); sq(-0.45f,0.62f,0.45f,0.68f);
        glColor3f(0.95f,0.90f,0.75f); fc(0,0.74f,0.14f,40);
        glColor3f(0.25f,0.15f,0.08f); sq(-0.08f,0.05f,0.08f,0.38f); fc(0,0.38f,0.08f,30);
        glColor3f(0.15f,0.15f,0.15f);
        float wX[]={-0.34f,-0.20f,0.10f,0.24f};
        for(int i=0;i<4;i++){
            sq(wX[i],0.42f,wX[i]+0.10f,0.52f); fc(wX[i]+0.05f,0.52f,0.05f,20);
            sq(wX[i],0.24f,wX[i]+0.10f,0.34f); fc(wX[i]+0.05f,0.34f,0.05f,20);
        }
    }
    void drawPersonS(const Person2& p){
        glPushMatrix(); glTranslatef(p.x,p.y,0);
        float s=p.scale;
        glColor3f(p.pr,p.pg,p.pb);
        sq(-0.015f*s,-0.06f*s,-0.002f*s,0.01f*s);
        sq(0.002f*s,-0.06f*s,0.015f*s,0.01f*s);
        glColor3f(p.sr,p.sg,p.sb); sq(-0.022f*s,0.01f*s,0.022f*s,0.08f*s);
        glColor3f(p.skr,p.skg,p.skb); fc(0,0.11f*s,0.024f*s,16);
        glPopMatrix();
    }

    void initRain(){
        for(int i=0;i<S_NUM_RAINS;i++){
            g_rain[i].x=(float(rand())/RAND_MAX)*2-1;
            g_rain[i].y=(float(rand())/RAND_MAX)*2;
            g_rain[i].speed=0.01f+(float(rand()%10)/1000.0f);
        }
    }

    void render(){
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        drawBackground(); drawSunS(); drawRain();
        for(int i=0;i<S_NUM_CLOUDS;i++) drawCloud(g_clouds[i]);
        drawTree(-0.95f,0.20f,1.1f); drawTree(0.90f,0.20f,1.0f);
        drawBuilding2(-0.90f,0.05f,0.30f,0.30f); drawBuilding2(0.60f,0.08f,0.28f,0.25f);
        drawMainBuildingS();
        for(int i=0;i<S_NUM_PEOPLE;i++) drawPersonS(g_people[i]);

        glColor3f(0.2f,0.2f,0.5f);
        glRasterPos2f(-0.95f,-0.92f);
        const char* hint="P=Pause  N=Day/Night  R=Rain  M=Toggle Music  ESC=Back";
        for(const char* c=hint;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*c);
        glutSwapBuffers();
    }

    void update(){
        if(!cloudsPaused){
            for(int i=0;i<S_NUM_CLOUDS;i++){
                g_clouds[i].offsetX+=g_clouds[i].speed;
                if(g_clouds[i].baseX+g_clouds[i].offsetX>1.4f)
                    g_clouds[i].offsetX=-1.4f-g_clouds[i].baseX;
            }
        }
        if(rainEnabled){
            for(int i=0;i<S_NUM_RAINS;i++){
                g_rain[i].y-=g_rain[i].speed;
                if(g_rain[i].y<-1){ g_rain[i].y=1; g_rain[i].x=(float(rand())/RAND_MAX)*2-1; }
            }
        }
    }
    void keyboard(unsigned char key){
        if(key=='p'||key=='P') cloudsPaused=!cloudsPaused;
        if(key=='n'||key=='N') isNight=!isNight;
        if(key=='r'||key=='R') rainEnabled=!rainEnabled;
        if(key=='m'||key=='M'){
            musicEnabled=!musicEnabled;
#ifdef _WIN32
            if(musicEnabled) PlaySound("bg.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
            else PlaySound(NULL,0,0);
#endif
        }
    }
    void reset(){ cloudsPaused=false; isNight=false; rainEnabled=false; musicEnabled=false; }
} // namespace SceneSayeed

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 4 – Abrar Adnan Pranjal (Train Station)
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneAbrar {
#define AB_MAX_SMOKE 300
#define AB_NUM_PEOPLE 9
#define AB_FLOCK 7

    bool g_soundMuted=false, g_paused=false;
    int  g_signal=1, g_frame=0, g_winWidth=1100, g_winHeight=650;
    int  g_signalFlash=0;
    float g_flashIntensity=0;
    float g_trainX=-0.3f, g_wheelAngle=0, g_pistonPhase=0, g_sunAngle=-0.3f;
    float g_cloudX[6]={-0.70f,0,0.55f,-0.20f,0.80f,-0.90f};
    float g_cloudY[6]={0.78f,0.88f,0.82f,0.92f,0.75f,0.86f};
    float g_cloudSp[6]={0.00008f,0.00006f,0.00010f,0.00005f,0.00009f,0.00007f};
    float g_trainSpeed=0.0003f;

    struct ABSmoke{ float x,y,vx,vy,r,alpha; bool white,active; };
    ABSmoke g_smoke[AB_MAX_SMOKE];

    struct ABPerson{
        float baseX,baseY,scale,sr,sg,sb,pr,pg,pb,skr,skg,skb;
        bool wave,hat; float hr,hg,hb,offsetX,dir,speed;
    };
    ABPerson g_people[AB_NUM_PEOPLE]={
        {-0.72f,-0.370f,0.90f,0.90f,0.90f,0.88f,0.22f,0.18f,0.12f,0.82f,0.60f,0.42f,false,false,0,0,0,0,1,0.0004f},
        {-0.54f,-0.368f,0.92f,0.88f,0.62f,0.12f,0.24f,0.18f,0.06f,0.95f,0.74f,0.50f,true, false,0,0,0,0,-1,0.0005f},
        {-0.44f,-0.366f,0.90f,0.12f,0.26f,0.65f,0.08f,0.12f,0.32f,0.80f,0.58f,0.40f,false,false,0,0,0,0,1,0.00045f},
        {0.22f,-0.370f,0.92f,0.10f,0.10f,0.18f,0.06f,0.06f,0.12f,0.80f,0.56f,0.38f,false,false,0,0,0,0,-1,0.00055f},
        {0.32f,-0.368f,0.90f,0.88f,0.78f,0.22f,0.10f,0.28f,0.14f,0.84f,0.58f,0.38f,true, false,0,0,0,0,1,0.00038f},
        {0.62f,-0.370f,0.90f,0.74f,0.24f,0.10f,0.20f,0.12f,0.05f,0.85f,0.64f,0.44f,false,false,0,0,0,0,-1,0.00048f},
        {-0.14f,-0.620f,1.08f,0.36f,0.12f,0.62f,0.14f,0.06f,0.36f,0.82f,0.58f,0.40f,true, false,0,0,0,0,1,0.00042f},
        {-0.02f,-0.622f,1.05f,0.88f,0.65f,0.12f,0.22f,0.16f,0.05f,0.95f,0.74f,0.50f,false,false,0,0,0,0,-1,0.0005f},
        {0.09f,-0.620f,1.05f,0.22f,0.36f,0.18f,0.10f,0.16f,0.08f,0.76f,0.48f,0.32f,true, false,0,0,0,0,1,0.00044f},
    };
    struct ABBird{ float x,y,speed,r,g,b; };
    ABBird g_flock[AB_FLOCK];

    // ── drawing helpers ──
    void qd(float x1,float y1,float x2,float y2){
        glBegin(GL_QUADS);
        glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2);
        glEnd();
    }
    void fc(float cx,float cy,float r,int n){
        float tp=2*PI;
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int i=0;i<=n;i++) glVertex2f(cx+r*cosf(i*tp/n),cy+r*sinf(i*tp/n));
        glEnd();
    }
    void oc(float cx,float cy,float r,int n,float lw){
        float tp=2*PI; glLineWidth(lw);
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<=n;i++) glVertex2f(cx+r*cosf(i*tp/n),cy+r*sinf(i*tp/n));
        glEnd();
    }
    void fe(float cx,float cy,float rx,float ry,int n){
        float tp=2*PI;
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int i=0;i<=n;i++) glVertex2f(cx+rx*cosf(i*tp/n),cy+ry*sinf(i*tp/n));
        glEnd();
    }

    void initSmoke(){ for(int i=0;i<AB_MAX_SMOKE;i++) g_smoke[i].active=false; }
    void spawnSmoke(float bx,float by,bool white){
        for(int i=0;i<AB_MAX_SMOKE;i++){
            if(!g_smoke[i].active){
                float vx=((float)rand()/RAND_MAX-0.45f)*0.0006f;
                float vy=0.0020f+(float)rand()/RAND_MAX*0.003f;
                float rv=0.022f+(float)rand()/RAND_MAX*0.016f;
                g_smoke[i]={bx,by,vx,vy,rv,0.80f,white,true}; return;
            }
        }
    }
    void updateSmoke(){
        for(int i=0;i<AB_MAX_SMOKE;i++){
            if(!g_smoke[i].active) continue;
            g_smoke[i].x+=g_smoke[i].vx+0.0001f;
            g_smoke[i].y+=g_smoke[i].vy*0.6f;
            g_smoke[i].r+=0.0005f; g_smoke[i].alpha-=0.003f;
            if(g_smoke[i].alpha<=0) g_smoke[i].active=false;
        }
    }
    void drawSmoke(){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        for(int i=0;i<AB_MAX_SMOKE;i++){
            if(!g_smoke[i].active) continue;
            if(g_smoke[i].white) glColor4f(0.92f,0.92f,0.92f,g_smoke[i].alpha);
            else                  glColor4f(0.32f,0.32f,0.34f,g_smoke[i].alpha);
            fc(g_smoke[i].x,g_smoke[i].y,g_smoke[i].r,20);
        }
        glDisable(GL_BLEND);
    }
    void drawBackground(){
        glBegin(GL_QUADS);
        glColor3f(0.42f,0.72f,0.95f); glVertex2f(-1,1); glVertex2f(1,1);
        glColor3f(0.62f,0.86f,0.98f); glVertex2f(1,-1); glVertex2f(-1,-1);
        glEnd();
        glColor3f(0.76f,0.42f,0.22f); qd(-1,-1,1,-0.10f);
        glColor3f(0.80f,0.46f,0.25f); qd(-1,-0.55f,1,-0.38f);
        glColor3f(0.58f,0.28f,0.12f); qd(-1,-0.50f,1,-0.42f);
        glColor3f(0.72f,0.38f,0.20f); qd(-1,-1,1,-0.50f);
        glColor3f(0.64f,0.32f,0.16f); qd(-1,-1,1,-0.72f);
    }
    void drawSunAB(){
        float sx=cosf(g_sunAngle)*0.78f,sy=0.65f+sinf(g_sunAngle)*0.30f;
        glColor3f(1,0.92f,0.25f); fc(sx,sy,0.062f,32);
        glColor3f(1,0.97f,0.70f); fc(sx,sy,0.045f,32);
    }
    void drawCloud(float cx,float cy){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1,1,1,0.95f);
        fe(cx-0.09f,cy,0.072f,0.048f,20); fe(cx+0.09f,cy,0.072f,0.048f,20);
        fe(cx,cy,0.080f,0.052f,20); fe(cx-0.06f,cy+0.045f,0.062f,0.050f,20);
        fe(cx+0.05f,cy+0.050f,0.058f,0.048f,20); fe(cx,cy+0.065f,0.055f,0.045f,20);
        glDisable(GL_BLEND);
    }
    void drawTreeAB(float tx,float ty,float s){
        glColor3f(0.38f,0.22f,0.09f); qd(tx-0.01f*s,ty,tx+0.01f*s,ty+0.16f*s);
        glColor3f(0.18f,0.42f,0.14f);
        fc(tx,ty+0.17f*s,0.065f*s,22); fc(tx-0.04f*s,ty+0.14f*s,0.055f*s,20);
        fc(tx+0.04f*s,ty+0.15f*s,0.052f*s,20); fc(tx,ty+0.22f*s,0.048f*s,18);
    }
    void drawBuilding(float x,float y,float w,float h,float r,float g,float b,float dr,float dg,float db,int wins,int winRows,bool arch,bool gable){
        glColor3f(r,g,b); qd(x,y,x+w,y+h);
        glColor3f(dr*0.85f,dg*0.85f,db*0.85f); qd(x-0.005f,y+h,x+w+0.005f,y+h+0.022f);
        if(gable){
            glColor3f(dr*0.70f,dg*0.70f,db*0.70f);
            glBegin(GL_TRIANGLES);
            glVertex2f(x,y+h+0.018f); glVertex2f(x+w*0.5f,y+h+0.065f); glVertex2f(x+w,y+h+0.018f);
            glEnd();
        }
        if(arch){
            float ax=x+w*0.22f,aw=0.065f;
            glColor3f(dr*0.55f,dg*0.55f,db*0.55f);
            qd(ax,y,ax+aw,y+0.10f); fc(ax+aw*0.5f,y+0.10f,aw*0.5f,16);
            ax=x+w*0.55f; qd(ax,y,ax+aw,y+0.10f); fc(ax+aw*0.5f,y+0.10f,aw*0.5f,16);
        }
        float ww=0.032f,wh=0.042f,gap=(w-wins*ww)/(wins+1);
        float winStartY=arch?0.16f:0.05f;
        for(int row=0;row<winRows;row++){
            float wy=y+winStartY+row*(wh+0.038f);
            for(int i=0;i<wins;i++){
                float wx=x+gap+i*(ww+gap);
                glColor3f(dr*0.55f,dg*0.50f,db*0.45f); qd(wx-0.003f,wy-0.003f,wx+ww+0.003f,wy+wh+0.003f);
                glColor3f(0.55f,0.42f,0.22f); qd(wx,wy,wx+ww,wy+wh);
            }
        }
    }
    void drawFactory(float x,float y){
        float w=0.18f,h=0.52f;
        glColor3f(0.52f,0.22f,0.10f); qd(x,y,x+w,y+h);
        glColor3f(0.38f,0.14f,0.05f); qd(x-0.004f,y+h,x+w+0.004f,y+h+0.020f);
        float aww=0.045f;
        for(int i=0;i<3;i++){
            float ax=x+0.022f+i*(aww+0.012f),ay=y+0.08f;
            glColor3f(0.28f,0.08f,0.03f); qd(ax,ay,ax+aww,ay+0.14f); fc(ax+aww*0.5f,ay+0.14f,aww*0.5f,14);
            glColor3f(0.50f,0.38f,0.18f); qd(ax+0.003f,ay,ax+aww-0.003f,ay+0.14f);
        }
        float chx=x+w*0.70f,chH=0.50f;
        glColor3f(0.40f,0.18f,0.07f); qd(chx,y+h,chx+0.038f,y+h+chH);
        glColor3f(0.18f,0.08f,0.03f); qd(chx-0.008f,y+h+chH-0.012f,chx+0.046f,y+h+chH+0.008f);
    }
    void drawStationHouse(float x,float y){
        float w=0.16f,h=0.36f;
        glColor3f(0.88f,0.72f,0.30f); qd(x,y,x+w,y+h);
        glColor3f(0.60f,0.48f,0.20f); qd(x,y+h*0.68f,x+w,y+h);
        glColor3f(0.35f,0.28f,0.18f);
        glBegin(GL_TRIANGLES); glVertex2f(x-0.008f,y+h); glVertex2f(x+w*0.5f,y+h+0.06f); glVertex2f(x+w+0.008f,y+h); glEnd();
        glColor3f(0.45f,0.35f,0.15f);
        qd(x+0.02f,y+0.10f,x+0.07f,y+0.18f); qd(x+0.09f,y+0.10f,x+0.14f,y+0.18f);
        glColor3f(0.35f,0.25f,0.10f);
        qd(x+w*0.38f,y,x+w*0.38f+0.045f,y+0.12f); fc(x+w*0.38f+0.0225f,y+0.12f,0.0225f,14);
    }
    void drawLampAB(float x,float y){
        glColor3f(0.48f,0.48f,0.50f); qd(x-0.004f,y,x+0.004f,y+0.18f);
        glLineWidth(2.5f); glColor3f(0.45f,0.45f,0.48f);
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<=10;i++){ float a=PI+i*PI*0.5f/10; glVertex2f(x+0.020f*cosf(a),y+0.18f+0.020f*sinf(a)); }
        glEnd();
        glColor3f(1,0.95f,0.60f); fc(x+0.020f,y+0.200f,0.014f,14);
    }
    void drawSignalAB(){
        float sx=0.15f,sy=-0.22f;
        glColor3f(0.35f,0.35f,0.38f); qd(sx-0.007f,sy-0.30f,sx+0.007f,-0.42f);
        glColor3f(0.12f,0.12f,0.14f); qd(sx-0.024f,sy,sx+0.024f,sy+0.090f);
        if(g_signalFlash>0){
            glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1,1,0.8f,0.6f*g_flashIntensity); fc(sx,sy+0.052f,0.045f,20);
            glDisable(GL_BLEND);
            g_signalFlash--; g_flashIntensity=g_signalFlash/15.0f;
        }
        if(g_signal==0) glColor3f(1,0.10f,0.10f); else glColor3f(0.18f,0,0);
        fc(sx,sy+0.070f,0.015f,14);
        if(g_signal==1) glColor3f(0.10f,1,0.22f); else glColor3f(0,0.18f,0.04f);
        fc(sx,sy+0.035f,0.015f,14);
        glColor3f(0.30f,0.30f,0.32f); qd(sx-0.018f,sy-0.30f,sx+0.018f,sy-0.26f);
    }
    void drawWheel(float cx,float cy,float r){
        glColor3f(0.10f,0.10f,0.12f); fc(cx,cy,r,32);
        glColor3f(0.38f,0.38f,0.40f); oc(cx,cy,r,32,2.5f);
        glColor3f(0.50f,0.52f,0.55f); fc(cx,cy,r*0.70f,28);
        glPushMatrix(); glTranslatef(cx,cy,0); glRotatef(g_wheelAngle,0,0,1);
        glColor3f(0.25f,0.26f,0.28f); glLineWidth(2.5f); glBegin(GL_LINES);
        for(int s=0;s<8;s++){ float a=s*PI/4; glVertex2f(r*0.15f*cosf(a),r*0.15f*sinf(a)); glVertex2f(r*0.65f*cosf(a),r*0.65f*sinf(a)); }
        glEnd(); glPopMatrix();
        glColor3f(0.12f,0.12f,0.14f); fc(cx,cy,r*0.16f,12);
    }
    void drawTracks(){
        glColor3f(0.42f,0.32f,0.18f); qd(-1,-0.480f,1,-0.415f);
        glColor3f(0.55f,0.55f,0.58f); glLineWidth(3.5f);
        glBegin(GL_LINES);
        glVertex2f(-1,-0.422f); glVertex2f(1,-0.422f);
        glVertex2f(-1,-0.462f); glVertex2f(1,-0.462f);
        glEnd();
        glLineWidth(5.5f); glColor3f(0.40f,0.25f,0.11f);
        glBegin(GL_LINES);
        for(float sx=-1;sx<1;sx+=0.065f){ glVertex2f(sx,-0.416f); glVertex2f(sx,-0.470f); }
        glEnd();
    }
    void drawTrainWheels(){
        float tx=g_trainX;
        drawWheel(tx+0.79f,-0.450f,0.055f); drawWheel(tx+0.94f,-0.450f,0.055f);
        drawWheel(tx+0.46f,-0.448f,0.060f); drawWheel(tx+0.64f,-0.448f,0.060f);
        drawWheel(tx+0.23f,-0.448f,0.055f); drawWheel(tx+0.35f,-0.448f,0.055f);
        float bx=tx-0.30f;
        drawWheel(bx+0.016f,-0.450f,0.078f); drawWheel(bx+0.122f,-0.450f,0.078f);
        drawWheel(bx+0.218f,-0.450f,0.078f); drawWheel(bx-0.005f,-0.450f,0.055f);
        drawWheel(bx+0.304f,-0.450f,0.055f);
    }
    void drawPiston(float tx){
        float ry=-0.336f;
        glColor3f(0.60f,0.28f,0.08f); qd(tx-0.22f,ry-0.005f,tx+0.09f,ry+0.015f);
        float pl=0.07f+sinf(g_pistonPhase)*0.028f;
        glColor3f(0.45f,0.45f,0.48f); qd(tx-0.26f-pl,ry-0.005f,tx-0.22f,ry+0.016f);
        glColor3f(0.28f,0.28f,0.30f); qd(tx-0.25f,ry-0.015f,tx-0.18f,ry+0.025f);
    }
    void drawTrain(){
        float tx=g_trainX;
        // freight car
        glColor3f(0.65f,0.18f,0.06f); qd(tx+0.73f,-0.38f,tx+1.03f,-0.38f+0.25f);
        glColor3f(0.38f,0.40f,0.42f); qd(tx+0.725f,-0.38f+0.25f,tx+1.035f,-0.38f+0.275f);
        // passenger car
        glColor3f(0.72f,0.22f,0.07f); qd(tx+0.39f,-0.37f,tx+0.73f,-0.37f+0.26f);
        glColor3f(0.36f,0.38f,0.42f); qd(tx+0.385f,-0.37f+0.26f,tx+0.735f,-0.37f+0.288f);
        for(int w=0;w<6;w++){
            float wx=tx+0.407f+w*0.050f,wy=-0.37f+0.045f;
            glColor3f(0.62f,0.76f,0.88f); qd(wx,wy,wx+0.038f,wy+0.075f);
        }
        // tender
        glColor3f(0.14f,0.14f,0.17f); qd(tx+0.17f,-0.35f,tx+0.39f,-0.14f);
        // locomotive
        glColor3f(0.65f,0.20f,0.06f); qd(tx-0.04f,-0.36f,tx+0.17f,-0.09f);
        glColor3f(0.25f,0.26f,0.30f); qd(tx-0.04f,-0.09f,tx+0.17f,-0.060f);
        glColor3f(0.18f,0.32f,0.50f); qd(tx+0.02f,-0.30f,tx+0.12f,-0.14f);
        float bx=tx-0.30f,by=-0.285f,brad=0.105f;
        glColor3f(0.12f,0.12f,0.15f); qd(bx,by-brad,bx+0.32f,by+brad);
        glColor3f(0.10f,0.10f,0.13f); fc(bx,by,brad+0.005f,32);
        float skx=bx+0.064f,sky=by+brad;
        glColor3f(0.10f,0.10f,0.12f);
        qd(skx-0.022f,sky,skx+0.022f,sky+0.075f); qd(skx-0.035f,sky+0.062f,skx+0.035f,sky+0.085f);
        fc(skx,sky+0.080f,0.038f,22);
        glColor3f(0.72f,0.12f,0.04f);
        glBegin(GL_TRIANGLES);
        glVertex2f(bx-0.005f,-0.360f); glVertex2f(bx-0.095f,-0.435f); glVertex2f(bx+0.015f,-0.360f);
        glEnd();
        glColor3f(0.42f,0.20f,0.07f); qd(bx-0.008f,-0.370f,bx+0.49f,-0.355f);
        drawPiston(tx);
    }
    void drawOnePerson(const ABPerson& p){
        float s=p.scale;
        glColor3f(0.10f,0.07f,0.02f);
        fe(-0.014f*s,-0.068f*s,0.014f*s,0.007f*s,10);
        fe(0.014f*s,-0.068f*s,0.014f*s,0.007f*s,10);
        glColor3f(p.pr,p.pg,p.pb);
        qd(-0.020f*s,-0.065f*s,-0.005f*s,0.018f*s);
        qd(0.005f*s,-0.065f*s,0.020f*s,0.018f*s);
        glColor3f(p.sr,p.sg,p.sb);
        glBegin(GL_QUADS);
        glVertex2f(-0.024f*s,0.018f*s); glVertex2f(0.024f*s,0.018f*s);
        glVertex2f(0.026f*s,0.090f*s);  glVertex2f(-0.026f*s,0.090f*s);
        glEnd();
        glColor3f(p.skr,p.skg,p.skb);
        fc(0,0.128f*s,0.030f*s,20);
    }


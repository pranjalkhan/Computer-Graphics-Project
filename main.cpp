/*
 * ============================================================
 *  MERGED CG PROJECT - AIUB (Single-Author Edition)
 *  Pages: Cover (0), Instructions (1), Scenes (2-6)
 * ============================================================
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

static int g_scene = 0;
static int g_winW = 1100, g_winH = 650;
static int g_fullMergeActive = 0;
static int g_mergeIdx = 0;
static int g_mergeTick = 0;

#ifndef PI
#define PI 3.14159265358979323846f
#endif

// ═══════════════════════════════════════════════════════════════════════════════
//  PAGE 0 – COVER  (no student table — single-author layout)
// ═══════════════════════════════════════════════════════════════════════════════
namespace Cover {
    // EDIT YOUR NAME HERE ↓
    static const char* studentName = "Abrar Adnan Pranjal";
    static const char* studentID   = "23-53229-3";

    void drawText(float x, float y, const char* str,
                  void* font = GLUT_BITMAP_HELVETICA_12) {
        glRasterPos2f(x, y);
        for (int i = 0; str[i]; i++) glutBitmapCharacter(font, str[i]);
    }
    void drawTextCentered(float cx, float y, const char* str, void* font) {
        int len = strlen(str);
        float charW = 0.007f;
        if (font == GLUT_BITMAP_HELVETICA_18)        charW = 0.011f;
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
    void drawBackgroundDecor(float t) {
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i=0;i<6;i++) {
            float cx = -0.85f + i*0.34f;
            float cy = 0.35f + 0.10f*sinf(t*0.6f + i);
            float r  = 0.05f + 0.02f*cosf(t + i*1.2f);
            glColor4f(0.85f,0.88f,1.0f,0.25f);
            glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
            for(int k=0;k<=6;k++){
                float a = k*PI/3 + t*0.3f;
                glVertex2f(cx+r*cosf(a), cy+r*sinf(a));
            }
            glEnd();
        }
        glDisable(GL_BLEND);
    }

    void render() {
        static float t = 0; t += 0.02f;
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        drawBackgroundDecor(t);

        // Outer frame
        glColor3f(0.3f,0.3f,0.4f);
        drawRect(-0.96f,-0.96f,0.96f,0.96f);

        // Header bar
        glColor3f(0.0f,0.0f,0.2f);
        fillRect(-0.90f,0.80f,0.90f,0.94f);
        glColor3f(1,1,1);
        drawTextCentered(0,0.86f,"AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH (AIUB)",
                         GLUT_BITMAP_HELVETICA_18);

        // Project title
        glColor3f(0,0,0);
        drawTextCentered(0,0.70f,"COMPUTER GRAPHICS",GLUT_BITMAP_TIMES_ROMAN_24);
        drawTextCentered(0,0.63f,"Project",GLUT_BITMAP_HELVETICA_18);

        // Submitted By (single)
        glColor3f(0,0,0);
        drawTextCentered(0,0.50f,"Submitted By",GLUT_BITMAP_HELVETICA_18);
        glColor3f(0.5f,0.5f,0.7f);
        glBegin(GL_LINES);
        glVertex2f(-0.30f,0.485f); glVertex2f(0.30f,0.485f);
        glEnd();

        // Single author row
        float tY = 0.42f;
        glColor3f(0.1f,0.1f,0.3f);
        fillRect(-0.55f,tY,0.55f,tY+0.04f);
        glColor3f(1,1,1);
        drawText(-0.51f,tY+0.014f,"Name",GLUT_BITMAP_HELVETICA_12);
        drawText( 0.20f,tY+0.014f,"Student ID",GLUT_BITMAP_HELVETICA_12);

        glColor3f(0.94f,0.94f,0.97f);
        fillRect(-0.55f,tY-0.07f,0.55f,tY-0.005f);
        glColor3f(0,0,0);
        drawText(-0.51f,tY-0.045f,studentName,GLUT_BITMAP_HELVETICA_12);
        drawText( 0.20f,tY-0.045f,studentID,  GLUT_BITMAP_HELVETICA_12);

        glColor3f(0.3f,0.3f,0.5f);
        drawRect(-0.55f,tY-0.07f,0.55f,tY+0.04f);
        glBegin(GL_LINES);
        glVertex2f(0.16f,tY-0.07f); glVertex2f(0.16f,tY+0.04f);
        glEnd();

        // Submitted To
        float stY = -0.10f;
        glColor3f(0,0,0);
        drawTextCentered(0,stY,"Submitted To",GLUT_BITMAP_HELVETICA_18);
        drawTextCentered(0,stY-0.06f,"Mahfujur Rahman",GLUT_BITMAP_HELVETICA_12);
        drawTextCentered(0,stY-0.10f,"Assistant Professor, Computer Science",GLUT_BITMAP_HELVETICA_12);
        drawTextCentered(0,stY-0.14f,"Section: G  |  CSE",GLUT_BITMAP_HELVETICA_12);

        // Date + hint
        glColor3f(0,0,0);
        drawTextCentered(0,-0.60f,"Date of Submission: May 7, 2026",GLUT_BITMAP_HELVETICA_12);

        glColor3f(0.2f,0.2f,0.5f);
        drawTextCentered(0,-0.85f,"Press ENTER or SPACE to view Scenarios",
                         GLUT_BITMAP_HELVETICA_18);

        glutSwapBuffers();
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  PAGE 1 – INSTRUCTIONS  (5 scenarios, no student names)
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
    // Descriptive scene names — no student names
    static Scene scenes[5]={
        {"Coastal Village",
         "P=Play music.wav  S=Stop  N=Day/Night  Esc=Back",
         "No mouse interaction",
         "music.wav (loop; P=play S=stop)",
         "No collision detection",'1',0.85f,0.90f,1.00f},
        {"Historical Dhaka",
         "P=Pause  N=Day/Night  R=Rain  M=Music",
         "No mouse interaction",
         "bg.wav (loop; M to toggle)",
         "No collision detection",'2',0.85f,1.00f,0.85f},
        {"Train Station",
         "S=Signal  Space=Pause  Arrows=TrainSpd  M/U=Mute",
         "Left=Toggle Signal  Right=Pause",
         "Train_Sound.wav",
         "People 0&1 walk toward each other",'3',1.00f,0.85f,0.85f},
        {"Modern City",
         "S=Signal  Space=Pause  Arrows=Speed  N=Night  M/U=Mute",
         "Left=Toggle Signal  Right=Pause",
         "vehicle.wav (optional)",
         "Person index 7 (red flag) moves slower",'4',1.00f,0.98f,0.80f},
        {"Futuristic City",
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
        drawText("SCENARIOS",-0.918f,0.858f,0.048f,0.15f,0.15f,0.20f);

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
}

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 2 – Coastal Village
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneAfia {
    float animTime=0,boat1X=-0.48f,boat2X=0.05f,boat3X=0.55f,birdX=-1.2f,birdY=0.75f;
    static bool nightMode=false;
    static float fishTimer=0;
    struct Butterfly { float x,y,phase,speed,r,g,b; };
    static Butterfly butterflies[6] = {
        {-0.40f,-0.02f,0,0.9f, 1.0f,0.55f,0.10f},
        { 0.20f,-0.04f,1,1.1f, 0.95f,0.85f,0.15f},
        { 0.55f,-0.03f,2,0.8f, 0.35f,0.70f,1.00f},
        {-0.15f, 0.00f,3,1.0f, 0.90f,0.30f,0.70f},
        { 0.75f,-0.05f,4,1.2f, 0.40f,0.90f,0.30f},
        {-0.65f,-0.03f,5,0.9f, 1.00f,0.65f,0.40f},
    };
    struct Fish { float x,y,t; bool active; };
    static Fish fish[3] = {{0,0,0,false},{0,0,0,false},{0,0,0,false}};
    struct Seagull { float x,y,s,phase; };
    static Seagull gulls[4] = {
        {-0.60f,0.60f,1.0f,0.0f},{-0.35f,0.66f,0.9f,1.2f},
        { 0.25f,0.58f,1.1f,2.3f},{ 0.55f,0.63f,0.95f,3.4f},
    };
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
    void drawMoon(){
        drawFilledCircle(0.62f,0.82f,0.055f,0.95f,0.95f,1);
        drawFilledCircle(0.65f,0.84f,0.050f,0.05f,0.06f,0.15f);
    }
    void drawStar5(float cx,float cy,float r,float alpha){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1,1,0.85f,alpha);
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int i=0;i<=10;i++){
            float a=i*PI/5.0f - PI/2.0f;
            float rr=(i%2==0)?r:r*0.45f;
            glVertex2f(cx+rr*cosf(a),cy+rr*sinf(a));
        }
        glEnd();
        glDisable(GL_BLEND);
    }
    void drawSeagull(const Seagull& s){
        glColor3f(0.92f,0.92f,0.95f); glLineWidth(2.5f);
        float flap = sinf(animTime*6 + s.phase) * 0.02f * s.s;
        glBegin(GL_LINE_STRIP);
        glVertex2f(s.x-0.05f*s.s, s.y+0.02f*s.s+flap);
        glVertex2f(s.x,          s.y);
        glVertex2f(s.x+0.05f*s.s, s.y+0.02f*s.s+flap);
        glEnd();
        glColor3f(0.75f,0.75f,0.78f); glLineWidth(1.5f);
        glBegin(GL_LINES);
        glVertex2f(s.x-0.02f*s.s, s.y+0.01f*s.s+flap*0.5f);
        glVertex2f(s.x+0.02f*s.s, s.y+0.01f*s.s+flap*0.5f);
        glEnd();
        glLineWidth(1);
    }
    void drawButterfly(const Butterfly& b){
        float t = animTime*3 + b.phase;
        float x = b.x + sinf(t)*0.04f;
        float y = b.y + sinf(t*1.7f)*0.03f;
        float wing = 0.010f + 0.010f*fabsf(sinf(t*8));
        glColor3f(b.r,b.g,b.b);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y); glVertex2f(x - wing, y + wing*1.4f); glVertex2f(x - wing*0.6f, y - wing*0.8f);
        glVertex2f(x, y); glVertex2f(x + wing, y + wing*1.4f); glVertex2f(x + wing*0.6f, y - wing*0.8f);
        glEnd();
        glColor3f(0.15f,0.15f,0.15f);
        glBegin(GL_LINES); glVertex2f(x, y+0.004f); glVertex2f(x, y-0.004f); glEnd();
    }
    void drawFish(const Fish& f){
        if(!f.active) return;
        glPushMatrix(); glTranslatef(f.x, f.y, 0);
        glColor3f(0.95f,0.55f,0.20f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0,0); glVertex2f(0.025f,0.008f); glVertex2f(0.025f,-0.008f);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.020f,0); glVertex2f(-0.008f,0.010f); glVertex2f(-0.008f,-0.010f);
        glEnd();
        glPopMatrix();
    }
    void drawWaterSparkle(float t){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for(int i=0;i<25;i++){
            float x = -0.9f + fmodf(i*0.073f + t*0.05f, 1.8f);
            float y = -0.22f - fmodf(i*0.031f + t*0.02f, 0.28f);
            float a = 0.35f + 0.65f*fabsf(sinf(t*2 + i));
            glColor4f(1,1,1,a*0.7f);
            glBegin(GL_QUADS);
            glVertex2f(x-0.003f,y); glVertex2f(x+0.003f,y);
            glVertex2f(x+0.003f,y+0.003f); glVertex2f(x-0.003f,y+0.003f);
            glEnd();
        }
        glDisable(GL_BLEND);
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
        glClear(GL_COLOR_BUFFER_BIT); glLoadIdentity();
        drawRect(-1,-1,1,1,0.97f,0.96f,0.92f);
        if(nightMode){
            glColor3f(0.05f,0.06f,0.15f);
            glBegin(GL_QUADS);
            glVertex2f(-1,1); glVertex2f(1,1); glVertex2f(1,-0.18f); glVertex2f(-1,-0.18f);
            glEnd();
            for(int i=0;i<40;i++){
                float x = -0.98f + fmodf(i*0.049f, 1.96f);
                float y = -0.15f + fmodf(i*0.083f, 1.10f);
                float a = 0.4f + 0.6f*fabsf(sinf(animTime + i));
                drawStar5(x,y,0.006f + (i%3)*0.002f, a);
            }
            drawMoon();
        } else {
            drawFilledCircle(-0.20f,0.55f,0.09f,1,1,1);
            drawFilledCircle(-0.08f,0.58f,0.07f,1,1,1);
            drawFilledCircle(0.04f,0.54f,0.06f,1,1,1);
            drawFilledCircle(0.30f,0.62f,0.08f,1,1,1);
            drawFilledCircle(0.40f,0.65f,0.06f,1,1,1);
            drawFilledCircle(0.20f,0.60f,0.06f,1,1,1);
            drawSun(-0.52f,0.70f);
        }
        drawBird(birdX,birdY);
        for(int i=0;i<4;i++) drawSeagull(gulls[i]);
        drawFilledCircle(0.10f,-0.02f,0.28f,0.25f,0.60f,0.15f);
        drawRect(-1,-0.18f,1,0.02f,0.88f,0.76f,0.38f);
        drawRect(-1,-0.55f,1,-0.18f,0.18f,0.62f,0.85f);
        glColor3f(0.30f,0.72f,0.92f); glLineWidth(1.5f);
        for(float wy=-0.25f;wy>-0.52f;wy-=0.06f){
            glBegin(GL_LINE_STRIP);
            for(float wx=-0.9f;wx<0.9f;wx+=0.08f) glVertex2f(wx,wy+0.008f*sinf(wx*12+animTime*3));
            glEnd();
        }

}

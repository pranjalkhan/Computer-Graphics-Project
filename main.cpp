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
        glLineWidth(1);
        drawWaterSparkle(animTime);
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
        drawPerson(-0.60f,-0.16f,0.10f,0.30f,0.70f);
        drawPerson(-0.55f,-0.16f,0.20f,0.30f,0.70f);
        drawPerson(-0.30f,-0.16f,0.10f,0.30f,0.70f);
        drawPerson(0.52f,-0.16f,0.10f,0.30f,0.70f);
        drawPerson(0.58f,-0.16f,0.20f,0.40f,0.65f);
        for(int i=0;i<3;i++) drawFish(fish[i]);
        for(int i=0;i<6;i++) drawButterfly(butterflies[i]);
        glPushMatrix(); glTranslatef(boat1X,-0.32f,0); drawBoat(0,0,1,0.90f,0.70f,0.05f,0.45f,0.25f,0.05f); glPopMatrix();
        glPushMatrix(); glTranslatef(boat2X,-0.30f,0); drawBoat(0,0,1,0.95f,0.95f,0.90f,0.45f,0.25f,0.05f); glPopMatrix();
        glPushMatrix(); glTranslatef(boat3X,-0.34f,0); drawBoat(0,0,0.85f,0.88f,0.68f,0.05f,0.42f,0.22f,0.04f); glPopMatrix();
        glColor3f(0.2f,0.2f,0.5f);
        glRasterPos2f(-0.95f,-0.92f);
        const char* hint="P=Play Sound  S=Stop  N=Day/Night  ESC=Back";
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
        for(int i=0;i<4;i++){ gulls[i].x += 0.003f*(0.7f + i*0.1f); if(gulls[i].x > 1.3f) gulls[i].x = -1.3f; }
        fishTimer += 0.016f;
        if(fishTimer > 2.5f){
            fishTimer = 0;
            for(int i=0;i<3;i++){
                if(!fish[i].active){
                    fish[i].x = -0.7f + (rand()%140)*0.01f;
                    fish[i].y = -0.20f; fish[i].t = 0; fish[i].active = true; break;
                }
            }
        }
        for(int i=0;i<3;i++){
            if(!fish[i].active) continue;
            fish[i].t += 0.016f;
            fish[i].y = -0.20f + 0.20f*sinf(fish[i].t*3) - 0.10f*fish[i].t;
            fish[i].x += 0.008f;
            if(fish[i].t > 0.9f || fish[i].y < -0.35f) fish[i].active = false;
        }
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
        if(key=='n'||key=='N') nightMode = !nightMode;
    }
    void reset(){
        animTime=0; boat1X=-0.48f; boat2X=0.05f; boat3X=0.55f; birdX=-1.2f;
        nightMode=false; fishTimer=0;
        for(int i=0;i<3;i++) fish[i].active=false;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 3 – Historical Dhaka
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneSayeed {
#define S_NUM_CLOUDS 5
#define S_NUM_PEOPLE 4
#define S_NUM_RAINS  300
#define S_NUM_BIRDS_S 8
    bool cloudsPaused=false, isNight=false, musicEnabled=false, rainEnabled=false;
    struct Rain{ float x,y,speed; };
    Rain g_rain[S_NUM_RAINS];
    struct Cloud{ float baseX,baseY,offsetX,speed,scale; };
    struct Person2{ float x,y,scale,sr,sg,sb,pr,pg,pb,skr,skg,skb; };
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
    struct BirdS { float x,y,speed,phase,r,g,b; };
    static BirdS g_birdsS[S_NUM_BIRDS_S];
    struct SmokePuff { float x,y,vy,alpha,r; bool active; };
    static SmokePuff g_puffs[40];
    void initBirds(){
        for(int i=0;i<S_NUM_BIRDS_S;i++){
            g_birdsS[i].x = -1.2f + (float)i*0.30f;
            g_birdsS[i].y = 0.70f + (float)(rand()%100)/100.0f * 0.15f;
            g_birdsS[i].speed = 0.0006f + (float)(rand()%100)/100.0f*0.0004f;
            g_birdsS[i].phase = (float)i * 1.3f;
            g_birdsS[i].r = 0.30f; g_birdsS[i].g = 0.30f; g_birdsS[i].b = 0.35f;
        }
    }
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
    void drawMoonS(){
        glColor3f(0.92f,0.92f,1); fc(0.75f,0.82f,0.075f,40);
        glColor3f(0.02f,0.02f,0.08f); fc(0.78f,0.85f,0.070f,40);
    }
    void drawStarsS(){
        for(int i=0;i<50;i++){
            float x = -0.98f + fmodf(i*0.041f, 1.96f);
            float y =  0.28f + fmodf(i*0.071f, 0.68f);
            float a = 0.4f + 0.6f*fabsf(sinf(i*0.7f + (float)(clock())/1000.0f));
            glColor3f(a,a,a*0.9f);
            glPointSize(2); glBegin(GL_POINTS); glVertex2f(x,y); glEnd();
        }
        glPointSize(1);
    }
    void drawSunS(){
        if(!isNight){
            glColor3f(1,0.92f,0.30f); glLineWidth(2);
            glBegin(GL_LINES);
            for(int i=0;i<12;i++){
                float a = i*PI/6.0f + (float)(clock())/2000.0f;
                glVertex2f(0.75f+0.10f*cosf(a), 0.80f+0.10f*sinf(a));
                glVertex2f(0.75f+0.15f*cosf(a), 0.80f+0.15f*sinf(a));
            }
            glEnd(); glLineWidth(1);
            glColor3f(1,0.95f,0.35f); fc(0.75f,0.80f,0.08f,40);
        } else { drawMoonS(); drawStarsS(); }
    }
    void drawBirdS(const BirdS& b){
        float flap = sinf(b.phase + (float)(clock())/800.0f) * 0.015f;
        glColor3f(b.r, b.g, b.b); glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        glVertex2f(b.x-0.03f, b.y+0.012f+flap);
        glVertex2f(b.x,       b.y);
        glVertex2f(b.x+0.03f, b.y+0.012f+flap);
        glEnd(); glLineWidth(1);
    }
    void drawLampS(float x, float y){
        glColor3f(0.30f,0.25f,0.20f); sq(x-0.004f, y, x+0.004f, y+0.15f);
        glColor3f(0.55f,0.40f,0.10f); sq(x-0.018f, y+0.13f, x+0.018f, y+0.17f);
        if(isNight){
            glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1,0.9f,0.4f,0.35f); fc(x, y+0.145f, 0.045f, 18);
            glDisable(GL_BLEND);
            glColor3f(1,0.92f,0.5f); fc(x, y+0.145f, 0.012f, 12);
        } else { glColor3f(0.85f,0.75f,0.35f); fc(x, y+0.145f, 0.012f, 12); }
    }
    void drawHorseCart(float x, float y, float s){
        glColor3f(0.30f,0.20f,0.10f);
        fc(x-0.04f*s, y+0.02f*s, 0.022f*s, 16); fc(x+0.04f*s, y+0.02f*s, 0.022f*s, 16);
        glColor3f(0.55f,0.40f,0.20f);
        fc(x-0.04f*s, y+0.02f*s, 0.012f*s, 12); fc(x+0.04f*s, y+0.02f*s, 0.012f*s, 12);
        glColor3f(0.55f,0.35f,0.15f); sq(x-0.06f*s, y+0.04f*s, x+0.06f*s, y+0.10f*s);
        glColor3f(0.35f,0.20f,0.10f);
        sq(x+0.08f*s, y+0.05f*s, x+0.18f*s, y+0.10f*s);
        sq(x+0.16f*s, y+0.09f*s, x+0.20f*s, y+0.14f*s);
        sq(x+0.08f*s, y+0.0f, x+0.10f*s, y+0.05f*s);
        sq(x+0.16f*s, y+0.0f, x+0.18f*s, y+0.05f*s);
    }
    void spawnChimneySmoke(){
        for(int i=0;i<40;i++){
            if(!g_puffs[i].active){
                g_puffs[i].x = -0.90f + 0.30f*0.70f;
                g_puffs[i].y = 0.62f; g_puffs[i].vy = 0.0015f;
                g_puffs[i].alpha = 0.8f; g_puffs[i].r = 0.04f;
                g_puffs[i].active = true; break;
            }
        }
    }
    void drawPuffs(){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        for(int i=0;i<40;i++){
            if(!g_puffs[i].active) continue;
            glColor4f(0.55f,0.55f,0.55f, g_puffs[i].alpha);
            fc(g_puffs[i].x, g_puffs[i].y, g_puffs[i].r, 16);
        }
        glDisable(GL_BLEND);
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
        glClear(GL_COLOR_BUFFER_BIT); glLoadIdentity();
        drawBackground(); drawSunS(); drawRain();
        for(int i=0;i<S_NUM_CLOUDS;i++) drawCloud(g_clouds[i]);
        drawTree(-0.95f,0.20f,1.1f); drawTree(0.90f,0.20f,1.0f);
        drawBuilding2(-0.90f,0.05f,0.30f,0.30f); drawBuilding2(0.60f,0.08f,0.28f,0.25f);
        drawMainBuildingS();
        for(int i=0;i<S_NUM_BIRDS_S;i++) drawBirdS(g_birdsS[i]);
        drawHorseCart(-0.78f, -0.38f, 1.2f);
        drawLampS(-0.35f,-0.55f); drawLampS(0.35f,-0.55f); drawLampS(-0.75f,-0.45f);
        spawnChimneySmoke();
        drawPuffs();
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
        for(int i=0;i<S_NUM_BIRDS_S;i++){
            g_birdsS[i].x += g_birdsS[i].speed;
            if(g_birdsS[i].x > 1.3f) g_birdsS[i].x = -1.3f;
        }
        for(int i=0;i<40;i++){
            if(!g_puffs[i].active) continue;
            g_puffs[i].y += g_puffs[i].vy;
            g_puffs[i].r += 0.0003f;
            g_puffs[i].alpha -= 0.004f;
            if(g_puffs[i].alpha <= 0) g_puffs[i].active = false;
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
    void reset(){
        cloudsPaused=false; isNight=false; rainEnabled=false; musicEnabled=false;
        initBirds();
        for(int i=0;i<40;i++) g_puffs[i].active=false;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 4 – Train Station
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneAbrar {
#define AB_MAX_SMOKE 300
#define AB_NUM_PEOPLE 9
#define AB_FLOCK 7
    bool g_soundMuted=false, g_paused=false;
    int  g_signal=1, g_frame=0, g_winWidth=1100, g_winHeight=650;
    int  g_signalFlash=0; float g_flashIntensity=0;
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
    void qd(float x1,float y1,float x2,float y2){
        glBegin(GL_QUADS); glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2); glEnd();
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
                float rv=0.014f+(float)rand()/RAND_MAX*0.028f;
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
    void drawHills(){
        glColor3f(0.42f,0.55f,0.42f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,-0.10f); glVertex2f(-0.70f,0.18f); glVertex2f(-0.40f,-0.10f);
        glVertex2f(-0.55f,-0.10f); glVertex2f(-0.28f,0.12f); glVertex2f(-0.05f,-0.10f);
        glEnd();
        glColor3f(0.32f,0.45f,0.32f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,-0.10f); glVertex2f(-0.82f,0.10f); glVertex2f(-0.60f,-0.10f);
        glEnd();
    }
    void drawCrate(float x, float y, float s){
        glColor3f(0.55f,0.35f,0.15f); qd(x,y,x+0.05f*s,y+0.04f*s);
        glColor3f(0.40f,0.25f,0.10f); qd(x,y+0.04f*s,x+0.05f*s,y+0.045f*s);
        glColor3f(0.40f,0.25f,0.10f); glLineWidth(1.5f);
        glBegin(GL_LINES);
        glVertex2f(x,y); glVertex2f(x+0.05f*s,y+0.04f*s);
        glVertex2f(x,y+0.04f*s); glVertex2f(x+0.05f*s,y);
        glEnd(); glLineWidth(1);
    }
    void drawBarrel(float x, float y, float s){
        glColor3f(0.42f,0.28f,0.14f);
        glBegin(GL_QUADS);
        glVertex2f(x+0.008f*s,y); glVertex2f(x+0.032f*s,y);
        glVertex2f(x+0.028f*s,y+0.045f*s); glVertex2f(x+0.012f*s,y+0.045f*s);
        glEnd();
        glColor3f(0.25f,0.18f,0.10f);
        qd(x+0.005f*s,y+0.015f*s,x+0.035f*s,y+0.020f*s);
        qd(x+0.007f*s,y+0.035f*s,x+0.033f*s,y+0.040f*s);
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
        glColor3f(0.65f,0.18f,0.06f); qd(tx+0.73f,-0.38f,tx+1.03f,-0.38f+0.25f);
        glColor3f(0.38f,0.40f,0.42f); qd(tx+0.725f,-0.38f+0.25f,tx+1.035f,-0.38f+0.275f);
        glColor3f(0.72f,0.22f,0.07f); qd(tx+0.39f,-0.37f,tx+0.73f,-0.37f+0.26f);
        glColor3f(0.36f,0.38f,0.42f); qd(tx+0.385f,-0.37f+0.26f,tx+0.735f,-0.37f+0.288f);
        for(int w=0;w<6;w++){
            float wx=tx+0.407f+w*0.050f,wy=-0.37f+0.045f;
            glColor3f(0.62f,0.76f,0.88f); qd(wx,wy,wx+0.038f,wy+0.075f);
        }
        glColor3f(0.14f,0.14f,0.17f); qd(tx+0.17f,-0.35f,tx+0.39f,-0.14f);
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
    void drawBirdAB(float x,float y,float dir,float r,float g,float b){
        float facing=(dir>0)?1:-1;
        glPushMatrix(); glTranslatef(x,y,0);
        if(facing<0) glScalef(-1,1,1);
        glColor3f(r,g,b); fe(0,0,0.040f,0.028f,20);
        glColor3f(r*0.85f,g*0.85f,b*0.85f); fc(0.048f,0.012f,0.022f,16);
        glColor3f(1,0.65f,0.15f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.068f,0.014f); glVertex2f(0.088f,0.008f); glVertex2f(0.068f,0.002f);
        glEnd();
        glColor3f(0,0,0); fc(0.060f,0.018f,0.004f,8);
        glPopMatrix();
    }
    void initFlock(){
        for(int i=0;i<AB_FLOCK;i++){
            g_flock[i].x=-1.2f+(float)i*0.25f;
            g_flock[i].y=0.68f+((float)rand()/RAND_MAX)*0.18f;
            g_flock[i].speed=0.0003f+((float)rand()/RAND_MAX)*0.0005f;
            float ch=(float)rand()/RAND_MAX;
            if(ch<0.33f){g_flock[i].r=0.55f;g_flock[i].g=0.40f;g_flock[i].b=0.25f;}
            else if(ch<0.66f){g_flock[i].r=0.40f;g_flock[i].g=0.45f;g_flock[i].b=0.55f;}
            else{g_flock[i].r=0.65f;g_flock[i].g=0.35f;g_flock[i].b=0.30f;}
        }
    }
    void initPeople(){
        for(int i=0;i<AB_NUM_PEOPLE;i++){
            g_people[i].offsetX=0; g_people[i].speed=0.0001f+((float)rand()/RAND_MAX)*0.00015f;
            if(g_people[i].dir==0) g_people[i].dir=1;
        }
    }
    void render(){
        glClear(GL_COLOR_BUFFER_BIT); glLoadIdentity();
        drawBackground();
        drawHills();
        drawSunAB();
        for(int i=0;i<6;i++) drawCloud(g_cloudX[i],g_cloudY[i]);
        glColor3f(0.62f,0.65f,0.70f); qd(-1,-0.10f,-0.92f,0.30f);
        glColor3f(0.56f,0.60f,0.64f); qd(-0.92f,-0.10f,-0.85f,0.22f);
        drawFactory(-0.72f,-0.10f);
        drawBuilding(-0.98f,-0.10f,0.26f,0.42f,0.72f,0.30f,0.14f,0.52f,0.18f,0.07f,2,2,false,false);
        drawBuilding(-0.50f,-0.10f,0.24f,0.52f,0.78f,0.38f,0.16f,0.55f,0.22f,0.08f,3,2,true, false);
        drawBuilding(-0.24f,-0.10f,0.28f,0.58f,0.82f,0.65f,0.28f,0.58f,0.42f,0.14f,3,2,false,false);
        drawStationHouse(-0.02f,-0.10f);
        drawBuilding(0.20f,-0.10f,0.22f,0.44f,0.80f,0.68f,0.32f,0.56f,0.44f,0.16f,2,2,false,false);
        drawBuilding(0.44f,-0.10f,0.20f,0.40f,0.66f,0.56f,0.36f,0.44f,0.36f,0.18f,2,2,false,true);
        drawBuilding(0.66f,-0.10f,0.26f,0.46f,0.72f,0.66f,0.44f,0.48f,0.44f,0.24f,3,2,false,false);
        glColor3f(0.76f,0.42f,0.22f); qd(-1,-0.14f,1,-0.10f);
        drawTreeAB(-0.98f,-0.10f,1.1f); drawTreeAB(-0.93f,-0.10f,0.95f); drawTreeAB(0.86f,-0.10f,1); drawTreeAB(0.91f,-0.10f,0.9f);
        float lampX[]={-0.62f,-0.30f,0.05f,0.38f,0.70f};
        for(int i=0;i<5;i++) drawLampAB(lampX[i],-0.40f);
        drawSignalAB();
        drawTracks();
        drawCrate(-0.85f,-0.395f,1.4f); drawCrate(-0.82f,-0.395f,1.0f);
        drawBarrel(-0.42f,-0.395f,1.6f); drawBarrel(0.05f,-0.395f,1.4f);
        drawCrate(0.78f,-0.395f,1.3f);
        for(int i=0;i<AB_NUM_PEOPLE;i++){
            const ABPerson& p=g_people[i];
            if(p.baseY>-0.50f){ glPushMatrix(); glTranslatef(p.baseX+p.offsetX,p.baseY,0); drawOnePerson(p); glPopMatrix(); }
        }
        drawTrainWheels();
        for(int i=0;i<AB_FLOCK;i++) drawBirdAB(g_flock[i].x,g_flock[i].y,1,g_flock[i].r,g_flock[i].g,g_flock[i].b);
        for(int i=0;i<AB_NUM_PEOPLE;i++){
            const ABPerson& p=g_people[i];
            if(p.baseY<=-0.50f){ glPushMatrix(); glTranslatef(p.baseX+p.offsetX,p.baseY,0); drawOnePerson(p); glPopMatrix(); }
        }
        drawSmoke(); drawTrain();
        glColor3f(0.2f,0.2f,0.5f);
        glRasterPos2f(-0.95f,-0.92f);
        const char* hint="S=Signal  SPACE=Pause  Arrows=TrainSpd  M=Mute  U=Unmute  ESC=Back";
        for(const char* c=hint;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*c);
        glutSwapBuffers();
    }
    void update(){
        if(!g_paused){
            g_frame++;
            if(g_signal==1){
                g_trainX+=g_trainSpeed; if(g_trainX>1) g_trainX-=2; if(g_trainX<-1) g_trainX+=2;
                g_wheelAngle-=1.2f; g_pistonPhase+=0.03f;
            }
            g_sunAngle+=0.00012f;
            for(int i=0;i<6;i++){ g_cloudX[i]+=g_cloudSp[i]; if(g_cloudX[i]>1.6f) g_cloudX[i]=-1.6f; }
            updateSmoke();
            if(g_frame%2==0){
                float skx=g_trainX-0.30f+0.32f*0.20f,sky=-0.285f+0.105f+0.080f;
                spawnSmoke(skx,sky,true);
                if(g_frame%3==0) spawnSmoke(skx+0.005f,sky-0.010f,false);
            }
            for(int i=0;i<AB_NUM_PEOPLE;i++){
                ABPerson& p=g_people[i]; p.offsetX+=p.speed*p.dir;
                float wx=p.baseX+p.offsetX;
                if(wx>0.85f){wx=-0.85f;p.offsetX=wx-p.baseX;}
                else if(wx<-0.85f){wx=0.85f;p.offsetX=wx-p.baseX;}
            }
            float wx0=g_people[0].baseX+g_people[0].offsetX;
            float wx1=g_people[1].baseX+g_people[1].offsetX;
            if(fabsf(wx0-wx1)<0.12f){
                g_people[0].dir*=-1; g_people[1].dir*=-1;
                if(wx0<wx1){g_people[0].offsetX-=0.005f;g_people[1].offsetX+=0.005f;}
                else{g_people[0].offsetX+=0.005f;g_people[1].offsetX-=0.005f;}
            }
            for(int i=0;i<AB_FLOCK;i++){
                g_flock[i].x+=g_flock[i].speed;
                if(g_flock[i].x>1.25f){ g_flock[i].x=-1.25f; g_flock[i].y=0.68f+((float)rand()/RAND_MAX)*0.18f; }
            }
        }
    }
    void keyboard(unsigned char key,int,int){
        if(key=='s'||key=='S'){ g_signal=!g_signal; g_signalFlash=15; g_flashIntensity=1; }
        if(key==' ') g_paused=!g_paused;
        if(key=='m'||key=='M'){ if(!g_soundMuted){ g_soundMuted=true;
#ifdef _WIN32
            PlaySound(NULL,NULL,0);
#endif
        }}
        if(key=='u'||key=='U'){ if(g_soundMuted){ g_soundMuted=false;
#ifdef _WIN32
            PlaySound("Train_Sound.wav",NULL,SND_ASYNC|SND_LOOP|SND_FILENAME);
#endif
        }}
    }
    void specialKeys(int key,int,int){
        if(key==GLUT_KEY_UP){ g_trainSpeed+=0.0001f; if(g_trainSpeed>0.0020f) g_trainSpeed=0.0020f; }
        if(key==GLUT_KEY_DOWN){ g_trainSpeed-=0.0001f; if(g_trainSpeed<0.0001f) g_trainSpeed=0.0001f; }
    }
    void mouseFunc(int button,int state,int,int){
        if(state==GLUT_DOWN){
            if(button==GLUT_LEFT_BUTTON){ g_signal=!g_signal; g_signalFlash=15; g_flashIntensity=1; }
            if(button==GLUT_RIGHT_BUTTON) g_paused=!g_paused;
        }
    }
    void reset(){
        g_paused=false; g_signal=1; g_trainX=-0.3f; g_wheelAngle=0; g_pistonPhase=0;
        g_sunAngle=-0.3f; g_frame=0; g_signalFlash=0;
        initSmoke(); initFlock(); initPeople();
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 5 – Modern City
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneRafid {
#define RF_NUM_VEHICLES 10
#define RF_NUM_PEOPLE 8
#define RF_COLLIDE 0.065f
#define RF_NUM_BIRDS 6
    int   g_paused=0, g_signal=1, g_muted=0, g_frame=0;
    float g_metroX=-0.30f, g_metroSpeed=0.0004f, g_sunAngle=-0.3f, g_roadSpeedMult=1;
    float g_cloudX[5]={-0.70f,0,0.50f,-0.20f,0.80f};
    float g_cloudY[5]={0.78f,0.86f,0.80f,0.90f,0.73f};
    float g_cloudSp[5]={0.00008f,0.00006f,0.00010f,0.00005f,0.00009f};
    static float g_timeRF=0;
    static bool g_nightRF=false;
    struct RFBird { float x,y,phase,speed; };
    static RFBird g_birdsRF[RF_NUM_BIRDS];
    struct RFVehicle{ float baseX,baseY,offsetX,speed,originalSpeed,dir,r,g,b,r2,g2,b2; int type; };
    struct RFPerson{ float baseX,baseY,offsetX,speed,dir,scale,sr,sg,sb,pr,pg,pb,skr,skg,skb; int wave; };
    RFVehicle g_vehicles[RF_NUM_VEHICLES];
    RFPerson  g_people[RF_NUM_PEOPLE];
    void dq(float x1,float y1,float x2,float y2){ glBegin(GL_QUADS); glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2); glEnd(); }
    void dc(float cx,float cy,float r,int s){ glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy); for(int i=0;i<=s;i++){float a=i*2*PI/s;glVertex2f(cx+r*cosf(a),cy+r*sinf(a));} glEnd(); }
    void de(float cx,float cy,float rx,float ry,int s){ glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy); for(int i=0;i<=s;i++){float a=i*2*PI/s;glVertex2f(cx+rx*cosf(a),cy+ry*sinf(a));} glEnd(); }
    void initBirdsRF(){
        for(int i=0;i<RF_NUM_BIRDS;i++){
            g_birdsRF[i].x = -1.2f + i*0.4f;
            g_birdsRF[i].y = 0.55f + (rand()%100)/100.0f*0.2f;
            g_birdsRF[i].phase = (float)i*1.1f;
            g_birdsRF[i].speed = 0.0008f + (rand()%100)/100.0f*0.0005f;
        }
    }
    void drawBirdRF(const RFBird& b){
        float flap = sinf(g_timeRF*6 + b.phase)*0.012f;
        glColor3f(0.20f,0.22f,0.28f); glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        glVertex2f(b.x-0.028f, b.y+0.010f+flap);
        glVertex2f(b.x, b.y);
        glVertex2f(b.x+0.028f, b.y+0.010f+flap);
        glEnd(); glLineWidth(1);
    }
    void drawStarsRF(){
        for(int i=0;i<60;i++){
            float x = -0.98f + fmodf(i*0.037f, 1.96f);
            float y =  0.30f + fmodf(i*0.061f, 0.66f);
            float a = 0.4f + 0.6f*fabsf(sinf(g_timeRF + i*0.7f));
            glColor3f(a,a,a);
            glPointSize(2); glBegin(GL_POINTS); glVertex2f(x,y); glEnd();
        }
        glPointSize(1);
    }
    void drawBillboard(float x,float y,float w,float h,float r,float g,float b){
        glColor3f(0.18f,0.18f,0.20f); dq(x-0.004f,y,x+w+0.004f,y+h+0.004f);
        glColor3f(r,g,b); dq(x,y,x+w,y+h);
        glColor3f(1,1,1);
        for(int i=0;i<4;i++) dq(x+w*0.10f, y+h*0.55f - i*h*0.15f, x+w*0.65f, y+h*0.55f - i*h*0.15f + h*0.06f);
        glColor3f(r*0.8f,g*0.8f,b*0.8f); dq(x+w*0.80f, y+h*0.30f, x+w*0.92f, y+h*0.70f);
        glColor3f(0.30f,0.30f,0.32f); dq(x+w*0.48f, y-0.10f, x+w*0.52f, y);
    }
    void drawBackground(){
        glBegin(GL_QUADS);
        glColor3f(0.38f,0.68f,0.95f); glVertex2f(-1,1); glVertex2f(1,1);
        glColor3f(0.62f,0.86f,0.98f); glVertex2f(1,0); glVertex2f(-1,0);
        glEnd();
        glColor3f(0.28f,0.55f,0.22f); dq(-1,-0.1f,1,-0.55f);
        glColor3f(0.28f,0.30f,0.32f); dq(-1,-0.55f,1,-0.87f);
        glColor3f(0.85f,0.85f,0.20f);
        dq(-1,-0.688f,1,-0.682f); dq(-1,-0.696f,1,-0.690f);
        glColor3f(0.9f,0.9f,0.9f);
        for(float dx=-1;dx<1;dx+=0.12f){dq(dx,-0.633f,dx+0.07f,-0.629f);dq(dx,-0.750f,dx+0.07f,-0.746f);}
        glColor3f(0.65f,0.64f,0.62f); dq(-1,-0.87f,1,-1);
        glColor3f(0.8f,0.8f,0.8f); dq(-1,-0.87f,1,-0.862f);
    }
    void drawSunRF(){
        float sx=cosf(g_sunAngle)*0.78f,sy=0.70f+sinf(g_sunAngle)*0.22f;
        glColor3f(1,0.95f,0.55f); dc(sx,sy,0.055f,32);
        glColor3f(1,0.98f,0.75f); dc(sx,sy,0.038f,32);
    }
    void drawCloudRF(float cx,float cy){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1,1,1,0.92f);
        de(cx-0.10f,cy,0.075f,0.045f,20); de(cx+0.10f,cy,0.075f,0.045f,20);
        de(cx,cy,0.085f,0.050f,20); de(cx-0.06f,cy+0.042f,0.065f,0.048f,20);
        de(cx+0.05f,cy+0.048f,0.060f,0.046f,20); de(cx,cy+0.062f,0.055f,0.042f,20);
        glDisable(GL_BLEND);
    }
    void drawTreeRF(float tx,float ty,float s){
        glColor3f(0.42f,0.28f,0.12f); dq(tx-0.012f*s,ty,tx+0.012f*s,ty+0.20f*s);
        glColor3f(0.15f,0.48f,0.12f); dc(tx,ty+0.21f*s,0.075f*s,22);
        glColor3f(0.18f,0.55f,0.14f); dc(tx-0.04f*s,ty+0.18f*s,0.065f*s,20);
        dc(tx+0.04f*s,ty+0.18f*s,0.062f*s,20);
        glColor3f(0.22f,0.60f,0.16f); dc(tx,ty+0.26f*s,0.055f*s,18);
    }
    void drawSkyscraper(float x,float y,float w,float h,float r,float g,float b,float wr,float wg,float wb,int winsX,int winsY){
        glColor3f(r,g,b); dq(x,y,x+w,y+h);
        glColor3f(r*0.75f,g*0.75f,b*0.75f); dq(x-0.004f,y+h,x+w+0.004f,y+h+0.018f);
        float ww=w/(winsX+1)*0.6f,wh=h/(winsY+1)*0.5f;
        float gapX=(w-winsX*ww)/(winsX+1),gapY=(h-winsY*wh)/(winsY+1);
        for(int row=0;row<winsY;row++){
            float wy=y+gapY+row*(wh+gapY);
            for(int col=0;col<winsX;col++){
                float wx=x+gapX+col*(ww+gapX);
                glColor3f(r*0.55f,g*0.60f,b*0.65f); dq(wx-0.002f,wy-0.002f,wx+ww+0.002f,wy+wh+0.002f);
                glColor3f(wr,wg,wb); dq(wx,wy,wx+ww,wy+wh);
            }
        }
    }
    void drawViaduct(){
        glColor3f(0.82f,0.82f,0.80f); dq(-1,-0.115f,1,-0.070f);
        glColor3f(0.70f,0.70f,0.68f); dq(-1,-0.150f,1,-0.115f);
        glColor3f(0.88f,0.88f,0.86f); dq(-1,-0.072f,1,-0.060f);
        glColor3f(0.72f,0.72f,0.70f);
        for(float px=-0.85f;px<1;px+=0.18f){
            dq(px-0.020f,-0.40f,px+0.020f,-0.150f);
            glColor3f(0.65f,0.65f,0.63f); dq(px-0.030f,-0.165f,px+0.030f,-0.150f);
            glColor3f(0.72f,0.72f,0.70f);
        }
    }
    void drawMetro(){
        float tx=g_metroX,ty=-0.114f,h=0.055f,len=0.42f;
        for(int car=0;car<3;car++){
            float cx=tx-car*(len+0.012f);
            glColor3f(0.94f,0.95f,0.96f); dq(cx-len,ty-h,cx,ty);
            glColor3f(0.15f,0.55f,0.75f); dq(cx-len,ty-h,cx,ty-h+0.010f);
            glColor3f(0.10f,0.25f,0.55f); dq(cx-len,ty-h+0.010f,cx,ty);
            glColor3f(0.88f,0.72f,0.12f); dq(cx-len,ty-h+0.010f,cx,ty-h+0.016f);
            glColor3f(0.55f,0.72f,0.85f);
            int nw=7; float ww=(len-0.030f)/nw*0.72f,gap=(len-0.030f-nw*ww)/(nw-1);
            for(int wi=0;wi<nw;wi++){ float wx=cx-len+0.015f+wi*(ww+gap); dq(wx,ty-h+0.018f,wx+ww,ty-0.012f); }
        }
        float fx=g_metroX;
        glColor3f(0.08f,0.20f,0.48f);
        glBegin(GL_TRIANGLES);
        glVertex2f(fx,ty-h); glVertex2f(fx+0.040f,ty-h*0.5f); glVertex2f(fx,ty);
        glEnd();
        glColor3f(1,0.95f,0.70f); dc(fx+0.032f,ty-h+0.014f,0.008f,10);
    }
    void drawBusRF(float x,float y,float dir,float r,float g,float b,float r2,float g2,float b2){
        float w=(dir>0)?0.22f:-0.22f,h=0.090f;
        glColor3f(r,g,b); dq(x,y,x+w,y+h);
        glColor3f(r2,g2,b2); dq(x,y+h-0.010f,x+w,y+h+0.012f);
        glColor3f(0.62f,0.80f,0.88f);
        int nw=5; float ww=fabsf(w)*0.12f,wh=h*0.35f;
        float startX=(dir>0)?x+0.025f:x-0.025f,stepX=(dir>0)?(fabsf(w)-0.06f)/(nw-1):-(fabsf(w)-0.06f)/(nw-1);
        for(int i=0;i<nw;i++){float wx=startX+i*stepX; dq(wx,y+h*0.38f,wx+((dir>0)?ww:-ww),y+h*0.38f+wh);}
        glColor3f(0.12f,0.12f,0.14f); dc(x+w*0.18f,y-0.016f,0.020f,16); dc(x+w*0.78f,y-0.016f,0.020f,16);
        glColor3f(0.38f,0.38f,0.40f); dc(x+w*0.18f,y-0.016f,0.012f,14); dc(x+w*0.78f,y-0.016f,0.012f,14);
    }
    void drawCarRF(float x,float y,float dir,float r,float g,float b){
        float w=(dir>0)?0.13f:-0.13f,h=0.055f;
        glColor3f(r,g,b); dq(x,y,x+w,y+h);
        glColor3f(r*0.85f,g*0.85f,b*0.85f);
        float cs=(dir>0)?x+fabsf(w)*0.18f:x-fabsf(w)*0.18f,ce=(dir>0)?x+fabsf(w)*0.82f:x-fabsf(w)*0.82f;
        dq(cs,y+h,ce,y+h+0.028f);
        glColor3f(0.58f,0.78f,0.90f); dq(cs+((dir>0)?0.005f:-0.005f),y+h+0.003f,ce-((dir>0)?0.005f:-0.005f),y+h+0.025f);
        glColor3f(0.12f,0.12f,0.14f); dc(x+w*0.22f,y-0.013f,0.016f,14); dc(x+w*0.78f,y-0.013f,0.016f,14);
    }
    void drawCNGRF(float x,float y,float dir,float r,float g,float b){
        float w=(dir>0)?0.085f:-0.085f,h=0.058f;
        glColor3f(r,g,b); dq(x,y,x+w,y+h);
        glColor3f(r*0.80f,g*0.80f,b*0.80f); dq(x,y+h,x+w,y+h+0.018f);
        glColor3f(0.12f,0.12f,0.14f); dc(x+w*0.15f,y-0.012f,0.014f,12); dc(x+w*0.80f,y-0.012f,0.014f,12);
    }
    void drawBikeRF(float x,float y,float dir,float r,float g,float b){
        float w=(dir>0)?0.065f:-0.065f;
        glColor3f(r,g,b); glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(x,y+0.010f); glVertex2f(x+w*0.5f,y+0.038f);
        glVertex2f(x+w*0.5f,y+0.038f); glVertex2f(x+w,y+0.010f);
        glVertex2f(x,y+0.010f); glVertex2f(x+w,y+0.010f);
        glEnd(); glLineWidth(1);
        glColor3f(0.15f,0.15f,0.17f); dc(x,y,0.016f,14); dc(x+w,y,0.016f,14);
    }
    void drawVehicleRF(RFVehicle v){
        float wx=v.baseX+v.offsetX;
        if(v.type==0) drawBusRF(wx,v.baseY,v.dir,v.r,v.g,v.b,v.r2,v.g2,v.b2);
        else if(v.type==1) drawCarRF(wx,v.baseY,v.dir,v.r,v.g,v.b);
        else if(v.type==2) drawCNGRF(wx,v.baseY,v.dir,v.r,v.g,v.b);
        else drawBikeRF(wx,v.baseY,v.dir,v.r,v.g,v.b);
    }
    void drawPersonRF(RFPerson p,int isLast){
        float s=p.scale;
        glColor3f(0.10f,0.08f,0.04f);
        de(-0.012f*s,-0.060f*s,0.012f*s,0.006f*s,10);
        de(0.012f*s,-0.060f*s,0.012f*s,0.006f*s,10);
        glColor3f(p.pr,p.pg,p.pb);
        dq(-0.018f*s,-0.058f*s,-0.004f*s,0.015f*s); dq(0.004f*s,-0.058f*s,0.018f*s,0.015f*s);
        glColor3f(p.sr,p.sg,p.sb);
        glBegin(GL_QUADS);
        glVertex2f(-0.022f*s,0.015f*s); glVertex2f(0.022f*s,0.015f*s);
        glVertex2f(0.024f*s,0.078f*s);  glVertex2f(-0.024f*s,0.078f*s);
        glEnd();
        glColor3f(p.skr,p.skg,p.skb); dc(0,0.110f*s,0.026f*s,20);
        glColor3f(0.14f,0.08f,0.02f); dc(0,0.130f*s,0.025f*s,16);
        if(isLast){
            glColor3f(1,0,0); glLineWidth(2);
            glBegin(GL_LINES); glVertex2f(0,0.165f*s); glVertex2f(0,0.140f*s); glEnd();
            glBegin(GL_TRIANGLES);
            glVertex2f(-0.008f*s,0.147f*s); glVertex2f(0,0.132f*s); glVertex2f(0.008f*s,0.147f*s);
            glEnd();
        }
    }
    void drawTrafficSignalRF(){
        float sx=0.22f,sy=-0.580f;
        glColor3f(0.35f,0.35f,0.38f); dq(sx-0.006f,sy-0.20f,sx+0.006f,sy);
        glColor3f(0.12f,0.12f,0.14f); dq(sx-0.022f,sy,sx+0.022f,sy+0.080f);
        if(g_signal==0) glColor3f(1,0.10f,0.10f); else glColor3f(0.20f,0,0);
        dc(sx,sy+0.062f,0.013f,14);
        if(g_signal==1) glColor3f(0.10f,1,0.22f); else glColor3f(0,0.18f,0.04f);
        dc(sx,sy+0.030f,0.013f,14);
    }
    void drawLampRF(float x,float y){
        glColor3f(0.42f,0.42f,0.45f); dq(x-0.005f,y,x+0.005f,y+0.24f);
        glColor3f(1,0.95f,0.65f); dc(x+0.022f,y+0.262f,0.012f,12);
    }
    void handleCollision(){
        int last=RF_NUM_PEOPLE-1;
        RFPerson* pl=&g_people[last];
        float lx=pl->baseX+pl->offsetX;
        for(int i=0;i<last;i++){
            RFPerson* o=&g_people[i];
            float ox=o->baseX+o->offsetX;
            if(fabsf(lx-ox)<RF_COLLIDE){
                o->dir=-o->dir;
                float ov=RF_COLLIDE-fabsf(lx-ox);
                if(lx<ox) o->offsetX+=ov+0.01f; else o->offsetX-=ov+0.01f;
                break;
            }
        }
    }
    void update(){
        g_timeRF += 0.016f;
        for(int i=0;i<RF_NUM_BIRDS;i++){
            g_birdsRF[i].x += g_birdsRF[i].speed;
            if(g_birdsRF[i].x > 1.3f) g_birdsRF[i].x = -1.3f;
        }
        if(g_paused) return;
        g_sunAngle+=0.00010f;
        for(int i=0;i<5;i++){g_cloudX[i]+=g_cloudSp[i];if(g_cloudX[i]>1.6f)g_cloudX[i]=-1.6f;}
        if(g_signal==1){
            for(int i=0;i<RF_NUM_VEHICLES;i++){
                RFVehicle* v=&g_vehicles[i];
                float eff=v->originalSpeed*g_roadSpeedMult;
                v->offsetX+=eff*v->dir;
                float wx=v->baseX+v->offsetX;
                if(v->dir>0&&wx>1.25f){wx=-1.25f;v->offsetX=wx-v->baseX;}
                else if(v->dir<0&&wx<-1.25f){wx=1.25f;v->offsetX=wx-v->baseX;}
            }
            g_metroX+=g_metroSpeed; if(g_metroX>1.5f) g_metroX=-1.5f;
        } else {
            for(int i=0;i<RF_NUM_VEHICLES;i++){
                RFVehicle* v=&g_vehicles[i];
                float cur=v->baseX+v->offsetX;
                bool past=(v->dir>0)?(cur>0.22f):(cur<0.22f);
                if(past){
                    v->offsetX+=v->originalSpeed*g_roadSpeedMult*v->dir;
                    float wx=v->baseX+v->offsetX;
                    if(v->dir>0&&wx>1.25f){wx=-1.25f;v->offsetX=wx-v->baseX;}
                    else if(v->dir<0&&wx<-1.25f){wx=1.25f;v->offsetX=wx-v->baseX;}
                }
            }
        }
        for(int i=0;i<RF_NUM_PEOPLE;i++){
            RFPerson* p=&g_people[i];
            p->offsetX+=p->speed*p->dir;
            float wx=p->baseX+p->offsetX;
            if(wx>1){wx=-1;p->offsetX=wx-p->baseX;}
            else if(wx<-1){wx=1;p->offsetX=wx-p->baseX;}
        }
        handleCollision();
    }
    void render(){
        glClear(GL_COLOR_BUFFER_BIT); glLoadIdentity();
        if(g_nightRF){
            glColor3f(0.04f,0.05f,0.15f);
            glBegin(GL_QUADS);
            glVertex2f(-1,1); glVertex2f(1,1); glVertex2f(1,0.0f); glVertex2f(-1,0.0f);
            glEnd();
            drawStarsRF();
            glColor3f(0.90f,0.90f,1); dc(0.70f,0.78f,0.055f,32);
            glColor3f(0.04f,0.05f,0.15f); dc(0.73f,0.80f,0.050f,32);
            drawBackground();
        } else {
            drawBackground(); drawSunRF();
        }
        for(int i=0;i<5;i++) drawCloudRF(g_cloudX[i],g_cloudY[i]);
        glColor3f(0.55f,0.62f,0.70f); dq(-1,-0.10f,-0.88f,0.55f);
        glColor3f(0.50f,0.58f,0.66f); dq(-0.90f,-0.10f,-0.80f,0.42f);
        drawSkyscraper(-0.72f,-0.10f,0.20f,0.82f,0.38f,0.52f,0.70f,0.55f,0.75f,0.90f,4,8);
        drawSkyscraper(-0.50f,-0.10f,0.18f,0.68f,0.45f,0.60f,0.72f,0.60f,0.78f,0.92f,3,7);
        drawSkyscraper(-0.30f,-0.10f,0.22f,0.92f,0.35f,0.50f,0.68f,0.52f,0.72f,0.90f,5,10);
        drawSkyscraper(-0.06f,-0.10f,0.20f,0.75f,0.40f,0.55f,0.68f,0.58f,0.76f,0.88f,4,8);
        drawSkyscraper(0.16f,-0.10f,0.18f,0.82f,0.38f,0.52f,0.70f,0.55f,0.75f,0.90f,4,9);
        drawSkyscraper(0.54f,-0.10f,0.20f,0.72f,0.42f,0.56f,0.68f,0.58f,0.76f,0.90f,4,8);
        for(float tx=-0.90f;tx<1;tx+=0.14f) drawTreeRF(tx,-0.42f,0.75f);
        for(float tx=-0.85f;tx<1;tx+=0.22f) drawTreeRF(tx,-0.52f,0.55f);
        drawViaduct(); drawMetro();
        for(int i=0;i<RF_NUM_VEHICLES;i++) drawVehicleRF(g_vehicles[i]);
        float lampX[]={-0.80f,-0.50f,-0.18f,0.12f,0.44f,0.76f};
        for(int i=0;i<6;i++) drawLampRF(lampX[i],-0.550f);
        drawTrafficSignalRF();
        for(int i=0;i<RF_NUM_PEOPLE;i++){
            RFPerson p=g_people[i]; float wx=p.baseX+p.offsetX;
            glPushMatrix(); glTranslatef(wx,p.baseY,0); drawPersonRF(p,i==RF_NUM_PEOPLE-1); glPopMatrix();
        }
        for(int i=0;i<RF_NUM_BIRDS;i++) drawBirdRF(g_birdsRF[i]);
        drawBillboard(-0.85f, -0.20f, 0.14f, 0.10f, 0.85f, 0.30f, 0.30f);
        drawBillboard( 0.70f, -0.22f, 0.16f, 0.09f, 0.30f, 0.55f, 0.90f);
        glColor3f(0.2f,0.2f,0.5f);
        glRasterPos2f(-0.95f,-0.92f);
        const char* hint="S=Signal  SPACE=Pause  Arrows=Speed  N=Night  ESC=Back";
        for(const char* c=hint;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*c);
        glutSwapBuffers();
    }
    void keyboard(unsigned char key,int,int){
        if(key=='s'||key=='S') g_signal=!g_signal;
        if(key==' ') g_paused=!g_paused;
        if(key=='n'||key=='N') g_nightRF = !g_nightRF;
        if(key=='m'||key=='M') g_muted=1;
        if(key=='u'||key=='U') g_muted=0;
    }
    void specialKeys(int key,int,int){
        if(key==GLUT_KEY_UP){g_roadSpeedMult+=0.05f;if(g_roadSpeedMult>2)g_roadSpeedMult=2;}
        else if(key==GLUT_KEY_DOWN){g_roadSpeedMult-=0.05f;if(g_roadSpeedMult<0.2f)g_roadSpeedMult=0.2f;}
        else if(key==GLUT_KEY_LEFT){g_metroSpeed-=0.00005f;if(g_metroSpeed<0.0001f)g_metroSpeed=0.0001f;}
        else if(key==GLUT_KEY_RIGHT){g_metroSpeed+=0.00005f;if(g_metroSpeed>0.0012f)g_metroSpeed=0.0012f;}
    }
    void mouseFunc(int button,int state,int,int){
        if(state==GLUT_DOWN){
            if(button==GLUT_LEFT_BUTTON) g_signal=!g_signal;
            if(button==GLUT_RIGHT_BUTTON) g_paused=!g_paused;
        }
    }
    void init(){
        float vx[10]={-0.90f,-0.40f,0.10f,0.65f,-0.70f,0.80f,0.30f,-0.10f,-0.55f,0.55f};
        float vy[10]={-0.640f,-0.640f,-0.640f,-0.640f,-0.640f,-0.760f,-0.760f,-0.760f,-0.760f,-0.760f};
        float sp[10]={0.00045f,0.00038f,0.00042f,0.00050f,0.00055f,0.00048f,0.00040f,0.00044f,0.00052f,0.00035f};
        float dr[10]={1,1,1,1,1,-1,-1,-1,-1,-1};
        int   typ[10]={0,1,0,2,0,0,2,1,3,3};
        float cr[10]={0.85f,0.90f,0.95f,0.10f,0.22f,0.18f,0.85f,0.85f,0.88f,0.10f};
        float cg[10]={0.50f,0.82f,0.95f,0.60f,0.55f,0.55f,0.50f,0.82f,0.42f,0.45f};
        float cb[10]={0.05f,0.12f,0.95f,0.20f,0.88f,0.18f,0.05f,0.10f,0.08f,0.80f};
        float cr2[10]={0.60f,0.70f,0.70f,0.08f,0.14f,0.12f,0.60f,0.65f,0.55f,0.06f};
        float cg2[10]={0.35f,0.62f,0.70f,0.45f,0.38f,0.38f,0.32f,0.62f,0.25f,0.28f};
        float cb2[10]={0.02f,0.08f,0.72f,0.14f,0.65f,0.12f,0.02f,0.06f,0.04f,0.55f};
        for(int i=0;i<RF_NUM_VEHICLES;i++){
            g_vehicles[i].baseX=vx[i]; g_vehicles[i].baseY=vy[i]; g_vehicles[i].offsetX=0;
            g_vehicles[i].originalSpeed=sp[i]+((float)rand()/RAND_MAX)*0.00015f;
            g_vehicles[i].speed=g_vehicles[i].originalSpeed;
            g_vehicles[i].dir=dr[i]; g_vehicles[i].type=typ[i];
            g_vehicles[i].r=cr[i]; g_vehicles[i].g=cg[i]; g_vehicles[i].b=cb[i];
            g_vehicles[i].r2=cr2[i]; g_vehicles[i].g2=cg2[i]; g_vehicles[i].b2=cb2[i];
        }
        float px[8]={-0.80f,-0.55f,-0.20f,0.15f,0.50f,0.72f,-0.38f,0.88f};
        float py[8]={-0.820f,-0.820f,-0.820f,-0.820f,-0.820f,-0.820f,-0.820f,-0.820f};
        float ps[8]={0.00030f,0.00025f,0.00032f,0.00028f,0.00035f,0.00022f,0.00027f,0.00033f};
        float pd[8]={1,-1,1,-1,1,-1,1,-1};
        float psc[8]={0.80f,0.82f,0.78f,0.80f,0.82f,0.78f,0.80f,0.82f};
        float shr[8]={0.12f,0.88f,0.22f,0.88f,0.65f,0.78f,0.10f,0.36f};
        float shg[8]={0.42f,0.30f,0.62f,0.78f,0.22f,0.22f,0.38f,0.62f};
        float shb[8]={0.78f,0.12f,0.18f,0.10f,0.65f,0.22f,0.62f,0.18f};
        float pnr[8]={0.10f,0.12f,0.08f,0.08f,0.18f,0.18f,0.14f,0.10f};
        float png[8]={0.10f,0.18f,0.18f,0.08f,0.10f,0.10f,0.06f,0.16f};
        float pnb[8]={0.20f,0.42f,0.08f,0.14f,0.28f,0.06f,0.28f,0.06f};
        float skr[8]={0.82f,0.95f,0.80f,0.84f,0.85f,0.82f,0.95f,0.76f};
        float skg[8]={0.60f,0.74f,0.58f,0.58f,0.64f,0.58f,0.74f,0.48f};
        float skb[8]={0.42f,0.50f,0.40f,0.38f,0.44f,0.40f,0.50f,0.32f};
        int wave[8]={0,1,0,1,0,1,0,1};
        for(int i=0;i<RF_NUM_PEOPLE;i++){
            g_people[i].baseX=px[i]; g_people[i].baseY=py[i]; g_people[i].offsetX=0;
            g_people[i].speed=(i==7)?0.00015f:ps[i]+((float)rand()/RAND_MAX)*0.00010f;
            g_people[i].dir=pd[i]; g_people[i].scale=psc[i];
            g_people[i].sr=shr[i]; g_people[i].sg=shg[i]; g_people[i].sb=shb[i];
            g_people[i].pr=pnr[i]; g_people[i].pg=png[i]; g_people[i].pb=pnb[i];
            g_people[i].skr=skr[i]; g_people[i].skg=skg[i]; g_people[i].skb=skb[i];
            g_people[i].wave=wave[i];
        }
        initBirdsRF();
    }
    void reset(){ g_paused=0; g_signal=1; g_metroX=-0.30f; g_sunAngle=-0.3f; g_roadSpeedMult=1; g_timeRF=0; g_nightRF=false; init(); }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  SCENE 6 – Futuristic City / Plane Crash
// ═══════════════════════════════════════════════════════════════════════════════
namespace SceneRahul {
    int sceneMode=0;
    float planeX=-1.25f, heliX=-1.25f, cloudMove=0;
    float trainX=-1.30f, flyingCar1X=-1.20f, flyingCar2X=1.20f, droneX=-1.20f, podX=-1.25f;
    float crashPlane1X=-1.25f, crashPlane2X=1.25f;
    bool crashActive=false, planeCrash=false;
    float crashSmokeSize=0, crashTimer=0;
    float boat1X=-1.10f, boat2X=-1.20f, boat3X=-1.30f, boat4X=-1.40f;
    struct CrashSmoke { float x,y,vy,alpha,r; bool active; };
    static CrashSmoke cs[60];
    void dr(float x,float y,float w,float h){ glBegin(GL_QUADS); glVertex2f(x,y); glVertex2f(x+w,y); glVertex2f(x+w,y+h); glVertex2f(x,y+h); glEnd(); }
    void dtr(float x1,float y1,float x2,float y2,float x3,float y3){ glBegin(GL_TRIANGLES); glVertex2f(x1,y1); glVertex2f(x2,y2); glVertex2f(x3,y3); glEnd(); }
    void dci(float cx,float cy,float r){ glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy); for(int i=0;i<=360;i++){float a=i*PI/180; glVertex2f(cx+cosf(a)*r,cy+sinf(a)*r);} glEnd(); }
    void del(float cx,float cy,float rx,float ry){ glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy); for(int i=0;i<=60;i++){float a=2*PI*i/60;glVertex2f(cx+cosf(a)*rx,cy+sinf(a)*ry);} glEnd(); }
    void drawGradRect(float x,float y,float w,float h,float r1,float g1,float b1,float r2,float g2,float b2){
        glBegin(GL_QUADS);
        glColor3f(r1,g1,b1); glVertex2f(x,y); glVertex2f(x+w,y);
        glColor3f(r2,g2,b2); glVertex2f(x+w,y+h); glVertex2f(x,y+h);
        glEnd();
    }
    void drawSky(){
        if(sceneMode==0)      drawGradRect(-1,-0.02f,2,1.02f,0.44f,0.76f,0.98f,0.12f,0.45f,0.82f);
        else if(sceneMode==1) drawGradRect(-1,-0.02f,2,1.02f,1,0.60f,0.25f,0.72f,0.28f,0.45f);
        else                  drawGradRect(-1,-0.02f,2,1.02f,0.08f,0.10f,0.24f,0.28f,0.12f,0.38f);
    }
    void drawGround(){
        if(sceneMode==0)      glColor3f(0.28f,0.62f,0.20f);
        else if(sceneMode==1) glColor3f(0.32f,0.55f,0.18f);
        else                  glColor3f(0.16f,0.34f,0.14f);
        dr(-1,-1,2,0.98f);
    }
    void drawSunR(){
        if(sceneMode==0){glColor3f(1,0.92f,0.10f);dci(-0.78f,0.78f,0.07f);}
        else if(sceneMode==1){glColor3f(1,0.45f,0.08f);dci(-0.72f,0.55f,0.075f);}
        else{glColor3f(0.92f,0.94f,1);dci(0.78f,0.78f,0.06f);}
    }
    void drawStars(){
        if(sceneMode==2){
            for(int i=0;i<50;i++){
                float x = -0.98f + fmodf(i*0.037f, 1.96f);
                float y = 0.10f + fmodf(i*0.061f, 0.88f);
                float a = 0.4f + 0.6f*fabsf(sinf(cloudMove + i*0.5f));
                glColor3f(a,a,a);
                glPointSize(2); glBegin(GL_POINTS); glVertex2f(x,y); glEnd();
            }
            glPointSize(1);
        }
    }
    void drawClouds(){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1,1,1,sceneMode==2?0.25f:0.85f);
        for(int i=0;i<4;i++){
            float cx = -0.9f + fmodf(cloudMove*0.0005f + i*0.5f, 2.0f);
            float cy = 0.55f + (i%2)*0.10f;
            del(cx-0.06f, cy, 0.06f, 0.03f);
            del(cx+0.06f, cy, 0.06f, 0.03f);
            del(cx, cy, 0.07f, 0.04f);
        }
        glDisable(GL_BLEND);
    }
    void drawCity(){
        for(int i=0;i<8;i++){
            float bx = -0.95f + i*0.24f;
            float bw = 0.18f;
            float bh = 0.25f + (i%3)*0.10f;
            if(sceneMode==0)      glColor3f(0.55f,0.70f,0.90f);
            else if(sceneMode==1) glColor3f(0.60f,0.40f,0.35f);
            else                  glColor3f(0.20f,0.28f,0.50f);
            dr(bx, 0.0f, bw, bh);
            for(int wy=0;wy<3;wy++){
                for(int wx=0;wx<3;wx++){
                    if(sceneMode==2 && ((i+wy+wx)%3==0)) glColor3f(1.0f,0.90f,0.40f);
                    else if(sceneMode==2) glColor3f(0.10f,0.15f,0.30f);
                    else glColor3f(0.85f,0.92f,1.0f);
                    dr(bx+0.025f+wx*0.045f, 0.05f+wy*0.07f, 0.025f, 0.04f);
                }
            }
            glColor3f(0.85f,0.30f,0.20f);
            dr(bx+bw*0.5f-0.004f, bh, 0.008f, 0.05f);
            glColor3f(1,0.40f,0.40f);
            dci(bx+bw*0.5f, bh+0.05f, 0.008f);
        }
    }
    void drawPlane(){
        glPushMatrix(); glTranslatef(planeX, 0.55f, 0);
        glColor3f(0.85f,0.85f,0.90f);
        del(0,0,0.10f,0.025f);
        dtr(-0.06f,0.01f, 0.02f, 0.10f, 0.04f, 0.01f);
        dtr(-0.06f,-0.01f, 0.02f, -0.10f, 0.04f, -0.01f);
        dtr(-0.10f,0, -0.12f, 0.05f, -0.08f, 0.02f);
        glColor3f(0.40f,0.60f,0.85f); dci(0.06f, 0, 0.012f);
        glPopMatrix();
    }
    void drawHeli(){
        glPushMatrix(); glTranslatef(heliX, 0.65f, 0);
        glColor3f(0.90f,0.65f,0.15f);
        del(0,0,0.06f,0.035f);
        glColor3f(0.55f,0.75f,0.90f);
        dtr(0.06f,0.02f, 0.12f, 0.01f, 0.06f,-0.01f);
        glColor3f(0.30f,0.30f,0.32f); dr(-0.015f,0.03f, 0.03f, 0.008f);
        glPushMatrix(); glTranslatef(0, 0.06f, 0); glRotatef(cloudMove*30, 0, 0, 1);
        glColor3f(0.40f,0.40f,0.42f);
        dr(-0.10f, -0.004f, 0.20f, 0.008f);
        dr(-0.004f, -0.10f, 0.008f, 0.20f);
        glPopMatrix();
        glColor3f(0.30f,0.20f,0.10f);
        dr(-0.04f,-0.02f, 0.02f, 0.005f);
        dr(0.02f,-0.02f, 0.02f, 0.005f);
        glPopMatrix();
    }
    void drawFlyingCar(float x, float y, float r,float g,float b){
        glColor3f(r,g,b); dr(x, y, 0.10f, 0.035f);
        glColor3f(0.60f,0.80f,0.95f); dr(x+0.02f, y+0.035f, 0.06f, 0.015f);
        glColor3f(1,1,0.60f); dci(x-0.005f, y+0.015f, 0.008f);
    }
    void drawDrone(float x, float y){
        glPushMatrix(); glTranslatef(x, y, 0);
        glColor3f(0.20f,0.20f,0.22f); dr(-0.03f,-0.005f,0.06f,0.01f);
        glColor3f(0.90f,0.20f,0.20f); dci(0,0,0.006f);
        glColor3f(0.40f,0.40f,0.42f);
        dci(-0.03f,0.0f,0.012f); dci(0.03f,0.0f,0.012f);
        glPopMatrix();
    }
    void drawBoatR(float x, float y, float s, float r, float g, float b){
        glPushMatrix(); glTranslatef(x,y,0); glScalef(s,s,1);
        glColor3f(r,g,b);
        glBegin(GL_POLYGON);
        glVertex2f(-0.08f,0); glVertex2f(0.08f,0);
        glVertex2f(0.06f,-0.025f); glVertex2f(-0.06f,-0.025f);
        glEnd();
        glColor3f(0.92f,0.92f,0.95f); dtr(0,0.06f, 0,0.01f, 0.05f,0.02f);
        glColor3f(0.35f,0.22f,0.10f); dr(-0.002f,0,0.004f,0.06f);
        glPopMatrix();
    }
    void drawTrainR(){
        glPushMatrix(); glTranslatef(trainX, -0.10f, 0);
        for(int car=0;car<3;car++){
            float cx = car*0.20f;
            glColor3f(0.30f,0.55f,0.85f); dr(cx, 0, 0.18f, 0.06f);
            glColor3f(0.10f,0.20f,0.35f); dr(cx, 0.06f, 0.18f, 0.015f);
            glColor3f(0.85f,0.95f,1);
            for(int w=0;w<3;w++) dr(cx+0.02f+w*0.05f, 0.015f, 0.025f, 0.03f);
        }
        glColor3f(0.20f,0.20f,0.22f);
        dci(0.04f,-0.005f,0.012f); dci(0.14f,-0.005f,0.012f);
        dci(0.24f,-0.005f,0.012f); dci(0.34f,-0.005f,0.012f);
        dci(0.44f,-0.005f,0.012f); dci(0.54f,-0.005f,0.012f);
        glPopMatrix();
    }
    void drawPodR(){
        glPushMatrix(); glTranslatef(podX, 0.75f, 0);
        glColor3f(0.85f,0.20f,0.65f);
        del(0,0,0.07f,0.03f);
        glColor3f(1,0.75f,0.95f); dci(0.04f,0,0.012f);
        glColor3f(1,0.90f,0.40f);
        for(int i=0;i<3;i++) dci(-0.04f + i*0.03f, -0.008f, 0.005f);
        glPopMatrix();
    }
    void drawCrashPlane(float x, float y, float tilt){
        glPushMatrix(); glTranslatef(x, y, 0); glRotatef(tilt, 0, 0, 1);
        glColor3f(0.80f,0.20f,0.15f);
        del(0,0,0.09f,0.022f);
        dtr(-0.06f,0, 0.02f, 0.09f, 0.04f, 0);
        dtr(-0.06f,0, 0.02f,-0.09f, 0.04f, 0);
        glPopMatrix();
    }
    void spawnCrashSmoke(float x, float y){
        for(int i=0;i<60;i++){
            if(!cs[i].active){
                cs[i].x = x + ((rand()%100)-50)/500.0f;
                cs[i].y = y + ((rand()%100)-50)/500.0f;
                cs[i].vy = 0.001f + (rand()%100)/10000.0f;
                cs[i].alpha = 0.9f;
                cs[i].r = 0.02f + (rand()%100)/3000.0f;
                cs[i].active = true; return;
            }
        }
    }
    void updateCrashSmoke(){
        for(int i=0;i<60;i++){
            if(!cs[i].active) continue;
            cs[i].y += cs[i].vy;
            cs[i].r += 0.0005f;
            cs[i].alpha -= 0.005f;
            if(cs[i].alpha <= 0) cs[i].active = false;
        }
    }
    void drawCrashSmoke(){
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        for(int i=0;i<60;i++){
            if(!cs[i].active) continue;
            glColor4f(0.25f,0.25f,0.25f, cs[i].alpha);
            dci(cs[i].x, cs[i].y, cs[i].r);
        }
        glDisable(GL_BLEND);
    }

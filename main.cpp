#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int cursorX=0, cursorY=0, opMenu1=0, opMenu2=0, acao=1;
int txSteve=0,tySteve=0,txInimigo=0, txC=0;
int steps = 0, stepsC = 0;
int forward = 1, forwardC = 1;
int vidas=1;
int corC=0;
int acabou=0;

// Função responsável por inicializar parâmetros e variáveis
void Inicializa() {
    // Define a janela de visualização 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void DesenhaTexto(float x, float y, const char* string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string);
        string++;
    }
}

void DesenhaSteve() {
	glColor3f(0.92,0.90,0.45);
	glRectf(115+txSteve, 600+tySteve, 125+txSteve, 620+tySteve);//Cabelo
	glColor3f(0.95, 0.86, 0.78);
    glRectf(100+txSteve, 530+tySteve, 140+txSteve, 600+tySteve); //Retângulo para a cabeça
    glColor3f(0.0,0.43,1);
    glRectf(105+txSteve, 560+tySteve, 115+txSteve, 580+tySteve);//Olhos
    glRectf(125+txSteve, 560+tySteve, 135+txSteve, 580+tySteve);
    glColor3f(0.0,0.0,0.0);
    glRectf(100+txSteve, 400+tySteve, 140+txSteve, 530+tySteve);//Corpo
    glColor3f(0.23,0.11,0.10);
    glRectf(100+txSteve, 380+tySteve, 140+txSteve, 400+tySteve);//Sapato
    glColor3f(0.95, 0.86, 0.78);
    glRectf(80+txSteve, 450+tySteve, 100+txSteve, 530+tySteve);//Braço Esq
    glBegin(GL_QUADS);//Braço Dir
        glVertex3f(160+txSteve, 460+tySteve, 0);
        glVertex3f(180+txSteve, 465+tySteve, 0);
        glVertex3f(160+txSteve, 535+tySteve, 0);
        glVertex3f(140+txSteve, 530+tySteve, 0);
    glEnd();
    glColor3f(0.5,0.5,0.5);
    glRectf(175+txSteve, 425+tySteve, 180+txSteve, 525+tySteve);//Cabo Espada
    glColor3f(0.85,0.85,0.85);
    glRectf(180+txSteve, 440+tySteve, 340+txSteve, 510+tySteve);//Corpo Espada
    glBegin(GL_TRIANGLES);//Ponta Espada
    	glVertex2i(340+txSteve,440+tySteve);
    	glVertex2i(340+txSteve,510+tySteve);
    	glVertex2i(360+txSteve,475+tySteve);
    glEnd();
}

void DesenhaLobo() {
    // Corpo
    glColor3f(0.5, 0.5, 0.5); // Cor cinza para o corpo
    glRectf(850+txInimigo, 400, 930+txInimigo, 480); // Corpo

    // Cabeça
    glColor3f(0.5, 0.5, 0.5); // Cor cinza para a cabeça
    glRectf(810+txInimigo, 460, 850+txInimigo, 500); // Cabeça

    // Olhos
    glColor3f(0.0, 0.0, 0.0); // Cor preta para os olhos
    glRectf(820+txInimigo, 475, 825+txInimigo, 480); // Olho esquerdo
    glRectf(830+txInimigo, 475, 835+txInimigo, 480); // Olho direito

    // Orelhas
    glColor3f(0.5, 0.5, 0.5); // Cor cinza para as orelhas
    glRectf(810+txInimigo, 500, 815+txInimigo, 520); // Orelha esquerda
    glRectf(845+txInimigo, 500, 850+txInimigo, 520); // Orelha direita

    // Focinho
    glColor3f(0.8, 0.8, 0.8); // Cor mais clara para o focinho
    glRectf(810+txInimigo, 470, 820+txInimigo, 475); // Focinho

    // Pernas
    glColor3f(0.5, 0.5, 0.5); // Cor cinza para as pernas
    glRectf(860+txInimigo, 380, 870+txInimigo, 400);
    glRectf(910+txInimigo, 380, 920+txInimigo, 400);

    // Cauda
    glColor3f(0.5, 0.5, 0.5); // Cor cinza para a cauda
    glRectf(930+txInimigo, 450, 950+txInimigo, 460); // Cauda
}

void DesenhaMonstro() {
    // Corpo
    glColor3f(0.3, 0.1, 0.1); // Cor vermelha escura para o corpo
    glRectf(850, 400, 930, 480); // Corpo

    // Cabeça
    glColor3f(0.3, 0.1, 0.1); // Cor vermelha escura para a cabeça
    glRectf(810, 460, 850, 500); // Cabeça

    // Olhos
    glColor3f(0.0, 1.0, 0.0); // Cor verde para os olhos
    glRectf(820, 475, 825, 480); // Olho esquerdo
    glRectf(830, 475, 835, 480); // Olho direito

    // Orelhas
    glColor3f(0.3, 0.1, 0.1); // Cor vermelha escura para as orelhas
    glRectf(810, 500, 815, 520); // Orelha esquerda
    glRectf(845, 500, 850, 520); // Orelha direita

    // Focinho
    glColor3f(0.6, 0.3, 0.3); // Cor mais clara para o focinho
    glRectf(810, 470, 820, 475); // Focinho

    // Pernas
    glColor3f(0.3, 0.1, 0.1); // Cor vermelha escura para as pernas
    glRectf(860, 380, 870, 400); // Perna traseira esquerda
    glRectf(910, 380, 920, 400); // Perna traseira direita

    // Cauda
    glColor3f(0.3, 0.1, 0.1); // Cor vermelha escura para a cauda
    glRectf(930, 450, 950, 460); // Cauda
}


void DesenhaCasa(int x, int y) {
    glColor3f(0.54, 0.27, 0.07);
    // Desenha o corpo da casa
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + 200, y);
    glVertex2i(x + 200, y + 200);
    glVertex2i(x, y + 200);
    glEnd();
    glColor3f(0.5, 0.0, 0.0);
    // Desenha o telhado da casa
    glBegin(GL_TRIANGLES);
    glVertex2i(x, y + 200);
    glVertex2i(x + 100, y + 300);
    glVertex2i(x + 200, y + 200);
    glEnd();
    glColor3f(0.84, 0.47, 0.27);
    // Desenha a porta da casa
    glBegin(GL_QUADS);
    glVertex2i(x + 80, y);
    glVertex2i(x + 120, y);
    glVertex2i(x + 120, y + 160);
    glVertex2i(x + 80, y + 160);
    glEnd();
    // Desenha as janelas da casa
    glBegin(GL_QUADS);
    glVertex2i(x + 20, y + 80);
    glVertex2i(x + 60, y + 80);
    glVertex2i(x + 60, y + 120);
    glVertex2i(x + 20, y + 120);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(x + 140, y + 80);   
    glVertex2i(x + 180, y + 80);
    glVertex2i(x + 180, y + 120);
    glVertex2i(x + 140, y + 120);
    glEnd();
}

void DesenhaArvore (int x, int y){
	glBegin(GL_QUADS);//Tronco
        glColor3f(0.45, 0.20, 0.09);
        glVertex3f(x, y, 0);
        glVertex3f(x+25, y, 0);
        glVertex3f(x+25, y+200, 0);
        glVertex3f(x, y+200, 0);
    glEnd();
    glBegin(GL_QUADS);//Folha
        glColor3f(0.09, 0.48, 0.09);
        glVertex3f(x-50, y+170, 0);
        glVertex3f(x+75, y+170, 0);
        glVertex3f(x+75, y+340, 0);
        glVertex3f(x-50, y+340, 0);
    glEnd();
    glBegin(GL_QUADS);//Arbusto
        glColor3f(0.09, 0.48, 0.09);
        glVertex3f(x+400, y, 0);
        glVertex3f(x+600, y, 0);
        glVertex3f(x+600, y+170, 0);
        glVertex3f(x+400, y+170, 0);
    glEnd();
}

void DesenhaMundo(){
	glBegin(GL_QUADS);//Céu
        glColor3f(0.88, 0.95, 1);
        glVertex3f(0,625, 0);
        glVertex3f(1000, 625, 0);
        glVertex3f(1000, 1000, 0);
        glVertex3f(0, 1000, 0);
    glEnd();
	glBegin(GL_QUADS);//Chão
        glColor3f(0.62, 0.58, 0.45);
        glVertex3f(0, 301, 0);
        glVertex3f(1000, 301, 0);
        glVertex3f(1000, 625, 0);
        glVertex3f(0, 625, 0);
    glEnd();
    DesenhaArvore(275, 625);
    DesenhaCasa(400, 625);
}
int vidaInimigo=150, vidaSteve=150;
void Menu() {
    glBegin(GL_QUADS); //Fundo Menu
        glColor3f(0, 0, 0.5);
        glVertex3f(0, 0, 0);
        glColor3f(0, 0, 0);
        glVertex3f(1000, 0, 0);
        glColor3f(0, 0, 1);
        glVertex3f(1000, 300, 0);
        glVertex3f(0, 300, 0);
    glEnd();
    
    glColor3f(0,0,0);
    glRectf(750, 185, 900, 205);//Vida max
    glColor3f(0,1,0);
    glRectf(750, 185, 750+vidaSteve, 205);//Vida atual
    
    glColor3f(0,0,0);
    glRectf(750, 85, 900, 105);//Vida max inimigo
    glColor3f(1,0,0);
    glRectf(750, 85, 750+vidaInimigo, 105);//Vida atual inimigo
    

    glColor3f(1, 1, 1);
    DesenhaTexto(50, 225, "ATACAR");
    DesenhaTexto(50, 175, "MAGIA");
    DesenhaTexto(50, 125, "ITEM");
    DesenhaTexto(50, 75, "PASSAR");
    DesenhaTexto(750, 225, "STEVE");
    glColor3f(0, 1, 0);
    DesenhaTexto(815, 150, "HP");
    glColor3f(1,1,1);
    DesenhaTexto(750, 125, "LOBO");
    glColor3f(1, 0, 0);
    DesenhaTexto(815, 50, "HP");
}

void Menu2() {
    if (opMenu1==3) {
        glColor3f(1, 1, 1);
        DesenhaTexto(200, 225, "POCAO");
        DesenhaTexto(200, 175, "POCAO GRANDE");
    }
}

void Cursor(){
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLES);
		glVertex2i(30 + cursorX, 245 + cursorY);
		glVertex2i(45 + cursorX,  235+ cursorY);
		glVertex2i(30 + cursorX, 225 + cursorY);
	glEnd();
}

void animaAtaque(int value) {
    if (steps < 9) {
        if (forward) {
            txSteve += 50; // Move para frente
        } else {
            txSteve -= 50; // Move para trás
        }
        steps++;
    } else {
        if (forward) {
            forward = 0; // Inverte a direção
            steps = 0; // Reseta os passos
        } else {
            // Animação completa
            return;
        }
    }
    glutPostRedisplay(); // Redesenha a cena
    glutTimerFunc(16, animaAtaque, 0); // Chama novamente a função após 100ms
}

void DesenhaCirculo(float x, float y, float radius) {
    int num_segments = 100;
    if(corC==0){
    	
	}else{
		glColor3f(1.0, 0.24, 0.0);
    	glBegin(GL_TRIANGLE_FAN);
    	for (int i = 0; i < num_segments; i++) {
        	float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        	float dx = radius * cosf(theta);
        	float dy = radius * sinf(theta);
        	glVertex2f(x + dx + txC, y + dy);
    	}
   		glEnd();
	}
}

void animaCirculo(int value) {
    if (stepsC < 9) {
        if (forwardC) {
            txC += 50; // Move para frente
            corC = 1;
        } else {
            corC = 0;
            txC -= 50; // Move para trás
        }
        stepsC++;
    } else {
        if (forwardC) {
            forwardC = 0; // Inverte a direção
            stepsC = 0; // Reseta os passos
        } else {
            // Animação completa
            // Reseta os valores para permitir nova animação
            forwardC = 1; // Prepara para a próxima animação
            txC = 0; // Reseta a posição X
            stepsC = 0; // Reseta os passos
            corC = 0; // Reseta a cor
            return;
        }
    }
    glutPostRedisplay(); // Redesenha a cena
    glutTimerFunc(16, animaCirculo, 0); // Chama novamente a função após 16ms
}

void gerenciaAcao(){
    if(opMenu1==1 && acabou==0){
        steps = 0;
        forward = 1;
        animaAtaque(0);
        vidaSteve+=-15;
        vidaInimigo+=-15;
        opMenu1=0;
    	opMenu2=0;
    }
    if(opMenu1==2 && acabou==0){
        vidaSteve+=-15;
        vidaInimigo+=-30;
        animaCirculo(0);
        opMenu1=0;
    	opMenu2=0;
    }
    if(opMenu1==4 && acabou==0){
        vidaSteve+=-15;
        opMenu1=0;
    	opMenu2=0;
    }
    if(opMenu2==4){
        opMenu2=0;
        vidaSteve+=vidaSteve>105?150-vidaSteve:45;
    }
    if(opMenu2==5){
        opMenu2=0;
        vidaSteve+=vidaSteve>60?150-vidaSteve:60;
    }
    if(vidaInimigo<=0&&vidas>0){
        vidas-=1;
        vidaInimigo=150;
    }
    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exit(0);
    }
    if (key == 13){ //ENTER key
    	if(opMenu1==0 && cursorY==0){//ATACAR
    		opMenu1=1;
    		gerenciaAcao();
		}
		if(opMenu1==0 && cursorY==-50){//MAGIA
    		opMenu1=2;
    		gerenciaAcao();
		}
		if(opMenu1==0 && cursorY==-100){//ITEM
    		opMenu1=3;
    		cursorX=150;
    		cursorY=0;
		}
		if(opMenu1==0 && cursorY==-150){//PASSAR
    		opMenu1=4;
    		gerenciaAcao();
		}
		if(opMenu1==2 && cursorY==0){//FOGO
			opMenu2=1;
			gerenciaAcao();
		}
		if(opMenu1==2 && cursorY==-50){//RAIO
			opMenu2=2;
			gerenciaAcao();
		}
		if(opMenu1==2 && cursorY==-100){//AGUA
			opMenu2=3;
			gerenciaAcao();
		}
		if(opMenu1==3 && cursorY==0){//POCAO
			opMenu2=4;
			gerenciaAcao();
		}
		if(opMenu1==3 && cursorY==-50){//POCAO GRANDE
			opMenu2=5;
			gerenciaAcao();
		}
	}
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
    	cursorY += cursorY==0?0:50;	
    }
    if(key == GLUT_KEY_DOWN) {
    	if(opMenu1==0){
    		cursorY += cursorY<=-150?0:-50;
		}
        if(opMenu1==2){
    		cursorY += cursorY<=-100?0:-50;
		}
		if(opMenu1==3){
			cursorY += cursorY<=-50?0:-50;
		}
    }
    if(key == GLUT_KEY_LEFT) {
    	if(cursorX>0){
    		cursorX += -150;
    		opMenu1=0;
		}
	}
    glutPostRedisplay();
}

void RenderizaJogo() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaMundo();
    Menu();
    Menu2();
    Cursor();
    DesenhaSteve();
    DesenhaCirculo(360,475,40);
    if(vidas>0){
    	DesenhaLobo();	
	}
    if(vidas==0){
    	DesenhaMonstro();
	}
	if(vidaInimigo<=0&&vidas==0){
		glColor3d(1,1,1);
		DesenhaTexto(450,450,"VOCE VENCEU");
		acabou=1;
	}
	else if(vidaSteve<=0){
		glColor3d(1,1,1);
		DesenhaTexto(450,450,"VOCE PERDEU");
		acabou=1;
	}
	
	glColor3f(0,0,0);
    DesenhaTexto(20, 950, "MOUSE DIREITO P/MENU");
    glFlush();
}

void menu(int num) {//MENU DO MOUSE
    opMenu1 = num;
    gerenciaAcao();
}

void menu2(int num){
	opMenu2 = num;
	gerenciaAcao();
}

// Programa Principal
int main(int argc, char** argv) {
	int submenu;
    // Inicializa a GLUT
    glutInit(&argc, argv);
    // Define o modo de operação da GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(1240, 720);
    // Cria a janela passando como argumento o título da mesma
    glutCreateWindow("KH Nel");
    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(RenderizaJogo);
    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc(Teclado);
    // Registra a função callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);
    // Chama a função responsável por fazer as inicializações
    Inicializa();
    //CRIAÇÃO DO MENU NO MOUSE
    submenu = glutCreateMenu(menu2);
    glutAddMenuEntry("POCAO",4);
    glutAddMenuEntry("POCAO GRANDE",5);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("ATACAR", 1);
    glutAddMenuEntry("MAGIA", 2);
    glutAddSubMenu("ITEM", submenu);
    glutAddMenuEntry("PASSAR", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();
    return 0;
}

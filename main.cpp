#include"window.hpp"
#include<unistd.h>
#include<stdlib.h>
#include<ctime>

typedef struct{
    int x,y;
} point;

point *snake = new point[1];

void draw_snake(point *snake);
void draw_filed(int x_gap, int y_gap, int x_size, int y_size, int size){

    XFillRectangle(dis, win, gc, x_gap, y_gap, x_size * size, size);
    XFillRectangle(dis, win, gc, x_gap, y_gap, size, y_size * size);
    XFillRectangle(dis, win, gc, x_size * size, y_gap, size, y_size * size + size);
    XFillRectangle(dis, win, gc, x_gap, y_size * size, x_size * size, size);

}

int toint(string s){
    int su=0;
    int i=0;
    while(s[i]){su=su * 10 + (s[i] - '0');i++;}
    return su;
}


void add_body(point *&snake, int &old_length){

    point *buf = new point[old_length+1];
    
    memcpy(buf, snake, old_length * sizeof(point));
    free(snake);

    //buf[old_length].x = buf[old_length-1].x;
    //buf[old_length].y = buf[old_length-1].y;

    //delete [] snake;

    //snake = buf;
    //free(buf);

    snake = buf;
    //cout<<(old_length) * sizeof(point)<<endl; 

    old_length++;
    return ;

}

bool apple_in_snake(point *snake, int l, point apple){
    for(int i = 0; i<l; i++){
        if(snake[i].x == apple.x && snake[i].y == apple.y){return 1;}
    
    }
    return 0;
}

bool snake_in_snake(point *snake, int l){
    for(int i=1; i<l; i++){
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){return 1;}
    }
    return 0;
}

int logic(point *&snake, char moving, int size, point &apple, int &leng, int x, int y, int sx, int sy, string &score){

    if(snake[0].x == apple.x && snake[0].y == apple.y){
        score = to_string(leng);
        add_body(snake, leng);
        while(apple_in_snake(snake, leng, apple)){apple.x = rand()%(sx-1) + 1; apple.y = rand() % (sy-1) + 1;}


    }


    if(leng > 1){
    if(snake_in_snake(snake, leng)){return 1;}
    for(int i=leng-1; i>0; i--){
       snake[i].x = snake[i - 1].x;
       snake[i].y = snake[i - 1].y;
    }}
    if(snake[0].x <= 0 || snake[0].y <= 0){return 1;}
    if(snake[0].x >= sx || snake[0].y >= sy){return 1;}
    switch(moving){
        case 'l':
            snake[0].x -= 1;
            break;
        case 'r':
            snake[0].x += 1;
            break;
        case 'u':
            snake[0].y -= 1;
            break;
        case 'd':
            snake[0].y += 1;
            break;
    }

    return 0;
}

void draw(point snake[], point apple, int leng, int x, int y, int size){

    for(int i=0; i<leng; i++){
        XFillRectangle(dis, win, gc, x + snake[i].x * size, y + snake[i].y * size, size, size);
    }
    
    XSetForeground(dis, gc, red);
    XFillRectangle(dis, win, gc, x + apple.x * size, y + apple.y * size, 10, 10);
    XSetForeground(dis, gc, black);
}

void init(point *&snake, point &apple, int &leng, char &moving, int lvlx, int lvly){
    leng = 1;
    moving = 'r';
    apple = {rand() % (lvlx - 1) + 1, rand() % (lvly - 1) + 1};
    free(snake);
    snake = new point[1];
    snake[0].x = 1;
    snake[0].y = 1;

}

int main(int argc, char **argv){

    string buf;
    srand((unsigned)time(0));

    for(int i=0; i<argc; i++){
        buf = argv[i];
        if(buf == "-x"){sx = toint(argv[i+1]);}

        if(buf == "-y"){sy = toint(argv[i+1]);}

    }
    int size = 10;

    cout<<sx<<" "<<sy<<endl;
    int lvlx = sx / size - 1;
    int lvly = sy / size - 1;
    int x_gap = (sx - ((lvlx + 2) * size)) / 2; // + 2 because of borders
    int y_gap = (sy - ((lvly + 2) * size)) / 2;
    if(x_gap < 0){x_gap = 0;}
    if(y_gap < 0){y_gap = 0;}
    create();
    XEvent event;
    KeySym press;

    int mov = 1;
    int time = 64000;
    int leng;
    char moving = 'r';
    point apple;
    bool first_time = 1;

    
    int game = 0;
    char txtsc[] = "your score - ";
    char playag[] = "press any button to play again...";
    char tbuf[1000];
    init(snake, apple, leng, moving, lvlx, lvly);
    string score = to_string(leng - 1);
    XSetForeground(dis, gc, black);


    while(1)
    {
        
        if(XPending(dis)){
        XNextEvent(dis, &event);
        //if(event.type == KeyPress && XLookupString(&event.xkey, text, len, &press, 0) == 1){
            //if(text[0] == 'q'){close();}
        //}
        if(event.type == KeyPress){
            if(game == 0){game = 1; init(snake, apple, leng, moving, lvlx, lvly); score = to_string(leng - 1); first_time = 0;}
            //cout<<event.xkey.keycode<<endl;
            if (event.xkey.keycode == EXIT_B){close();}

            else if (event.xkey.keycode == LEFT_B && moving != 'r'){moving = 'l';}
            else if (event.xkey.keycode == RIGHT_B && moving != 'l'){moving = 'r';}
            else if (event.xkey.keycode == UP_B && moving != 'd'){moving = 'u';}
            else if (event.xkey.keycode == DOWN_B && moving != 'u'){moving = 'd';}
            
        }}
        if(game){
        draw(); // я тут осознал, что меня спасла перегрузочка
        
        
        draw_filed(x_gap, y_gap, lvlx, lvly, size);

        if(logic(snake, moving, size, apple, leng, x_gap, y_gap, lvlx, lvly, score)){game = 0; score = to_string(leng - 1);}
        
        draw(snake, apple, leng, x_gap, y_gap, size);

        XSetForeground(dis, gc, white);
        XDrawString(dis, win, gc, 5, sy, score.c_str(), score.length());
        XSetForeground(dis, gc, black);
        }
        else{
            draw();
            XSetBackground(dis, gc, red);
            XSetForeground(dis, gc, green);
            XFillRectangle(dis, win, gc, x_gap, y_gap, sx - (4 * x_gap), sy - (4 * y_gap));
            XSetForeground(dis, gc, black);
            if(!first_time){
            
                XDrawString(dis, win, gc, 100, 100, txtsc, 13);
                XDrawString(dis, win, gc, 200, 100, score.c_str(), score.length());
                XDrawString(dis, win, gc, 100, 200, playag, 33);}
            else{
                XDrawString(dis, win, gc, 100, 200, playag, 25);
            }
            
        }
        

        usleep(time);
        

        

    }
}
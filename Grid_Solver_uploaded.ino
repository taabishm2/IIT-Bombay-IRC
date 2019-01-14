#include<math.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(LED_BUILTIN,OUTPUT);
}




int plen = 0;

//=================================Creating the stack======================================
int stack[50];
int top=-1;                                                                
void push(int d)
{
  top++;
  stack[top] = d;                                                             
                                                                              
}
int pop()
{
  top--;
  return stack[top+1];
}
//===============================stack1=========================================================
int stack1[45];
int top1=-1;                                                                
void push1(int d)
{
  top1++;
  stack1[top1] = d;                                                             
                                                                              
}
int pop1()
{
  top1--;
  return stack1[top1+1];
}
//=========================================stack2================================================
int stack2[45];
int top2=-1;                                                                
void push2(int d)
{
  top2++;
  stack2[top2] = d;                                                             
                                                                              
}
int pop2()
{
  top2--;
  return stack2[top2+1];
}
//======================================stack3===================================================
int stack3[45];
int top3=-1;                                                                
void push3(int d)
{
  top3++;
  stack3[top3] = d;                                                               
}
int pop3()
{
  top3--;
  return stack3[top3+1];
}
//=========================================================================================
//int node_type;       // 1 for cross-section(passable, 0 for node(not passable) and 5 for block
//boolean flag_node;   // Determines whether node is detected or node
int minm,r,c,i;
int maze[4][4]={
  {1,1,1,1},
  {0,0,0,1},
  {1,3,0,1},
  {0,1,1,1}
  };
/*int maze[4][4]={
  {1,1,1,1},
  {0,0,0,1},
  {3,0,1,1},
  {1,1,1,0}
  };
 */
/*  
int maze[9][5]={
  {1,1,1,1,1},
  {0,1,1,1,1},
  {0,0,1,0,1},
  {0,1,1,1,1},
  {0,1,1,0,1},
  {0,1,0,1,1},
  {1,1,1,0,1},
  {1,0,1,0,1},
  {1,1,1,1,9},
  };*/
int sol[4][4];
int sol1[4][4];
int sol2[4][4];
int sol3[4][4];
int l1;
int l2;
int l3;
int dest, dir, curDir;
int curX,curY,destX,destY;
int target[5];

void ini_sol()
 {
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      sol[i][j]=0;
    }
  }
 }

void ini_sol1()
 {
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      sol1[i][j]=0;
    }
  }
 }


void ini_sol2()
 {
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      sol2[i][j]=0;
    }
  }
 }


void ini_sol3()
 {
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      sol3[i][j]=0;
    }
  }
 }

 

 
/*
void printsol()
 {
  for(int i=3;i>-1;i--)
  {
    for(int j=0;j<4;j++)
    {
      cout << sol[i][j] <<  " ";
    }
    cout << '\n';
  }
 }

void printsol1()
 {
  for(int i=3;i>-1;i--)
  {
    for(int j=0;j<4;j++)
    {
      cout << sol1[i][j] << " ";
    }
    cout << '\n';
  }
 }
 void printsol2()
 {
  for(int i=3;i>-1;i--)
  {
    for(int j=0;j<4;j++)
    {
      cout << sol2[i][j] << " ";
    }
    cout << '\n';
  }
 }
 void printsol3()
 {
  for(int i=3;i>-1;i--)
  {
    for(int j=0;j<4;j++)
    {
      cout << sol3[i][j] << " " ;
    }
    cout << '\n';
  }
 }
*/
bool isvalid(int x,int y)
{ 
  if(x<0||x>3)
    return false;
  if(y<0||y>3)
    return false;
  if(maze[y][x] == 0)
    return false;
  if(sol[y][x] == 1)
    return false;
            
  return true;
}

bool isOptimizable(int x, int y, int p)
{
  int a=1,b=1,c=1,d=1;
  if(x-1 < 0) d=0;
  if(x+1 > 3) c=0;
  if(y-1 < 0) b=0;
  if(y+1 > 3) a=0;
   if(p == 1) {
  if(a*sol1[y+1][x] + b*sol1[y-1][x] + c*sol1[y][x+1] + d*sol1[y][x-1] > 1) {
      return true;
      }
   }
   
   if(p == 2) {
  if(a*sol2[y+1][x] + b*sol2[y-1][x] + c*sol2[y][x+1] + d*sol2[y][x-1] > 1) {
      return true;
      }
   }
   
   if(p == 3) {
  if(a*sol3[y+1][x] + b*sol3[y-1][x] + c*sol3[y][x+1] + d*sol3[y][x-1] > 1) {
      return true;
      }
   }
      return false;
}

bool findpath1(int x, int y, int d)
{
  if(!isvalid(x,y))                                                                          
    { return false; }
    
    if(isOptimizable(x,y,1)) {             // doubt
      return false;
      }
    
    sol1[y][x]=1; push1(10*y + x);
    l1++;
    if(maze[y][x]==dest)
    { curX = x; curY = y; return true; }
    
    if(d!=3) {  if (findpath1(x+1,y,1)) return true;}               // d=3 negative x direction
    if(d!=4) {  if (findpath1(x,y+1,2)) return true;}               // d=4 negative y direction
    if(d!=1) {  if (findpath1(x-1,y,3)) return true;}               // d=1 positive x direction
    if(d!=2) {  if (findpath1(x,y-1,4)) return true;}               // d=2 positive y direction
     sol1[y][x]=0; pop1();
     l1--;
     return false;
 }

bool findpath2(int x, int y, int d)
{
  if(!isvalid(x,y))                                                                          
    { return false; }
    
    if(isOptimizable(x,y,2)) {             // doubt
      return false;
      }
    
    sol2[y][x]=1; push2(10*y + x);
    l2++;
    if(maze[y][x]==dest)
    { curX = x; curY = y; return true; }
    
    if(d!=1) {  if (findpath2(x-1,y,3)) return true;}               // d=1 positive x direction
    if(d!=4) {  if (findpath2(x,y+1,2)) return true;}               // d=4 negative y direction
    if(d!=3) {  if (findpath2(x+1,y,1)) return true;}               // d=3 negative x direction
    if(d!=2) {  if (findpath2(x,y-1,4)) return true;}               // d=2 positive y direction
     sol2[y][x]=0; pop2();
     l2--;
     return false;
 }

bool findpath3(int x, int y, int d)
{
  if(!isvalid(x,y))                                                                          
    { return false; }
    
    if(isOptimizable(x,y,3)) {             // doubt
      return false;
      }
    
    sol3[y][x]=1; push3(10*y + x);
    l3++;
    if(maze[y][x]==dest)
    { curX = x; curY = y; return true; }
    
    if(d!=4) {  if (findpath3(x,y+1,2)) return true;}               // d=4 negative y direction  
    if(d!=3) {  if (findpath3(x+1,y,1)) return true;}               // d=3 negative x direction
    if(d!=1) {  if (findpath3(x-1,y,3)) return true;}               // d=1 positive x direction
    if(d!=2) {  if (findpath3(x,y-1,4)) return true;}               // d=2 positive y direction
     sol3[y][x]=0; pop3();
     l3--;
     return false;
 }


 /*
 void printmaze()
 {
  for(int i=3;i>-1;i--)
  {
    for(int j=0;j<4;j++)
    {
      cout << maze[i][j] << " ";
    }
    cout << '\n';
  }
  cout << '\n';
  cout << '\n';
 }
*/ 

void solvemaze(int xi, int yi, int end_pos) 
{
  ini_sol();
  ini_sol1();
  ini_sol2();
  ini_sol3();
  l1 = 0;
  l2 = 0;
  l3 = 0;
  top1 = -1; top2 = -1; top3 = -1;
  dest = end_pos;
  findpath1(xi, yi, 0);
  findpath2(xi, yi, 0);
  findpath3(xi, yi, 0);
 
  minm = l1;
  if(l2<=minm)
      minm=l2;
  else if(l3<=minm)
      minm = l3;
      
  if(minm == l1 )
  {
    for(r=0;r<=3;r++)
      {for(c=0;c<=3;c++)
           { sol[r][c]=sol1[r][c];}
      }   
    for(i=0;i<top1;i++)
       { push(stack1[i]);} 
   }
   
  else if(minm == l2 )
  {
    for(r=0;r<=3;r++)
       {for(c=0;c<=3;c++)
           {sol[r][c]=sol2[r][c];}
       }
    for(i=0;i<top2;i++)
        {push(stack2[i]);}         
  }
  
  else if(minm == l3 )
  {
    for(r=0;r<=3;r++)
       {for(c=0;c<=3;c++)
           {sol[r][c]=sol3[r][c];}
       }
    for(i=0;i<top3;i++)
        {push(stack3[i]);}              
  }  
  //printsol();
}


//Assuming
//First block is kept at Node = 5
//Transfer zone is Node = 6 (Ye toh fixed point h, save kr lena bas maze me)
//Jedi block is Node = 7    (Ye bhi fixed h na, 0,6 h sayad
//Jedi zone is Node = 8
//Pit is node = 9
//I am assuming wahi ruk jaega woh, Node 8 pe

void  getFinalPath()
{
  //printmaze();
        
        //Starting at point 2,0 and moving towards Clone block
        solvemaze(2,0,3);
        target[0] = 10*curY + curX;
      //cout << '\n';
      /*
        //Now moving towards Node 6;
        solvemaze(curX,curY,6);
        target[1] = 10*curY + curX;
        //now moving towards pit which is node 9
          
      cout << '\n';
    
        solvemaze(curX,curY,9);
        target[2] = 10*curY + curX;
        //Now sail towards Node 7 to pick up the Jedi block
              
      cout << '\n';
    
        solvemaze(curX,curY,7);
        target[3] = 10*curY + curX;
              
      cout << '\n';
    
        solvemaze(curX,curY,8);
        target[4] = 10*curY + curX;
        push(target[4]);*/
}


void loop() {
  Serial.print('\n');
  
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(LED_BUILTIN,LOW);
  
  
  delay(1000);
   getFinalPath();
  
  long int direct = 0;
  int arra[20];
    int ccc = 0;
  int x = 0; int y = 2;
  
  while(maze[x][y] != 3){
    if(x + 1 < 4){
      if( (sol[x+1][y] == 1) || sol[x+1][y] == 3){
        sol[x][y] = 0;
        x += 1;
        direct = (direct*10) + 1;
                arra[ccc] = 1;
                ccc += 1;// 1 for Up 
       }
     }
     if(x - 1 >= 0){
      if( (sol[x-1][y] == 1) || sol[x-1][y] == 3){
        sol[x][y] = 0;
        x -= 1;
        direct = (direct*10) + 2;
                arra[ccc] = 2;
                ccc += 1;//2 for Down
       }
     }
     if(y + 1 < 4){
      if( (sol[x][y+1] == 1) || sol[x][y+1] == 3){
        sol[x][y] = 0;
        y += 1;
        direct = (direct*10) + 3;
                arra[ccc] = 3;
                ccc += 1;//3 for Right
       }
     }
     if(y - 1 < 4){
      if( (sol[x][y-1] == 1) || sol[x][y-1] == 3){
        sol[x][y] = 0;
        y -= 1;
        direct = (direct*10) + 4;
                arra[ccc] = 4;
                ccc += 1;//4 for Left
       }
     }
    
   }
  long int dn;
  int direct_len = log10(direct)+1;
  for(int i = 0; i < direct_len; i++){
    Serial.print(arra[i]);
    //dn = (int)(direct/((pow(10,direct_len-i))))%10 ;
      for(int j = 0; j < arra[i]; j++){
        
        digitalWrite(LED_BUILTIN,HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN,LOW);
        delay(300);
      } 
      delay(1500);
        //Serial.print('\t');
    //Serial.print(dn);
        Serial.print('\n');
    
  }
  
  
    
  }

 

// β -> angle btwn x & y axis
// α -> angle btwn y & z axis
//  x = rcosβsinα  
//  y = rcosβcosα
//  z = rsinβ

void calcElbowPos(int r){
  int a = BX - 90;
  int b = BZ;
  x1 = r * cos(b * M_PI / 180) * sin(a * M_PI / 180); 
  y1 = r * cos(b * M_PI / 180) * cos(a * M_PI / 180); 
  z1 = r * sin(b * M_PI / 180); 
}

void calcHandPos(int x1, int y1, int z1, int r){
  int a = BX - 90;
  int b = BZ;
  int x2 = x1 + r * cos(b * M_PI / 180) * sin(a * M_PI / 180); 
  int y2 = y1 + r * cos(b * M_PI / 180) * cos(a * M_PI / 180); 
  int z2 = z1 + r * sin(b * M_PI / 180); 
}

